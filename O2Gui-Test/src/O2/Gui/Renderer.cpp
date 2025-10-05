#include <O2/Gui/Renderer.h>

namespace o2 {
	namespace gui {

		bool Renderer::operator<(const Renderer& other) const {
			return getZIndex() > other.getZIndex();
		}

	} // namespace gui
} // namespace o2
