#include <O2/Gui/ButtonRenderer.h>

namespace o2 {
	namespace gui {

		ButtonRenderer::ButtonRenderer(std::shared_ptr<Button>& button) {
			this->button = button;
		}

		void ButtonRenderer::update() {
			rectangle.setSize({ button->width, button->height });
			rectangle.setFillColor(
				sf::Color(
					button->color.r,
					button->color.g,
					button->color.b,
					button->color.a
				)
			);
			setPosition({ button->x, button->y });
		}

		bool ButtonRenderer::containsPoint(float x, float y) const {
			return
				button->x <= x and
				x <= button->x + button->width and
				button->y <= y and
				y <= button->y + button->height;
		}

		int ButtonRenderer::getZIndex() const {
			return button->zIndex;
		}

		void ButtonRenderer::click(float x, float y, MouseButton mouseButton) {
			button->onClick(x, y, mouseButton);
		}

		void ButtonRenderer::releaseClick(float x, float y, MouseButton mouseButton) {
			button->onReleaseClick(x, y, mouseButton);
		}

		void ButtonRenderer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
			states.transform *= getTransform();
			target.draw(rectangle, states);
		}

	} // namespace gui
} // namespace o2