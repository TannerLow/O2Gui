#include <O2/Gui/Button.h>

namespace o2 {
	namespace gui {

		void Button::setOnClick(std::function<void()> callback) {
			this->callback = callback;
		}

		void Button::handleClick(float clickX, float clickY) {
			if (x <= clickX and clickX <= x + width) {
				if (y <= clickY and clickY <= y + height) {
					callback();
				}
			}
		}

	} // namespace gui
} // namespace o2
