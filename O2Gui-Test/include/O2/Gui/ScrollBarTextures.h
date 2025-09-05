#pragma once
#include <filesystem>
#include <optional>

namespace fs = std::filesystem;

namespace o2 {
	namespace gui {

		struct ScrollBarTextures {
			std::optional<fs::path> decrease;
			fs::path bar;
			fs::path barBackground;
			std::optional<fs::path> increase;
		};

	} // namespace gui
} // namespace o2

