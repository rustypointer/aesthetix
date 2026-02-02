#pragma once
#include "state/app_state.hpp"
#include <ftxui/component/component_base.hpp>

namespace tui {
class SaveButton : public ftxui::ComponentBase {
public:
  explicit SaveButton(state::AppState &state);

  bool Focusable() const override;
  ftxui::Element Render() override;
  bool OnEvent(ftxui::Event event) override;

private:
  state::AppState &state_;
};
} // namespace tui
