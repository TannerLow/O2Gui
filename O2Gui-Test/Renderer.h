#pragma once
#include <SFML/Graphics.hpp>

class Renderer : public sf::Drawable, public sf::Transformable {
public:
	virtual void update() = 0;

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
};