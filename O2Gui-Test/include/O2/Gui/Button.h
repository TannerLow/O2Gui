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
			int zIndex = 0;
			bool isPressed = false;

		public:
			void setCallback(std::function<void()> callback);
			// NOTE technically dont need x and y coords since the bounds should have already been checked in the graphics manager
			void onClick(float clickX, float clickY, MouseButton mouseButton);
			void onReleaseClick(float clickX, float clickY, MouseButton mouseButton);
		};

	} // namespace gui
} // namespace o2
