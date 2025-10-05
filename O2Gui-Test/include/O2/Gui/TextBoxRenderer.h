#pragma once
#include "Renderer.h"
#include <SFML/Graphics.hpp>
#include "TextBox.h"

namespace o2 {
	namespace gui {

		class TextBoxRenderer : public Renderer {
		protected:
			std::shared_ptr<TextBox> textbox;
			sf::RectangleShape background;

		public:
			TextBoxRenderer(
				std::shared_ptr<TextBox>& textbox,
				sf::Texture* backgroundTexture
			);

			void update() override;
			bool containsPoint(float x, float y) const;
			int getZIndex() const override;
			void click(float x, float y, MouseButton button) override;
			void releaseClick(float x, float y, MouseButton button) override;

		protected:
			void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		};

	} // namespace gui
} // namespace o2
