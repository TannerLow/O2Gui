#pragma once
#include <memory>
#include "Renderer.h"

class Renderable {
public:
	bool owned = false;
	std::weak_ptr<Renderer> renderer;

	virtual ~Renderable() = 0;

	virtual void render() {
		if (auto sp = renderer.lock()) {
			sp->update();
		}
	}
};
