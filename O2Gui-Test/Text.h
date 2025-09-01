#pragma once
#include "Renderable.h"
#include <string>
#include "Color.h"

class Text : public Renderable {
public:
	std::string text;
	Color color;
};