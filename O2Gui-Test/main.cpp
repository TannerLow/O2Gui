#include <SFML/Graphics.hpp>
#include "GraphicsManager.h"
#include <iostream>
#include <filesystem>
#include "ScrollDirection.h"
#include "ScrollBarTextures.h"
#include "RateLimiter.h"

namespace fs = std::filesystem;

void buttonClickedMessage() {
    std::cout << "Button Clicked" << std::endl;
}

int main() {
    RateLimiter drawLimiter(250);
    sf::RenderWindow window(sf::VideoMode({ 1000, 800 }), "SFML works!");

    GraphicsManager graphicsManager;
    
    auto button = graphicsManager.createButton();
    button->x = 10;
    button->y = 20;
    button->width = 200;
    button->height = 100;
    button->color = Color(sf::Color::Green);
    button->render();
    button->setOnClick(buttonClickedMessage);

    auto image = graphicsManager.createImage(fs::path("resources/double_shottys.png"));
    image->x = 0;
    image->y = 0;
    image->width = 200;
    image->height = 600;
    image->owned = true;
    image->render();

    auto temp = graphicsManager.createButton();
    temp->x = 390;
    temp->y = 290;
    temp->width = 220;
    temp->height = 220;
    temp->color = Color(sf::Color::Red);
    temp->render();

    ScrollBarTextures scrollBarTextures;
    scrollBarTextures.increase = fs::path("resources/gray_scroll_down.png");
    scrollBarTextures.bar = fs::path("resources/gray_scroll_bar.png");
    scrollBarTextures.barBackground = fs::path("resources/gray_scroll_bar_bg.png");
    scrollBarTextures.decrease = fs::path("resources/gray_scroll_up.png");
    auto scrollPanel = graphicsManager.createScrollPanel(scrollBarTextures);
    scrollPanel->x = 400;
    scrollPanel->y = 300;
    scrollPanel->maxHeight = 600;
    scrollPanel->visibleWidth = 200;
    scrollPanel->visibleHeight = 200;
    scrollPanel->elements["image"] = image;
    scrollPanel->render();

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
                    std::cout << "mouse click  : (" << mouseButtonPressed->position.x << ", " << mouseButtonPressed->position.y << ")" << std::endl;
                    sf::Vector2f coords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    button->handleClick(coords.x, coords.y);
                    scrollPanel->handleClick(coords.x, coords.y);
                }
            }
            else if (const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>()) {
                if (mouseButtonReleased->button == sf::Mouse::Button::Left) {
                    std::cout << "mouse release: (" << mouseButtonReleased->position.x << ", " << mouseButtonReleased->position.y << ")" << std::endl;
                    sf::Vector2f coords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    scrollPanel->handleClickRelease(coords.x, coords.y);
                }
            }
            else if (const auto* mouseWheelScrolled = event->getIf<sf::Event::MouseWheelScrolled>()) {
                ScrollDirection direction = ScrollDirection::DOWN;
                if (mouseWheelScrolled->delta > 0) {
                    direction = ScrollDirection::UP;
                }

                scrollPanel->handleScroll(direction);
            }
        }

        sf::Vector2f mouseCoords = sf::Vector2f(sf::Mouse::getPosition(window));
        scrollPanel->update(mouseCoords.x, mouseCoords.y);

        if (drawLimiter.isReady()) {
            window.clear();
            window.draw(graphicsManager);
            window.display();
        }
    }
}