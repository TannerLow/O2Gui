#pragma once
#include <SFML/Graphics.hpp>
#include "Image.h"
#include "Renderer.h"


namespace o2 {
	namespace gui {

		class ImageRenderer : public Renderer {
		protected:
			std::shared_ptr<Image> image;
			sf::RectangleShape rectangle;

		public:
			ImageRenderer(std::shared_ptr<Image>& image, std::weak_ptr<sf::Texture> texture);

			void update() override;

		protected:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		};

	} // namespace gui
} // namespace o2
