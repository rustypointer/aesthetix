#pragma once
#include <filesystem>

namespace utils {
// base config dir: ~/.config/aesthetix or $XDG_CONFIG_HOME/aesthetix
std::filesystem::path getConfigDir();

// plugin dir: <config>/plugins
std::filesystem::path getPluginsDir();

// ensure all required dirs exist
void ensureConfigDirs();
} // namespace utils
