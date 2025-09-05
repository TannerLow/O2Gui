#include <O2/Gui/TextRenderer.h>
#include <O2/Util/VertexHelper.h>
#include <set>
#include <iostream>


namespace o2 {
	namespace gui {

		TextRenderer::TextRenderer(std::shared_ptr<Text>& text, std::weak_ptr<Font> font) {
			this->text = text;
			this->font = font;
		}

		void TextRenderer::render() {
			boundingBox = sf::FloatRect();
			vertexArrays.clear();

			std::unordered_map<int, size_t> charCounts;

			auto fontPtr = font.lock();
			if (!fontPtr) {
				std::cout << "TextRenderer Font pointer is invalid" << std::endl;
				assert(false && "Cant render text with no font");
				return;
			}

			for (int i = 0; i < textStr.getSize(); i++) {
				int texId = textStr[i] / fontPtr->numberOfCharactersPerTexture();
				auto it = vertexArrays.find(texId);
				if (it == vertexArrays.end()) {
					VertexArrayInfo info;
					vertexArrays[texId] = info;
					vertexArrays[texId].vertices = sf::VertexArray(sf::PrimitiveType::Triangles);
					vertexArrays[texId].texture = fontPtr->getTexture(textStr[i]);
				}

				// we will skip rendering an actual quad for newlines
				if (textStr[i] != '\n') {
					vertexArrays[texId].charCount++;
				}
			}

			for (auto& info : vertexArrays) {
				info.second.vertices.resize(info.second.charCount * 6);
			}

			sf::Vector2f nextCharPos = { 0, 0 };
			sf::Color color;
			for (int i = 0; i < textStr.getSize(); i++) {
				auto it = colors.find(i);
				if (it != colors.end()) {
					color = sf::Color(
						it->second.r,
						it->second.g,
						it->second.b,
						it->second.a
					);
				}
				const sf::IntRect texCoords = fontPtr->getCharacter(textStr[i]);

				if (textStr[i] == '\n') {
					nextCharPos.y += texCoords.size.y + lineSpacing;
					nextCharPos.x = 0;
					continue;
				}

				if (wrapWidth != 0 and nextCharPos.x + texCoords.size.x > wrapWidth) {
					nextCharPos.y += texCoords.size.y + lineSpacing;
					nextCharPos.x = 0;
				}

				VertexArrayInfo& info = vertexArrays[textStr[i] / fontPtr->numberOfCharactersPerTexture()];
				vh::positionQuad(&info.vertices[info.quadPosition * 6], { nextCharPos, sf::Vector2f(texCoords.size) });
				vh::updateQuadTexture(&info.vertices[info.quadPosition * 6], texCoords);
				vh::colorQuad(&info.vertices[info.quadPosition * 6], color);
				info.quadPosition++;
				nextCharPos.x += texCoords.size.x + 2;

				if (nextCharPos.x - 2 > boundingBox.size.x) {
					boundingBox.size.x = nextCharPos.x - 2;
				}
				if (nextCharPos.y + texCoords.size.y > boundingBox.size.y) {
					boundingBox.size.y = nextCharPos.y + texCoords.size.y;
				}
			}
		}

		void TextRenderer::setString(sf::String textStr) {
			this->textStr = textStr;
			//render();
		}

		void TextRenderer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
			states.transform *= getTransform();

			for (const auto& info : vertexArrays) {
				states.texture = info.second.texture;
				target.draw(info.second.vertices, states);
			}
		}

		void TextRenderer::setWrapWidth(float wrapWidth) {
			this->wrapWidth = wrapWidth;
			//render();
		}

		sf::FloatRect TextRenderer::getBoundingBox() const {
			return getTransform().transformRect(boundingBox);
		}

		sf::Vector2f TextRenderer::getCenter() const {
			return getBoundingBox().size / 2.f;
		}

		void TextRenderer::update() {
			setPosition({ text->x, text->y });
			setScale({ text->scale, text->scale });
			colors = text->colors;
			setString(text->text);
			owned = text->owned;
			render();
		}

	} // namespace gui
} // namespace o2
