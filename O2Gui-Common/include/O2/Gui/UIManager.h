#pragma once
#include <vector>
#include "UIElement.h"
#include <memory>

namespace o2 {
	namespace gui {
		
		class UIManager {
		protected:
			std::vector<std::shared_ptr<UIElement>> elements;

		public:
			void addElement(UIElement* element);
			void addElement(std::shared_ptr<UIElement>& element);
			void draw();
			void update();
			void handleEvent();
		};

	} // namespace gui
} // namespace o2
