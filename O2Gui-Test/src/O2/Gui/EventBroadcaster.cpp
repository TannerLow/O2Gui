#include <O2/Gui/EventBroadcaster.h>

namespace o2 {
	namespace gui {

		void EventBroadcaster::registerTextListener(std::function<void(char)> callback) {
			textEnteredListeners.emplace_back(callback);
		}

		void EventBroadcaster::broadcastEvent(const sf::Event::TextEntered* textEnteredEvent) {
			char c = static_cast<char>(textEnteredEvent->unicode);
			for (auto& callback : textEnteredListeners) {
				callback(c);
			}
		}

	} // namespace gui
} // namespace o2
