#include <O2/Gui/UIManager.h>

namespace o2 {
	namespace gui {

		void UIManager::addElement(UIElement* element) {
			elements.push_back(std::shared_ptr<UIElement>(element));
		}

		void UIManager::addElement(std::shared_ptr<UIElement>& element) {
			elements.push_back(element);
		}

		void UIManager::draw() {
			for (const auto& element : elements) {
				element->draw();
			}
		}

		void UIManager::update() {

		}

		void UIManager::handleEvent() {

		}

	} // namespace gui
} // namespace o2