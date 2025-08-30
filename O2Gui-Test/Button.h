#pragma once
#include <memory>
#include "Renderer.h"
#include <functional>

class Button {
public:
	float x;
	float y;
	float width;
	float height;
	std::weak_ptr<Renderer> renderer;
	std::function<void()> callback;

public:
	void setOnClick(std::function<void()> callback) {
		this->callback = callback;
	}

	void render() {
		if (auto sp = renderer.lock()) {
			sp->update();
		}
	}
};