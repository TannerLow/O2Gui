#pragma once
#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include "Button.h"
#include "ButtonRenderer.h"
#include "Image.h"
#include "ImageRenderer.h"
#include "ScrollPanel.h"
#include "ScrollPanelRenderer.h"
#include <filesystem>
#include <iostream>
#include <map>
#include "ScrollBarTextures.h"
#include "Font.h"
#include "TextRenderer.h"

namespace fs = std::filesystem;

class GraphicsManager : public sf::Drawable, public sf::Transformable {
public:
	std::vector<std::shared_ptr<Renderer>> renderers;
	std::map<fs::path, std::shared_ptr<sf::Texture>> textures;
	std::map<std::string, std::shared_ptr<Font>> fonts;

public:
	GraphicsManager() {}
	~GraphicsManager() = default;

	std::weak_ptr<Font> loadFont(
		const std::string& fontName,
		const sf::Vector2u charSize,
		const sf::Vector2u charsPerImageDimension,
		const fs::path& fontWidthFile,
		std::map<int, fs::path> imagePaths
	) {
		std::shared_ptr<Font> font = std::make_shared<Font>();
		
		if (!font->load(charSize, charsPerImageDimension, fontWidthFile, imagePaths)) {
			std::cout << "Failed to load font: " << fontName << std::endl;
			assert(false && "Failed to load font");
			exit(1);
			return std::weak_ptr<Font>();
		}

		fonts.emplace(fontName, font);
		return std::weak_ptr<Font>(font);
	}

	std::shared_ptr<Button> createButton() {
		std::shared_ptr<Button> button = std::make_shared<Button>();
		renderers.push_back(std::make_shared<ButtonRenderer>(button));
		button->renderer = std::weak_ptr<Renderer>(renderers.back());
		return button;
	}

	bool loadTexture(const fs::path& filepath) {
		if (textures.count(filepath) < 1) {
			textures[filepath] = std::make_shared<sf::Texture>();
			if (!textures[filepath]->loadFromFile(filepath)) {
				std::cout << "Failed to load image from file: " << filepath.string() << std::endl;
				assert(false && "Failed to load image from file");
				exit(1);
				return false;
			}
		}
		return true;
	}

	std::shared_ptr<Image> createImage(const fs::path& filepath) {
		if (!loadTexture(filepath)) {
			return nullptr;
		}

		std::shared_ptr<Image> image = std::make_shared<Image>();
		auto texture = std::weak_ptr<sf::Texture>(textures[filepath]);
		renderers.push_back(std::make_shared<ImageRenderer>(image, texture));
		image->renderer = std::weak_ptr<Renderer>(renderers.back());
		return image;
	}

	std::shared_ptr<ScrollPanel> createScrollPanel(const ScrollBarTextures& scrollBarTextures) {
		std::shared_ptr<ScrollPanel> scrollPanel = std::make_shared<ScrollPanel>();

		if (scrollBarTextures.decrease.has_value() and !loadTexture(scrollBarTextures.decrease.value())) {
			return nullptr;
		}
		if (!loadTexture(scrollBarTextures.bar)) {
			return nullptr;
		}
		if (!loadTexture(scrollBarTextures.barBackground)) {
			return nullptr;
		}
		if (scrollBarTextures.increase.has_value() and !loadTexture(scrollBarTextures.increase.value())) {
			return nullptr;
		}

		sf::Texture* decreaseTexture = nullptr;
		sf::Texture* barTexture = nullptr;
		sf::Texture* barBackgroundTexture = nullptr;
		sf::Texture* increaseTexture = nullptr;

		if (scrollBarTextures.decrease.has_value() and textures.count(scrollBarTextures.decrease.value()) > 0) {
			decreaseTexture = textures[scrollBarTextures.decrease.value()].get();
		}
		if (textures.count(scrollBarTextures.bar) > 0) {
			barTexture = textures[scrollBarTextures.bar].get();
		}
		if (textures.count(scrollBarTextures.barBackground) > 0) {
			barBackgroundTexture = textures[scrollBarTextures.barBackground].get();
		}
		if (scrollBarTextures.increase.has_value() and textures.count(scrollBarTextures.increase.value()) > 0) {
			increaseTexture = textures[scrollBarTextures.increase.value()].get();
		}

		renderers.push_back(
			std::make_shared<ScrollPanelRenderer>(
				scrollPanel,
				increaseTexture,
				barTexture,
				barBackgroundTexture,
				decreaseTexture
			)
		);
		scrollPanel->renderer = std::weak_ptr<Renderer>(renderers.back());

		return scrollPanel;
	}

	std::shared_ptr<Text> createText(const std::string& fontName) {
		auto it = fonts.find(fontName);
		if (it == fonts.end()) {
			std::cout << "Attempt to use unloaded font: " << fontName << std::endl;
			assert(false && "Font has not been loaded via GraphicsManager yet");
			return nullptr;
		}

		std::shared_ptr<Text> text = std::make_shared<Text>();
		renderers.push_back(std::make_shared<TextRenderer>(text, std::weak_ptr<Font>(it->second)));
		text->renderer = std::weak_ptr<Renderer>(renderers.back());
		return text;
	}

	void cleanOldRenderers() {
		// TODO implment a system of going thru the renderers and erasing any that are unique
	}

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		states.transform *= getTransform();
		for (const auto& renderer : renderers) {
			if (!renderer->owned) {
				target.draw(*renderer.get(), states);
			}
		}
	}
};