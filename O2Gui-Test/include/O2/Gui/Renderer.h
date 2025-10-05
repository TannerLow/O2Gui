#pragma once
#include <SFML/Graphics.hpp>
#include "MouseButton.h"

namespace o2 {
	namespace gui {

		class Renderer : public sf::Drawable, public sf::Transformable {
		public:
			bool owned = false;
			virtual void update() = 0;
			virtual bool containsPoint(float x, float y) const = 0;
			virtual int getZIndex() const = 0;
			virtual void click(float x, float y, MouseButton button) {}
			virtual void releaseClick(float x, float y, MouseButton button) {}

			bool operator<(const Renderer& other) const;

		protected:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
		};

	} // namespace gui
} // namespace o2
