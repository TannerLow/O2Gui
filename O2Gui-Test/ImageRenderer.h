#pragma once
#include <SFML/Graphics.hpp>
#include "Image.h"
#include "Renderer.h"

class ImageRenderer : public Renderer {
protected:
	std::shared_ptr<Image> image;

	sf::RectangleShape rectangle;

public:
	ImageRenderer(std::shared_ptr<Image>& image, std::weak_ptr<sf::Texture> texture) {
		this->image = image;
		if (auto sp = texture.lock()) {
			rectangle.setTexture(sp.get());
		}
	}

	void update() override {
		rectangle.setSize({ image->width, image->height });
		rectangle.setFillColor(
			sf::Color(
				image->color.r,
				image->color.g,
				image->color.b,
				image->color.a
			)
		);
		setPosition({ image->x, image->y });
		owned = image->owned;
	}

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		states.transform *= getTransform();
		target.draw(rectangle, states);
	}
};