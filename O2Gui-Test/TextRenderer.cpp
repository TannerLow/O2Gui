#include "TextRenderer.h"
#include "Util/VertexHelper.h"
#include <set>
#include <iostream>

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
	for (int i = 0; i < textStr.getSize(); i++) {
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
	setString(text->text);
	owned = text->owned;
	render();
}
