#include "app_state.hpp"

namespace state {
core::Plugin *AppState::currentPlugin() {
  if (plugins.empty()) {
    return nullptr;
  }
  return &plugins[selected_plugin_index];
}

void AppState::selectPlugin(int index) {
  if (index < 0 || index >= (int)plugins.size()) {
    return;
  }
  selected_plugin_index = index;
  selected_color_role_index = 0;
}

void AppState::selectNextPlugin() { selectPlugin(selected_plugin_index + 1); }

void AppState::selectPrevPlugin() { selectPlugin(selected_plugin_index - 1); }

void AppState::selectColorRole(int index) {
  auto *p = currentPlugin();
  if (!p) {
    return;
  }

  int colorRolesSize = p->getPluginColorRoles().size();
  if (index < 0 || index >= colorRolesSize) {
    return;
  }
  selected_color_role_index = index;
}

void AppState::selectNextColorRole() {
  selectColorRole(selected_color_role_index + 1);
}

void AppState::selectPrevColorRole() {
  selectColorRole(selected_color_role_index - 1);
}

void AppState::applySelectedColorToRole() {
  auto *p = currentPlugin();
  if (!p || !selected_color) {
    return;
  }

  const auto &roles = p->getPluginColorRoles();
  if (selected_color_role_index < 0 ||
      selected_color_role_index >= (int)roles.size()) {
    return;
  }

  if (selected_color.has_value()) {
    p->setColor(roles[selected_color_role_index], selected_color.value());
  }
}
} // namespace state
