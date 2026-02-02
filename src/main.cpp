#include "core/image_loader.hpp"
#include "tui/app.hpp"
#include <ftxui/component/screen_interactive.hpp>
#include <iostream>

using namespace ftxui;

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "Usage: aesthetix <image-path>\n";
    return 1;
  }

  const std::string image_path = argv[1];

  const int grid_w = 150;
  const int grid_h = 37;

  auto colors = core::ImageLoader::LoadImageGrid(image_path, grid_w, grid_h);

  if (colors.empty()) {
    std::cerr << "Error: failed to load image: " << image_path << "\n";
    return 1;
  }

  auto screen = ScreenInteractive::Fullscreen();
  tui::App app(std::move(colors), grid_w);
  screen.Loop(app.Render());
  return 0;
}
