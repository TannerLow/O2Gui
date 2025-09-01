#include "Font.h"
#include <fstream>
#include <sstream>


bool Font::load(
	const sf::Vector2u charSize,
	const sf::Vector2u charsPerImageDimension,
	const fs::path& fontWidthFile,
	std::map<int, fs::path> imagePaths
) {
	this->charSize = charSize;
	this->charsPerImageDimension = charsPerImageDimension;
	this->imagePaths = imagePaths;
	this->charactersPerImage = charsPerImageDimension.x * charsPerImageDimension.y;

	std::ifstream fontWidthFileHandle(fontWidthFile, std::ios::binary);
	if (!fontWidthFileHandle.is_open()) {
		printf("Unable to load font width file: %s\n", fontWidthFile.string().c_str());
		fontWidthFileHandle.close(); // just in case
		return false;
	}

	std::stringstream buffer;
	buffer << fontWidthFileHandle.rdbuf();
	fontWidthFileHandle.close();
	std::string charWidthData = buffer.str();

	//charWidths.reserve(charWidthData.size());
	//for (auto charIter = charWidthData.cbegin(); charIter != charWidthData.cend(); charIter++) {
	//	charWidths.push_back(uint8_t(*charIter));
	//}
	charWidths = std::vector<uint8_t>(charWidthData.begin(), charWidthData.end());

	textureData.resize(imagePaths.size());
	int i = 0;
	for (auto it = imagePaths.begin(); it != imagePaths.end(); it++) {
		int texId = it->first;
		if (!textureData[i].loadFromFile(it->second)) {
			printf("Failed to load texture from file: %d\n", i);
			textures[texId] = nullptr;
		}
		else {
			textures[texId] = &textureData[i];
		}
		i++;
	}

	loaded = true;
	return true;
}

const sf::IntRect Font::getCharacter(unsigned int code) const {
	sf::IntRect texRect;
	if (!loaded) {
		return texRect;
	}

	uint8_t charWidth = charWidths[code];

	code %= charactersPerImage;
	int right = charWidth & 0x0F;
	int left = ((charWidth & 0xF0) >> 4) & 0x0F;
	return {
		{(int)(code % charsPerImageDimension.x * charSize.x) + left, (int)(code / charsPerImageDimension.y * charSize.y)},
		{right - left + 1, (int)charSize.y}
	};
}

const sf::Texture* Font::getTexture(unsigned int code) {
	if (!loaded) {
		return nullptr;
	}

	int texId = code / charactersPerImage;

	auto it = textures.find(texId);
	if (it == textures.end()) {
		return nullptr;
	}

	return it->second;
}

int Font::numberOfCharactersPerTexture() const {
	if (!loaded) {
		return 0;
	}
	return charactersPerImage;
}

bool Font::isLoaded() const {
	return loaded;
}