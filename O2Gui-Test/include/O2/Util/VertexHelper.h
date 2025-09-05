#pragma once
#include <SFML/Graphics.hpp>

namespace o2 {
	namespace vh {

		void updateQuadTexture(sf::Vertex* vertex, const sf::IntRect texCoords);
		void positionQuad(sf::Vertex* vertex, const sf::FloatRect rect);
		void colorQuad(sf::Vertex* vertex, const sf::Color color);
		bool containedByQuad(const sf::Vertex* vertex, const sf::Vector2f point);

	} // namespace vh
} // namespace o2
