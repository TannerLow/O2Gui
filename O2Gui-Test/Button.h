#pragma once
#include <memory>
#include "Renderer.h"
#include <functional>
#include "Color.h"

class Button {
public:
	float x;
	float y;
	float width;
	float height;
	Color color;
	std::weak_ptr<Renderer> renderer;
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

	void render() {
		if (auto sp = renderer.lock()) {
			sp->update();
		}
	}
};