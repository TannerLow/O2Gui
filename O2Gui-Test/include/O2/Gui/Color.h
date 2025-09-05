#pragma once
#include <cstdint>
#include <SFML/Graphics.hpp>

namespace o2 {
	namespace gui {

		struct Color {
			uint8_t r = 255;
			uint8_t g = 255;
			uint8_t b = 255;
			uint8_t a = 255;

			Color() {}

			Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
				this->r = r;
				this->g = g;
				this->b = b;
				this->a = a;
			}

			Color(sf::Color color) {
				r = color.r;
				g = color.g;
				b = color.b;
				a = color.a;
			}
		};
	
	} // namespace gui
} // namespace o2
