#pragma once
#include <SFML/Window.hpp>

namespace o2 {
	namespace gui {

		enum class MouseButton {
			Left, 
			Right, 
			Middle
		};

		namespace convert {

			inline MouseButton toMouseButton(sf::Mouse::Button button) {
				switch (button)
				{
				case sf::Mouse::Button::Left   : return MouseButton::Left;
				case sf::Mouse::Button::Right  : return MouseButton::Right;
				case sf::Mouse::Button::Middle : return MouseButton::Middle;
				default                        : return MouseButton::Left;
				}
			}

		} // namespace convert

	} // namepsace gui
} // namespace o2
