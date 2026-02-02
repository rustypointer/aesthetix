#include "app.hpp"
#include "color_grid.hpp"
#include "color_roles_list.hpp"
#include "core/image_loader.hpp"
#include "core/plugin_loader.hpp"
#include "plugin_list.hpp"
#include "save_button.hpp"
#include "utils/paths.hpp"

using namespace ftxui;

namespace tui {
App::App(std::vector<core::Color> colors, const int grid_w) {

  utils::ensureConfigDirs();

  color_grid_ = Make<ColorGrid>(colors, grid_w, app_state_);

  app_state_.plugins = core::PluginLoader::LoadFromDirectory(
      "/home/arch/.config/aesthetix/plugins");

  plugin_list_comp_ = Make<PluginList>(app_state_);
  color_roles_list_comp_ = Make<ColorRolesList>(app_state_);
  save_button_comp_ = Make<SaveButton>(app_state_);

  auto vertCont = Container::Vertical(
      {plugin_list_comp_, color_roles_list_comp_, save_button_comp_});

  container_ = Container::Horizontal({color_grid_, vertCont});

  main_layout_ = Renderer(container_, [&] {
    return vbox({text("AESTHETIX") | center | bold,

                 hbox({
                     color_grid_->Render() | center | flex,

                     vbox({
                         plugin_list_comp_->Render(),
                         color_roles_list_comp_->Render(),
                         save_button_comp_->Render(),
                     }) | size(WIDTH, EQUAL, 32) |
                         flex,
                 }) | flex,

                 separator(),

                 footer()

           }) |
           bgcolor(Color::RGB(18, 18, 18)) | border |
           color(Color::RGB(88, 166, 255));
  });
}

Element App::footer() {
  Element preview;
  if (app_state_.selected_color.has_value()) {
    const auto &c = app_state_.selected_color.value();

    preview = hbox({text("Selected : ") | bold,
                    text("  ") | bgcolor(Color::RGB(c.r, c.g, c.b)) |
                        size(WIDTH, EQUAL, 5) | size(HEIGHT, EQUAL, 1),
                    text(" "), text(c.ToHex())});
  } else {
    preview = text("Selected : none") | bold;
  }

  return hbox({preview, filler() | flex,
               text("W/A/S/D: Move  | ←↑↓→: Focus  |  R: Reset   ") | dim});
}

Component App::Render() { return main_layout_; }
} // namespace tui
