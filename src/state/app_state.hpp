#pragma once
#include "core/plugin.hpp"
#include <optional>
#include <vector>

namespace state {
struct AppState {
  std::vector<core::Plugin> plugins;

  int selected_plugin_index = 0;
  int selected_color_role_index = 0;

  std::optional<core::Color> selected_color;

  core::Plugin *currentPlugin();
  void selectPlugin(int index);
  void selectNextPlugin();
  void selectPrevPlugin();

  void selectColorRole(int index);
  void selectNextColorRole();
  void selectPrevColorRole();

  void applySelectedColorToRole();
};
} // namespace state
