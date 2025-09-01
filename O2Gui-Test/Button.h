#pragma once
#include <functional>
#include "Color.h"
#include "Renderable.h"

class Button : public Renderable {
public:
	float x;
	float y;
	float width;
	float height;
	Color color;
	std::function<void()> callback;

public:
	void setOnClick(std::function<void()> callback) {
		this->callback = callback;
	}

	void handleClick(float clickX, float clickY) {
		if (x <= clickX and clickX <= x + width) {
			if (y <= clickY and clickY <= y + height) {
				callback();
			}
		}
	}
};