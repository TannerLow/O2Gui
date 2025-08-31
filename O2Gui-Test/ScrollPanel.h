#pragma once
#include <memory>
#include "Renderer.h"
#include "Renderable.h"
#include "ScrollDirection.h"
#include "ScrollBarComponentLocations.h"
#include "RateLimiter.h"

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
	ScrollPanel() {
		scrollButtonsLimiter.setLimit(10);
		scrollBarLimiter.setLimit(250);
	}

	void handleClick(float clickX, float clickY) {
		ScrollBarComponentLocations& sbcl = scrollBarComponentLocations;
		if (sbcl.scrollDecreaseX <= clickX and clickX <= sbcl.scrollDecreaseX + sbcl.scrollDecreaseWidth) {
			if (sbcl.scrollDecreaseY <= clickY and clickY <= sbcl.scrollDecreaseY + sbcl.scrollDecreaseHeight) {
				pressingDecrease = true;
			}
		}

		if (sbcl.scrollIncreaseX <= clickX and clickX <= sbcl.scrollIncreaseX + sbcl.scrollIncreaseWidth) {
			if (sbcl.scrollIncreaseY <= clickY and clickY <= sbcl.scrollIncreaseY + sbcl.scrollIncreaseHeight) {
				pressingIncrease = true;
			}
		}

		if (sbcl.scrollBarX <= clickX and clickX <= sbcl.scrollBarX + sbcl.scrollBarWidth) {
			if (sbcl.scrollBarY <= clickY and clickY <= sbcl.scrollBarY + sbcl.scrollBarHeight) {
				pressingBar = true;
				mouseOffsetFromBarY = clickY - sbcl.scrollBarY;
			}
		}
	}

	void handleClickRelease(float clickX, float clickY) {
		pressingDecrease = false;
		pressingIncrease = false;
		pressingBar = false;
	}

	void scrollUp() {
		scrollPercentage -= scrollAmount / (maxHeight - visibleHeight);
		scrollPercentage = std::max(scrollPercentage, 0.f);
	}

	void scrollDown() {
		scrollPercentage += scrollAmount / (maxHeight - visibleHeight);
		scrollPercentage = std::min(scrollPercentage, 1.f);
	}

	void scrollToMouse(float mouseX, float mouseY) {
		ScrollBarComponentLocations& sbcl = scrollBarComponentLocations;
		float lowerBound = sbcl.scrollDecreaseY + sbcl.scrollDecreaseHeight;
		float upperBound = sbcl.scrollIncreaseY - sbcl.scrollBarHeight;
		mouseY -= lowerBound + mouseOffsetFromBarY;
		scrollPercentage = mouseY / (upperBound - lowerBound);
		scrollPercentage = std::max(scrollPercentage, 0.f);
		scrollPercentage = std::min(scrollPercentage, 1.f);
	}

	void handleScroll(ScrollDirection direction) {
		if (direction == ScrollDirection::UP) {
			scrollUp();
		}
		else {
			scrollDown();
		}
		render();
	}

	void update(float mouseX, float mouseY) {
		bool dirty = false;

		if (scrollButtonsLimiter.isReady()) {
			if (pressingDecrease) {
				scrollUp();
				dirty = true;
			}
			if (pressingIncrease) {
				scrollDown();
				dirty = true;
			}
		}

		if (scrollBarLimiter.isReady()) {
			if (pressingBar) {
				scrollToMouse(mouseX, mouseY);
				dirty = true;
			}
		}

		if (dirty) {
			render();
		}
	}

	void render() override {
		if (auto sp = renderer.lock()) {
			sp->update();
		}
	}
};