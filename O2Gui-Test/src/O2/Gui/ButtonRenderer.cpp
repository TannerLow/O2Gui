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

		void ButtonRenderer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
			states.transform *= getTransform();
			target.draw(rectangle, states);
		}

	} // namespace gui
} // namespace o2