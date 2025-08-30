#pragma once
#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include "Button.h"
#include "ButtonRenderer.h"

class GraphicsManager : public sf::Drawable, public sf::Transformable {
public:
	std::vector<std::shared_ptr<Renderer>> renderers;

public:
	GraphicsManager() {}
	~GraphicsManager() = default;

	std::shared_ptr<Button> createButton() {
		std::shared_ptr<Button> button = std::make_shared<Button>();
		renderers.push_back(std::make_shared<ButtonRenderer>(button));
		button->renderer = std::weak_ptr<Renderer>(renderers.back());
		return button;
	}

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		states.transform *= getTransform();
		for (const auto& renderer : renderers) {
			target.draw(*renderer.get(), states);
		}
	}
};