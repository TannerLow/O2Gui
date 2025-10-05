#include <O2/Gui/Button.h>

namespace o2 {
	namespace gui {

		void Button::setCallback(std::function<void()> callback) {
			this->callback = callback;
		}

		void Button::onClick(float clickX, float clickY, MouseButton mouseButton) {
			if (mouseButton != MouseButton::Left) {
				return;
			}

			if (x <= clickX and clickX <= x + width) {
				if (y <= clickY and clickY <= y + height) {
					isPressed = true;
				}
			}
		}

		void Button::onReleaseClick(float clickX, float clickY, MouseButton mouseButton) {
			if (mouseButton != MouseButton::Left) {
				return;
			}

			if (isPressed) {
				if (x <= clickX and clickX <= x + width) {
					if (y <= clickY and clickY <= y + height) {
						if (callback) {
							callback();
						}
					}
				}
			}

			isPressed = false;
		}

	} // namespace gui
} // namespace o2
