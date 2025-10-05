#pragma once
#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include "Button.h"
#include "ButtonRenderer.h"
#include "Image.h"
#include "ImageRenderer.h"
#include "ScrollPanel.h"
#include "ScrollPanelRenderer.h"
#include <filesystem>
#include <iostream>
#include <map>
#include "ScrollBarTextures.h"
#include "Font.h"
#include "TextRenderer.h"
#include "TextBoxRenderer.h"
#include "TextBox.h"
#include <optional>


namespace fs = std::filesystem;

namespace o2 {
	namespace gui {

		namespace compare {
			bool RendererPtrComparator(const std::shared_ptr<Renderer>& a, const std::shared_ptr<Renderer>& b);
		}

		class GraphicsManager : public sf::Drawable, public sf::Transformable {
		public:
			std::vector<std::shared_ptr<Renderer>> renderers;
			std::map<fs::path, std::shared_ptr<sf::Texture>> textures;
			std::map<std::string, std::shared_ptr<Font>> fonts;

		public:
			GraphicsManager() {}
			~GraphicsManager() = default;

			bool loadTexture(const fs::path& filepath);
			std::weak_ptr<Font> loadFont(
				const std::string& fontName,
				const sf::Vector2u charSize,
				const sf::Vector2u charsPerImageDimension,
				const fs::path& fontWidthFile,
				std::map<int, fs::path> imagePaths
			);
			std::shared_ptr<Button> createButton();
			std::shared_ptr<Image> createImage(const fs::path& filepath);
			std::shared_ptr<ScrollPanel> createScrollPanel(const ScrollBarTextures& scrollBarTextures);
			std::shared_ptr<Text> createText(const std::string& fontName);
			std::shared_ptr<TextBox> createTextBox(std::optional<fs::path> filepath);

			void click(float x, float y, MouseButton mouseButton);
			void releaseClick(float x, float y, MouseButton mouseButton);
			void sortByZIndex();
			void cleanOldRenderers() {
				// TODO implment a system of going thru the renderers and erasing any that are .unique()... maybe
			}

		protected:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		};

	} // namespace gui
} // namespace o2
