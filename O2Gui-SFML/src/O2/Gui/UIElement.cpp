#include <O2/Gui/UIElement.h>
#include <iostream>

namespace o2 {
	namespace gui {

		//void UIElement::draw() {
		//	std::cout << "UIElement draw call" << std::endl;
		//}

		void UIElement::update() {
			std::cout << "UIElement update call" << std::endl;
		}

		void UIElement::handleEvent() {
			std::cout << "UIElement handleEvent call" << std::endl;
		}

	} // namespace gui
} // namespace o2