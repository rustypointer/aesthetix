#pragma once
#include "plugin.hpp"
#include <string>
#include <vector>

namespace core {
class PluginLoader {
public:
  static std::vector<Plugin> LoadFromDirectory(const std::string &plugins_dir);
};
} // namespace core
