#pragma once
#include <filesystem>
#include <optional>

namespace fs = std::filesystem;

struct ScrollBarTextures {
	std::optional<fs::path> decrease;
	fs::path bar;
	fs::path barBackground;
	std::optional<fs::path> increase;
};
