#include "plugin_list.hpp"
#include <ftxui/component/event.hpp>
#include <ftxui/dom/elements.hpp>
#include <vector>

using namespace ftxui;

namespace tui {
PluginList::PluginList(state::AppState &state) : state_(state) {}

bool PluginList::Focusable() const { return true; }

Element PluginList::Render() {
  std::vector<Element> items;

  if (state_.plugins.empty()) {
    items.push_back(text("No plugins found") | dim);
  } else {
    for (int i = 0; i < (int)state_.plugins.size(); i++) {
      bool selected = (i == state_.selected_plugin_index);
      std::string pluginName = state_.plugins[i].getPluginName();
      std::string text_content =
          selected ? "> " + pluginName : "  " + pluginName;

      auto line = text(text_content);

      if (selected) {
        line |= inverted;
      }

      items.push_back(line);
    }
  }

  auto content = std::vector<Element>({text("Plugins") | center, separator()});

  content.insert(content.end(), items.begin(), items.end());

  auto box = vbox(content) | border | size(HEIGHT, EQUAL, 18);

  if (Focused()) {
    box |= color(Color::Yellow);
  }

  return box;
}

bool PluginList::OnEvent(Event e) {
  if (e == Event::Character('w')) {
    state_.selectPrevPlugin();
    return true;
  }

  if (e == Event::Character('s')) {
    state_.selectNextPlugin();
    return true;
  }

  if (e == Event::Character('r')) {
    auto *plugin = state_.currentPlugin();
    if (plugin) {
      plugin->resetAllColors();
    }
    return true;
  }

  return false;
}
} // namespace tui
