#pragma once
#include <vector>
#include <SFML/Window.hpp>
#include <functional>

namespace o2 {
	namespace gui {

		class EventBroadcaster {
		public:
			std::vector<std::function<void(char)>> textEnteredListeners;

		public:
			void registerTextListener(std::function<void(char)> callback);
			void broadcastEvent(const sf::Event::TextEntered* textEnteredEvent);
		};

	} // namespace gui
} // namespace o2