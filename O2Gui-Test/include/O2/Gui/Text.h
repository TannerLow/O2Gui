#pragma once
#include "Renderable.h"
#include <string>
#include "Color.h"
#include <unordered_map>


namespace o2 {
	namespace gui {

		class Text : public Renderable {
		public:
			float x = 0;
			float y = 0;
			float scale = 1;
			std::string text;
			std::unordered_map<size_t, Color> colors;
		};

	} // namespace gui
} // namespace o2
