#include "color_roles_list.hpp"
#include "core/color.hpp"
#include <ftxui/component/event.hpp>
#include <ftxui/dom/elements.hpp>
#include <vector>

using namespace ftxui;

namespace tui {
ColorRolesList::ColorRolesList(state::AppState &state) : state_(state) {}

bool ColorRolesList::Focusable() const { return true; }

Element ColorRolesList::Render() {
  std::vector<Element> items;

  auto *plugin = state_.currentPlugin();

  if (!plugin) {
    items.push_back(text("No plugin selected") | dim);
  } else {
    const auto &roles = plugin->getPluginColorRoles();

    for (int i = 0; i < (int)roles.size(); i++) {
      bool selected = (i == state_.selected_color_role_index);

      Element selector = selected ? text("> ") | bold : text("  ");
      Element roleName = text(roles[i]) | size(WIDTH, EQUAL, 14);

      const core::Color *c = plugin->getColorForRoleIndex(i);

      Element colorBox;
      Element colorText;

      if (c) {
        colorBox = text(" ") | bgcolor(Color::RGB(c->r, c->g, c->b)) |
                   size(WIDTH, EQUAL, 3);

        colorText = text(c->ToHex());
      } else {
        colorBox = text("   ") | dim;
        colorText = text("none") | dim;
      }

      auto line =
          hbox({selector | (selected ? inverted : nothing),
                roleName | (selected ? inverted : nothing), text(" "), colorBox,
                text(" "), colorText | (selected ? inverted : nothing)});

      items.push_back(line);
    }
  }

  auto content =
      std::vector<Element>({text("Color Roles") | center, separator()});

  content.insert(content.end(), items.begin(), items.end());

  auto box = vbox(content) | border | size(HEIGHT, EQUAL, 18);

  if (Focused()) {
    box |= color(Color::Yellow);
  }

  // box |= color(Focused() ? Color::White : Color::GrayDark);

  return box;
}

bool ColorRolesList::OnEvent(Event e) {
  if (e == Event::Character('w')) {
    state_.selectPrevColorRole();
    return true;
  }

  if (e == Event::Character('s')) {
    state_.selectNextColorRole();
    return true;
  }

  if (e == Event::Character('r')) {
    auto *plugin = state_.currentPlugin();
    if (plugin) {
      std::string currColorRole =
          plugin->getPluginColorRoles()[state_.selected_color_role_index];
      plugin->resetColor(currColorRole);
    }
    return true;
  }

  return false;
}
} // namespace tui
