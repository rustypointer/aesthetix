#include "color.hpp"
#include <sstream>

namespace core {
Color Color::FromHex(const std::string &hex) {
  unsigned int r, g, b;
  sscanf(hex.c_str() + 1, "%02x%02x%02x", &r, &g, &b);
  return {(uint8_t)r, (uint8_t)g, (uint8_t)b};
}

std::string Color::ToHex() const {
  char buf[8];
  snprintf(buf, sizeof(buf), "#%02x%02x%02x", r, g, b);
  return buf;
}
} // namespace core
