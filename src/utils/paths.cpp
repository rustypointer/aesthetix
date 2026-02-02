#include "paths.hpp"
#include <cstdlib>
#include <stdexcept>
#include <system_error>

namespace utils {
std::filesystem::path getConfigDir() {
  if (const char *xdg = std::getenv("XDG_CONFIG_HOME")) {
    return std::filesystem::path(xdg) / "aesthetix";
  }

  if (const char *home = std::getenv("HOME")) {
    return std::filesystem::path(home) / ".config" / "aesthetix";
  }

  throw std::runtime_error("Neither XDG_CONFIG_HOME nor HOME is set");
}

std::filesystem::path getPluginsDir() { return getConfigDir() / "plugins"; }

void ensureConfigDirs() {
  namespace fs = std::filesystem;

  std::error_code ec;
  fs::create_directories(getPluginsDir(), ec);

  if (ec) {
    throw std::runtime_error("Failed to create config directories: " +
                             getPluginsDir().string());
  }
}
} // namespace utils
