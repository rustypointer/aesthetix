#include "save_button.hpp"
#include "core/plugin.hpp"
#include <ftxui/component/event.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

namespace tui {
SaveButton::SaveButton(state::AppState &state) : state_(state) {}

bool SaveButton::Focusable() const { return true; }

Element SaveButton::Render() {
  Element button;
  button = text("[SAVE]") | bold | hcenter | vcenter | border;

  auto *plugin = state_.currentPlugin();
  if (!plugin || !plugin->allColorRolesSet()) {
    button |= dim;
  }

  if (Focused()) {
    button |= color(Color::Yellow);
  }

  return button;
}

bool SaveButton::OnEvent(Event e) {
  if (e == Event::Return) {
    auto *plugin = state_.currentPlugin();
    if (plugin && plugin->allColorRolesSet()) {
      plugin->savePlugin();
      return true;
    }
  }
  return false;
}
} // namespace tui
