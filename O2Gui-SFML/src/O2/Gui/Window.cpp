#include <O2/Gui/Window.h>
#include <SFML/Graphics.hpp>
#include <cassert>

namespace o2 {
	namespace gui {

        struct Window::Impl {
            sf::RenderWindow window;
        };

        Window::Window(unsigned int width, unsigned int height, const std::string& title, bool fullscreen) {
            impl = std::make_unique<Impl>();
            impl->window.create(
                sf::VideoMode({width, height}), 
                title, 
                fullscreen ? sf::State::Fullscreen : sf::State::Windowed
            );
        }

        Window::~Window() = default;

        bool Window::isOpen() const {
            return impl->window.isOpen();
        }

        void Window::pollEvents() {
            while (const std::optional event = impl->window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                    impl->window.close();
            }
            //assert(false && "Not implemented");
        }

        void Window::clear() {
            impl->window.clear();
        }

        void Window::draw() {
            for (const auto& element : elements) {
                assert(element != nullptr);
                element->draw();
            }
        }

        void Window::display() {
            impl->window.display();
        }

        void Window::addElement(std::shared_ptr<UIElement>& element) {
            elements.push_back(element);
        }

	} // namespace gui
} // namespace o2
