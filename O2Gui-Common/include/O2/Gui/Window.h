#pragma once
#include <string>
#include <memory>
#include "UIElement.h"
#include <vector>

namespace o2{
	namespace gui {

        class Window {
        protected:
            struct Impl;
            std::unique_ptr<Impl> impl;

            std::vector<std::shared_ptr<UIElement>> elements;

        public:
            Window(unsigned int width, unsigned int height, const std::string& title, bool fullscreen);
            ~Window();

            bool isOpen() const;
            void pollEvents();
            void clear();
            void draw();
            void display();

            void addElement(std::shared_ptr<UIElement>& element);
        };

	} // namespace gui
} // namespace o2