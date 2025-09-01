#pragma once
#include <memory>
#include "Color.h"
#include "Renderable.h"

class Image : public Renderable {
public:
	float x;
	float y;
	float width;
	float height;
	Color color;
};