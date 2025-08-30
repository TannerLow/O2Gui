#pragma once

namespace o2 {
	namespace gui {

		class UIElement {
		public:
			virtual ~UIElement() = default;
			virtual void draw() = 0;
			virtual void update();
			virtual void handleEvent();
		};

	} // namespace gui
} // namespace o2

