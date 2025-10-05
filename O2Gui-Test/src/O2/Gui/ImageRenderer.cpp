#include <O2/Gui/ImageRenderer.h>


namespace o2 {
	namespace gui {

		ImageRenderer::ImageRenderer(std::shared_ptr<Image>& image, std::weak_ptr<sf::Texture> texture) {
			this->image = image;
			if (auto sp = texture.lock()) {
				rectangle.setTexture(sp.get());
			}
		}

		void ImageRenderer::update() {
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

		bool ImageRenderer::containsPoint(float x, float y) const {
			return 
				image->x <= x                  and 
				x <= image->x + image->width   and
				image->y <= y                  and
				y <= image->y + image->height;
		}

		int ImageRenderer::getZIndex() const {
			return image->zIndex;
		}

		void ImageRenderer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
			states.transform *= getTransform();
			target.draw(rectangle, states);
		}

	} // namespace gui
} // namespace o2
