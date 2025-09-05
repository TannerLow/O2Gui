#pragma once
#include "Renderable.h"
#include "ScrollDirection.h"
#include "ScrollBarComponentLocations.h"
#include <O2/Util/RateLimiter.h>

namespace o2 {
	namespace gui {

		class ScrollPanel : public Renderable {
		public:
			float x;
			float y;
			float visibleWidth;
			float visibleHeight;
			float maxHeight;

			ScrollBarComponentLocations scrollBarComponentLocations;

			float scrollPercentage = 0;
			float scrollAmount = 20;

			bool pressingDecrease = false;
			bool pressingIncrease = false;
			bool pressingBar = false;
			float mouseOffsetFromBarY = 0;
			RateLimiter scrollButtonsLimiter;
			RateLimiter scrollBarLimiter;

			std::unordered_map<std::string, std::weak_ptr<Renderable>> elements;

		public:
			ScrollPanel();

			void handleClick(float clickX, float clickY);
			void handleClickRelease(float clickX, float clickY);
			void scrollUp();
			void scrollDown();
			void scrollToMouse(float mouseX, float mouseY);
			void handleScroll(ScrollDirection direction);
			void update(float mouseX, float mouseY);
		};

	} // namespace gui
} // namespace o2
