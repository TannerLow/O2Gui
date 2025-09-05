#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
#include <stdint.h>
#include <map>
#include <filesystem>

namespace fs = std::filesystem;


namespace o2 {
	namespace gui {

		class Font {
		protected:
			// assumption that all images will be the same size
			std::vector<sf::Texture> textureData;
			std::map<int, sf::Texture*> textures;
			std::map<int, fs::path> imagePaths;
			sf::Vector2u charSize;
			sf::Vector2u charsPerImageDimension;
			std::vector<uint8_t> charWidths;
			bool loaded = false;
			unsigned int charactersPerImage;

		public:
			Font() {}

			bool load(
				const sf::Vector2u charSize,
				const sf::Vector2u charsPerImageDimension,
				const fs::path& fontWidthFile,
				std::map<int, fs::path> imagePaths
			);

			// assumes characters can only have a max width of 16
			const sf::IntRect getCharacter(unsigned int code) const;
			const sf::Texture* getTexture(unsigned int code);
			int numberOfCharactersPerTexture() const;
			bool isLoaded() const;
		};

	} // namespace gui
} // namespace o2
