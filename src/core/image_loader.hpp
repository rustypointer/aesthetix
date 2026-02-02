#pragma once
#include "color.hpp"
#include <string>
#include <vector>

namespace core {
class ImageLoader {
public:
  static std::vector<Color> LoadImageGrid(const std::string &path, int grid_w,
                                          int grid_h);
};
} // namespace core
