#include <O2/Gui/TextBox.h>
#include <functional>
#include <cctype>

namespace o2 {
	namespace gui {

		void TextBox::onClick(float x, float y, MouseButton mouseButton) {
			if (mouseButton != MouseButton::Left) {
				return;
			}
			clicked = true;
		}

		void TextBox::onClickRelease(float clickX, float clickY, MouseButton mouseButton) {
			if (mouseButton != MouseButton::Left) {
				return;
			}

			if (clicked) {
				if (x <= clickX and clickX <= x + width) {
					if (y <= clickY and clickY <= y + height) {
						if (eventBroadcaster) {
							eventBroadcaster->registerTextListener(std::bind(&TextBox::onTextEntered, this, std::placeholders::_1));
						}
						text->text = "Clicked";
						text->render();
					}
				}
			}

			clicked = false;
		}

		void TextBox::onTextEntered(char c) {
			if (std::isprint(c)) {
				text->text += c;
			}
			else if (c == 8) { // backspace
				if (not text->text.empty()) {
					text->text.pop_back();
				}
			}
			else if (c == 127) { // ctrl + backspace
				deleteLastWord();
			}

			text->render();
		}

		void TextBox::deleteLastWord(bool rerender) {
			std::string& s = text->text;

			if (s.empty()) return;

			// Remove trailing spaces
			while (!s.empty() && std::isspace((unsigned char)s.back())) {
				s.pop_back();
			}

			// Remove last word characters
			while (!s.empty() && !std::isspace((unsigned char)s.back())) {
				s.pop_back();
			}

			if (rerender) {
				text->render();
			}
		}

	} // namespace gui
} // namespace o2