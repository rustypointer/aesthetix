#pragma once
#include "state/app_state.hpp"
#include <ftxui/component/component_base.hpp>

namespace tui {
class PluginList : public ftxui::ComponentBase {
public:
  explicit PluginList(state::AppState &state);

  bool Focusable() const override;
  ftxui::Element Render() override;
  bool OnEvent(ftxui::Event event) override;

private:
  state::AppState &state_;
};
} // namespace tui
