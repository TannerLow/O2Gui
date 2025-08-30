#pragma once
#include "UIElement.h"
#include <memory>
#include "Window.h"

namespace o2 {
	namespace gui {

		class Rectangle : public UIElement {
		protected:
			struct Impl;
			std::unique_ptr<Impl> impl;

		public:
			Rectangle();
			virtual ~Rectangle() = default;
			void draw() override;
			void update() override;
			void handleEvent() override;
		};

	} // namespace gui
} // namespace o2