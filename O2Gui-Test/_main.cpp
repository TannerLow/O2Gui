#include <iostream>
#include <O2/Gui/UIElement.h>
#include <O2/Gui/Rectangle.h>
#include <O2/Gui/UIManager.h>
#include <O2/Gui/Window.h>
#include <memory>

#include "RateLimiter.h"
#include <iostream>

using namespace o2::gui;

int _main() {

	// limiter used to prevent using 100% GPU in release mode
	RateLimiter drawLimiter(250); // fps

	std::shared_ptr<UIElement> rectangle = std::make_shared<Rectangle>();
	rectangle->draw();
	rectangle->update();
	rectangle->handleEvent();

	Window window(1000, 800, "O2Gui Demo", false);
	window.addElement(rectangle);

	while (window.isOpen()) {
		window.pollEvents();
		if (drawLimiter.isReady()) {
			window.clear();
			window.draw();
			window.display();
		}
	}

	return 0;
}
