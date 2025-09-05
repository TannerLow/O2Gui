#pragma once
#include <functional>
#include "Color.h"
#include "Renderable.h"

namespace o2 {
	namespace gui {

		class Button : public Renderable {
		public:
			float x;
			float y;
			float width;
			float height;
			Color color;
			std::function<void()> callback;

		public:
			void setOnClick(std::function<void()> callback);
			void handleClick(float clickX, float clickY);
		};

	} // namespace gui
} // namespace o2
