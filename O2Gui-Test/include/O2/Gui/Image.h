#pragma once
#include <memory>
#include "Color.h"
#include "Renderable.h"

namespace o2 {
	namespace gui {

		class Image : public Renderable {
		public:
			float x;
			float y;
			float width;
			float height;
			Color color;
			int zIndex = 0;
		};

	} // namespace gui
} // namespace o2
