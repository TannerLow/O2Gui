#pragma once
#include <memory>
#include "Renderer.h"
#include "Color.h"
#include "Renderable.h"

class Image : public Renderable {
public:
	float x;
	float y;
	float width;
	float height;
	Color color;

public:
	void render() override {
		if (auto sp = renderer.lock()) {
			sp->update();
		}
	}
};