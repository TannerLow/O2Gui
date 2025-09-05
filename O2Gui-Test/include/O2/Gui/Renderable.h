#pragma once
#include <memory>
#include "Renderer.h"

namespace o2 {
	namespace gui {

		class Renderable {
		public:
			bool owned = false;
			std::weak_ptr<Renderer> renderer;

			virtual ~Renderable() = 0;

			virtual void render();
		};

	} // namespace gui
} // namespace o2
