#pragma once
#include <cstdint>
#include <string>

namespace core {
struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;

  static Color FromHex(const std::string &hex);
  std::string ToHex() const;
};
} // namespace core
