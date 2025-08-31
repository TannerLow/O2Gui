#pragma once
#include <memory>
#include "Renderer.h"

class Renderable {
public:
	bool owned = false;
	std::weak_ptr<Renderer> renderer;

	virtual void render() = 0;
};