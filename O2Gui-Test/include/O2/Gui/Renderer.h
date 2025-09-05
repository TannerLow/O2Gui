#pragma once
#include <SFML/Graphics.hpp>

namespace o2 {
	namespace gui {

		class Renderer : public sf::Drawable, public sf::Transformable {
		public:
			bool owned = false;
			virtual void update() = 0;

		protected:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
		};

	} // namespace gui
} // namespace o2
