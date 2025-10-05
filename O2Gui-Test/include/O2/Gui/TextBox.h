#pragma once
#include "Renderable.h"
#include "Color.h"
#include "Text.h"
#include "EventBroadcaster.h"

namespace o2 {
	namespace gui {
		
		class TextBox : public Renderable {
		public:
			float x;
			float y;
			float width;
			float height;
			float textScale = 1.f;
			int zIndex = 0;
			bool clicked = false;

			std::shared_ptr<Text> text;
			std::shared_ptr<EventBroadcaster> eventBroadcaster;

		public:
			void onClick(float x, float y, MouseButton mouseButton);
			void onClickRelease(float x, float y, MouseButton mouseButton);
			void onTextEntered(char c);

			// similar to ctrl + backspace in notepad
			void deleteLastWord(bool rerender = false);
		};

	} // namespace gui
} // namespace o2
