#pragma once
#include "core/color.hpp"
#include "state/app_state.hpp"
#include <ftxui/component/component_base.hpp>
#include <vector>

namespace tui {
class ColorGrid : public ftxui::ComponentBase {
public:
  ColorGrid(std::vector<core::Color> colors, int columns,
            state::AppState &state);

  bool Focusable() const override;
  ftxui::Element Render() override;
  bool OnEvent(ftxui::Event event) override;

private:
  std::vector<core::Color> colors_;
  state::AppState &state_;
  int columns_;
  int selected_ = 0;
};
} // namespace tui
