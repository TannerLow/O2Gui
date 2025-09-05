#include <O2/Gui/Renderable.h>

namespace o2 {
	namespace gui {

		Renderable::~Renderable() = default;

		void Renderable::render() {
			if (auto sp = renderer.lock()) {
				sp->update();
			}
		}

	} // namespace gui
} // namespace o2
