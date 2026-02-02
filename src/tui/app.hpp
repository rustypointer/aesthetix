#pragma once
#include "core/color.hpp"
#include "state/app_state.hpp"
#include <ftxui/component/component.hpp>

namespace tui {
class App {
public:
  App(std::vector<core::Color> colors, const int grid_w);
  ftxui::Component Render();

private:
  state::AppState app_state_;

  ftxui::Component color_grid_;
  ftxui::Component plugin_list_comp_;
  ftxui::Component color_roles_list_comp_;
  ftxui::Component save_button_comp_;

  ftxui::Component container_;
  ftxui::Component main_layout_;

  ftxui::Element footer();
};
} // namespace tui
