#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Renderer.h"

class ButtonRenderer : public Renderer {
protected:
	std::shared_ptr<Button> button;
	
	sf::RectangleShape rectangle;

public:
	ButtonRenderer(std::shared_ptr<Button>& button) {
		this->button = button;
	}

	void update() override {
		rectangle.setSize({ button->width, button->height });
		rectangle.setFillColor(
			sf::Color(
				button->color.r,
				button->color.g,
				button->color.b,
				button->color.a
			)
		);
		setPosition({ button->x, button->y });
	}

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		states.transform *= getTransform();
		target.draw(rectangle, states);
	}
};