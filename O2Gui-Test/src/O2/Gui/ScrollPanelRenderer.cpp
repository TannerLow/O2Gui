#include <O2/Gui/ScrollPanelRenderer.h>


namespace o2 {
	namespace gui {

		ScrollPanelRenderer::ScrollPanelRenderer(
			std::shared_ptr<ScrollPanel>& scrollPanel,
			sf::Texture* increaseTexture,
			sf::Texture* barTexture,
			sf::Texture* barBackgroundTexture,
			sf::Texture* decreaseTexture
		) : sprite(renderTexture.getTexture()) {

			this->scrollPanel = scrollPanel;

			barButton = std::make_unique<sf::Sprite>(*barTexture);
			barBackground.setTexture(barBackgroundTexture);
			barBackground.setSize(sf::Vector2f(barBackgroundTexture->getSize()));
			if (increaseTexture) {
				increaseButton = std::make_unique<sf::Sprite>(*increaseTexture);
			}
			if (decreaseTexture) {
				decreaseButton = std::make_unique<sf::Sprite>(*decreaseTexture);
			}
		}

		void ScrollPanelRenderer::onSizeUpdate() {
			ScrollBarComponentLocations scrollBarComponentLocations;

			cachedWidth = scrollPanel->visibleWidth;
			cachedHeight = scrollPanel->visibleHeight;
			renderTexture.resize({ (unsigned int)cachedWidth, (unsigned int)cachedHeight });

			if (decreaseButton) {
				sf::Vector2i size = decreaseButton->getTextureRect().size;
				decreaseButton->setPosition({ cachedWidth - size.x, 0 });
				sf::Vector2f position = decreaseButton->getPosition();
				scrollBarComponentLocations.scrollDecreaseX = position.x + scrollPanel->x;
				scrollBarComponentLocations.scrollDecreaseY = position.y + scrollPanel->y;
				scrollBarComponentLocations.scrollDecreaseWidth = size.x;
				scrollBarComponentLocations.scrollDecreaseHeight = size.y;
			}
			if (barButton) {
				sf::Vector2i size = barButton->getTextureRect().size;
				if (decreaseButton and increaseButton) {
					sf::Vector2i decreaseSize = decreaseButton->getTextureRect().size;
					sf::Vector2i increaseSize = decreaseButton->getTextureRect().size;
					barButton->setPosition({ cachedWidth - size.x, (float)decreaseSize.y });
					scrollBarScrollLength = cachedHeight - decreaseSize.y - increaseSize.y - size.y;
				}
				else {
					barButton->setPosition({ cachedWidth - size.x, 0 });
				}

				sf::Vector2f position = barButton->getPosition();
				float percent = scrollPanel->scrollPercentage;
				scrollBarComponentLocations.scrollBarX = position.x + scrollPanel->x;
				scrollBarComponentLocations.scrollBarY = position.y + scrollPanel->y + scrollBarScrollLength * percent;
				scrollBarComponentLocations.scrollBarWidth = size.x;
				scrollBarComponentLocations.scrollBarHeight = size.y;
			}
			{
				sf::Vector2f size = barBackground.getSize();
				barBackground.setPosition({ cachedWidth - size.x, 0 });
				barBackground.setSize({ size.x, cachedHeight });
			}
			if (increaseButton) {
				sf::Vector2i size = increaseButton->getTextureRect().size;
				increaseButton->setPosition({ cachedWidth - size.x, cachedHeight - size.y });
				sf::Vector2f position = increaseButton->getPosition();
				scrollBarComponentLocations.scrollIncreaseX = position.x + scrollPanel->x;
				scrollBarComponentLocations.scrollIncreaseY = position.y + scrollPanel->y;
				scrollBarComponentLocations.scrollIncreaseWidth = size.x;
				scrollBarComponentLocations.scrollIncreaseHeight = size.y;
			}

			scrollPanel->scrollBarComponentLocations = scrollBarComponentLocations;
		}

		void ScrollPanelRenderer::update() {
			setPosition({ scrollPanel->x, scrollPanel->y });

			if (scrollPanel->visibleWidth != cachedWidth or scrollPanel->visibleHeight != cachedHeight) {
				onSizeUpdate();
			}

			sf::RenderStates states;
			float scrollableHeight = scrollPanel->maxHeight - scrollPanel->visibleHeight;
			float percent = scrollPanel->scrollPercentage;
			states.transform.translate({ 0, -scrollableHeight * percent });

			sf::RenderStates scrollBarStates;
			scrollBarStates.transform.translate({ 0, scrollBarScrollLength * percent });
			scrollPanel->scrollBarComponentLocations.scrollBarY = barButton->getPosition().y + scrollPanel->y + scrollBarScrollLength * percent;

			renderTexture.clear();

			for (auto& element : scrollPanel->elements) {
				std::weak_ptr<Renderable>& renderable = element.second;
				if (auto spRenderable = renderable.lock()) {
					if (auto spRenderer = spRenderable->renderer.lock()) {
						renderTexture.draw(*spRenderer.get(), states);
					}
				}
			}

			if (barButton) {
				renderTexture.draw(barBackground);
			}
			if (barButton) {
				renderTexture.draw(*barButton.get(), scrollBarStates);
			}
			if (increaseButton) {
				renderTexture.draw(*increaseButton.get());
			}
			if (decreaseButton) {
				renderTexture.draw(*decreaseButton.get());
			}

			renderTexture.display();

			sprite.setTexture(renderTexture.getTexture(), true);
		}

		void ScrollPanelRenderer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
			states.transform *= getTransform();
			target.draw(sprite, states);
		}

	} // namespace gui
} // namespace o2
