#include "color_grid.hpp"
#include <algorithm>
#include <ftxui/component/event.hpp>
#include <ftxui/dom/elements.hpp>
#include <iostream>

using namespace ftxui;

namespace tui {
ColorGrid::ColorGrid(std::vector<core::Color> colors, int columns,
                     state::AppState &state)
    : colors_(std::move(colors)), columns_(columns), state_(state) {}

bool ColorGrid::Focusable() const { return true; }

Element ColorGrid::Render() {
  std::vector<Element> rows;

  int total = colors_.size();
  int rows_count = (total + columns_ - 1) / columns_;

  int index = 0;
  for (int r = 0; r < rows_count; r++) {
    std::vector<Element> row;

    for (int c = 0; c < columns_ && index < total; c++, index++) {
      const auto &col = colors_[index];

      Element cell = text(index == selected_ ? "#" : " ") |
                     bgcolor(Color::RGB(col.r, col.g, col.b)) |
                     size(WIDTH, EQUAL, 1) | size(HEIGHT, EQUAL, 1);

      row.push_back(cell);
    }

    rows.push_back(hbox(row));
  }

  auto ele = vbox(rows) | border;

  if (Focused()) {
    ele |= color(Color::Yellow);
  }
  return ele;
}

bool ColorGrid::OnEvent(Event e) {
  if (e == Event::Return) {
    state_.applySelectedColorToRole();
    return true;
  }

  bool moved = false;

  if (e == Event::Character('w')) {
    selected_ -= columns_;
    if (selected_ < 0) {
      selected_ = 0;
    }
    moved = true;
  }
  if (e == Event::Character('s')) {
    selected_ += columns_;
    if (selected_ >= (int)colors_.size()) {
      selected_ = colors_.size() - 1;
    }
    moved = true;
  }
  if (e == Event::Character('a')) {
    selected_--;
    if (selected_ < 0) {
      selected_ = 0;
    }
    moved = true;
  }
  if (e == Event::Character('d')) {
    selected_++;
    if (selected_ >= (int)colors_.size()) {
      selected_ = colors_.size() - 1;
    }
    moved = true;
  }

  selected_ = std::clamp(selected_, 0, (int)colors_.size() - 1);

  if (moved) {
    state_.selected_color = colors_[selected_];
    return true;
  }

  return false;
}
} // namespace tui
