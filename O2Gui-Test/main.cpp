#include <SFML/Graphics.hpp>
#include "GraphicsManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1000, 800 }), "SFML works!");

    GraphicsManager graphicsManager;
    
    auto button = graphicsManager.createButton();
    button->x = 10;
    button->y = 20;
    button->width = 200;
    button->height = 100;
    button->render();

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(graphicsManager);
        window.display();
    }
}