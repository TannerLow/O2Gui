#pragma once
#include <SFML/Graphics.hpp>
#include "Font.h"
#include <map>
#include "Renderer.h"
#include "Text.h"


namespace o2 {
	namespace gui {

		class TextRenderer : public Renderer {
		protected:
			struct VertexArrayInfo {
				sf::VertexArray vertices;
				const sf::Texture* texture;
				size_t quadPosition = 0;
				size_t charCount = 0;
			};

			std::shared_ptr<Text> text;
			std::weak_ptr<Font> font;
			sf::String textStr;
			std::unordered_map<int, VertexArrayInfo> vertexArrays;
			float lineSpacing = 2;
			float wrapWidth = 0;
			sf::FloatRect boundingBox;
			std::unordered_map<size_t, Color> colors;

		public:
			TextRenderer() {}
			TextRenderer(std::shared_ptr<Text>& text, std::weak_ptr<Font> font);

			void setString(sf::String textStr);
			void setWrapWidth(float wrapWidth);
			sf::FloatRect getBoundingBox() const;
			sf::Vector2f getCenter() const;
			void update() override;

		protected:
			// void renderWithTextureUpdates(); Maybe some optimization I can do if I need to update text colors without changing positions or texCoords
			void render();
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		};

	} // namespace gui
} // namespace o2

