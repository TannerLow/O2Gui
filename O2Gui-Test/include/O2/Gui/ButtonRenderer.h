#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Renderer.h"

namespace o2 {
	namespace gui {

		class ButtonRenderer : public Renderer {
		protected:
			std::shared_ptr<Button> button;
			sf::RectangleShape rectangle;

		public:
			ButtonRenderer(std::shared_ptr<Button>& button);

			void update() override;
			bool containsPoint(float x, float y) const override;
			int getZIndex() const override;
			void click(float x, float y, MouseButton mouseButton) override;
			void releaseClick(float x, float y, MouseButton mouseButton) override;

		protected:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		};

	} // namespace gui
} // namespace o2
