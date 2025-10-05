#include <O2/Gui/GraphicsManager.h>
#include <algorithm>


namespace o2 {
	namespace gui {

		namespace compare {
			bool RendererPtrComparator(const std::shared_ptr<Renderer>& a, const std::shared_ptr<Renderer>& b) {
				if (!a or !b) return true;
				return *a < *b;
			}
		}

		std::weak_ptr<Font> GraphicsManager::loadFont(
			const std::string& fontName,
			const sf::Vector2u charSize,
			const sf::Vector2u charsPerImageDimension,
			const fs::path& fontWidthFile,
			std::map<int, fs::path> imagePaths
		) {
			std::shared_ptr<Font> font = std::make_shared<Font>();

			if (!font->load(charSize, charsPerImageDimension, fontWidthFile, imagePaths)) {
				std::cout << "Failed to load font: " << fontName << std::endl;
				assert(false && "Failed to load font");
				exit(1);
				return std::weak_ptr<Font>();
			}

			fonts.emplace(fontName, font);
			return std::weak_ptr<Font>(font);
		}

		std::shared_ptr<Button> GraphicsManager::createButton() {
			std::shared_ptr<Button> button = std::make_shared<Button>();
			renderers.push_back(std::make_shared<ButtonRenderer>(button));
			button->renderer = std::weak_ptr<Renderer>(renderers.back());
			return button;
		}

		bool GraphicsManager::loadTexture(const fs::path& filepath) {
			if (textures.count(filepath) < 1) {
				textures[filepath] = std::make_shared<sf::Texture>();
				if (!textures[filepath]->loadFromFile(filepath)) {
					std::cout << "Failed to load image from file: " << filepath.string() << std::endl;
					assert(false && "Failed to load image from file");
					exit(1);
					return false;
				}
			}
			return true;
		}

		std::shared_ptr<Image> GraphicsManager::createImage(const fs::path& filepath) {
			if (!loadTexture(filepath)) {
				return nullptr;
			}

			std::shared_ptr<Image> image = std::make_shared<Image>();
			auto texture = std::weak_ptr<sf::Texture>(textures[filepath]);
			renderers.push_back(std::make_shared<ImageRenderer>(image, texture));
			image->renderer = std::weak_ptr<Renderer>(renderers.back());
			sortByZIndex();
			return image;
		}

		std::shared_ptr<ScrollPanel> GraphicsManager::createScrollPanel(const ScrollBarTextures& scrollBarTextures) {
			std::shared_ptr<ScrollPanel> scrollPanel = std::make_shared<ScrollPanel>();

			if (scrollBarTextures.decrease.has_value() and !loadTexture(scrollBarTextures.decrease.value())) {
				return nullptr;
			}
			if (!loadTexture(scrollBarTextures.bar)) {
				return nullptr;
			}
			if (!loadTexture(scrollBarTextures.barBackground)) {
				return nullptr;
			}
			if (scrollBarTextures.increase.has_value() and !loadTexture(scrollBarTextures.increase.value())) {
				return nullptr;
			}

			sf::Texture* decreaseTexture = nullptr;
			sf::Texture* barTexture = nullptr;
			sf::Texture* barBackgroundTexture = nullptr;
			sf::Texture* increaseTexture = nullptr;

			if (scrollBarTextures.decrease.has_value() and textures.count(scrollBarTextures.decrease.value()) > 0) {
				decreaseTexture = textures[scrollBarTextures.decrease.value()].get();
			}
			if (textures.count(scrollBarTextures.bar) > 0) {
				barTexture = textures[scrollBarTextures.bar].get();
			}
			if (textures.count(scrollBarTextures.barBackground) > 0) {
				barBackgroundTexture = textures[scrollBarTextures.barBackground].get();
			}
			if (scrollBarTextures.increase.has_value() and textures.count(scrollBarTextures.increase.value()) > 0) {
				increaseTexture = textures[scrollBarTextures.increase.value()].get();
			}

			renderers.push_back(
				std::make_shared<ScrollPanelRenderer>(
					scrollPanel,
					increaseTexture,
					barTexture,
					barBackgroundTexture,
					decreaseTexture
					)
			);
			scrollPanel->renderer = std::weak_ptr<Renderer>(renderers.back());
			sortByZIndex();

			return scrollPanel;
		}

		std::shared_ptr<Text> GraphicsManager::createText(const std::string& fontName) {
			auto it = fonts.find(fontName);
			if (it == fonts.end()) {
				std::cout << "Attempt to use unloaded font: " << fontName << std::endl;
				assert(false && "Font has not been loaded via GraphicsManager yet");
				return nullptr;
			}

			std::shared_ptr<Text> text = std::make_shared<Text>();
			renderers.push_back(std::make_shared<TextRenderer>(text, std::weak_ptr<Font>(it->second)));
			text->renderer = std::weak_ptr<Renderer>(renderers.back());
			sortByZIndex();
			return text;
		}

		std::shared_ptr<TextBox> GraphicsManager::createTextBox(std::optional<fs::path> filepath) {
			if (filepath.has_value() and !loadTexture(filepath.value())) {
				return nullptr;
			}
			sf::Texture* texture = nullptr;
			if (filepath.has_value()) {
				texture = textures[filepath.value()].get();
			}

			std::shared_ptr<TextBox> textbox = std::make_shared<TextBox>();
			renderers.push_back(std::make_shared<TextBoxRenderer>(textbox, texture));
			textbox->renderer = std::weak_ptr<Renderer>(renderers.back());
			sortByZIndex();
			return textbox;
		}

		void GraphicsManager::click(float x, float y, MouseButton mouseButton) {
			std::shared_ptr<Renderer> topMost;
			int zIndexMax = INT_MIN;

			// NOTE renderers should already be z sorted otherwise the rendering will be off
			// so can likely get away with breaking the loop at first valid renderer
			for (std::shared_ptr<Renderer>& renderer : renderers) {
				if (not renderer->owned) {
					if (renderer->containsPoint(x, y)) {
						int zIndex = renderer->getZIndex();
						if (zIndex > zIndexMax) {
							zIndexMax = zIndex;
							topMost = renderer;
						}
					}
				}
			}

			if (topMost) {
				topMost->click(x, y, mouseButton);
			}
		}

		void GraphicsManager::releaseClick(float x, float y, MouseButton mouseButton) {
			// releaseClick differs in that it sends the event to all renderers since
			// we may click on one thing but release on another
			for (std::shared_ptr<Renderer>& renderer : renderers) {
				if (not renderer->owned) {
					renderer->releaseClick(x, y, mouseButton);
				}
			}
		}

		void GraphicsManager::sortByZIndex() {
			std::sort(renderers.begin(), renderers.end(), compare::RendererPtrComparator);
		}

		void GraphicsManager::draw(sf::RenderTarget& target, sf::RenderStates states) const {
			states.transform *= getTransform();
			for (int i = renderers.size() - 1; i >= 0; i--) {
				const std::shared_ptr<Renderer>& renderer = renderers[i];
				if (!renderer->owned) {
					target.draw(*renderer.get(), states);
				}
			}
		}

	} // namespace gui
} // namespace o2
