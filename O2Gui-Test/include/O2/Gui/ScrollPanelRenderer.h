#pragma once
#include <SFML/Graphics.hpp>
#include "ScrollPanel.h"
#include "Renderer.h"


namespace o2 {
	namespace gui {

		class ScrollPanelRenderer : public Renderer {
		protected:
			std::shared_ptr<ScrollPanel> scrollPanel;

			sf::RenderTexture renderTexture;
			float cachedWidth = 0;
			float cachedHeight = 0;
			sf::Sprite sprite;
			float scrollBarScrollLength = 0;
			std::unique_ptr<sf::Sprite> increaseButton;
			std::unique_ptr<sf::Sprite> barButton;
			sf::RectangleShape barBackground;
			std::unique_ptr<sf::Sprite> decreaseButton;

		public:
			ScrollPanelRenderer(
				std::shared_ptr<ScrollPanel>& scrollPanel,
				sf::Texture* increaseTexture,
				sf::Texture* barTexture,
				sf::Texture* barBackgroundTexture,
				sf::Texture* decreaseTexture
			);

			void onSizeUpdate();
			void update() override;

		protected:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		};

	} // namespace gui
} // namespace o2
