#include <O2/Gui/TextBoxRenderer.h>

namespace o2 {
	namespace gui {

		TextBoxRenderer::TextBoxRenderer(
			std::shared_ptr<TextBox>& textbox,
			sf::Texture* backgroundTexture
		) {
			this->textbox = textbox;
			if (backgroundTexture) {
				background.setTexture(backgroundTexture);
			}
		}

		void TextBoxRenderer::update() {
			setPosition({ textbox->x, textbox->y });
			background.setSize({ textbox->width, textbox->height });
		}

		bool TextBoxRenderer::containsPoint(float x, float y) const {
			return
				textbox->x <= x and
				x <= textbox->x + textbox->width and
				textbox->y <= y and
				y <= textbox->y + textbox->height;
		}
		
		int TextBoxRenderer::getZIndex() const {
			return textbox->zIndex;
		}

		void TextBoxRenderer::click(float x, float y, MouseButton mouseButton) {
			textbox->onClick(x, y, mouseButton);
		}

		void TextBoxRenderer::releaseClick(float x, float y, MouseButton mouseButton) {
			textbox->onClickRelease(x, y, mouseButton);
		}

		void TextBoxRenderer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
			states.transform *= getTransform();
			target.draw(background, states);
			if (textbox->text) {
				if (auto textRenderer = textbox->text->renderer.lock()) {
					target.draw(*textRenderer.get(), states);
				}
			}
		}

	} // namespace gui
} // namespace o2