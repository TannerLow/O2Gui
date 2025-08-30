#include <O2/Gui/Rectangle.h>
#include <iostream>
#include <SFML/Graphics.hpp>

namespace o2 {
	namespace gui {

		struct Rectangle::Impl {
			sf::RectangleShape shape;
		};

		Rectangle::Rectangle()
			: UIElement()
		{
			impl = std::make_unique<Impl>();
			impl->shape.setSize({100, 100});
			impl->shape.setFillColor(sf::Color::Green);
			impl->shape.setPosition({10, 10});
		}

		void Rectangle::draw() {
			
		}

		void Rectangle::update() {
			std::cout << "Rectangle update call" << std::endl;
		}

		void Rectangle::handleEvent() {
			std::cout << "Rectangle handleEvent call" << std::endl;
		}

	} // namespace gui
} // namespace o2