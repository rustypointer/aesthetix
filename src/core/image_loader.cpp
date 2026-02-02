#include "image_loader.hpp"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace core {
std::vector<Color> ImageLoader::LoadImageGrid(const std::string &path,
                                              int grid_w, int grid_h) {
  int width, height, channels;
  unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 3);

  if (!data) {
    std::cerr << "Failed to load image : " << path << "\n";
    return {};
  }

  std::vector<Color> result;
  result.reserve(grid_w * grid_h);

  // downscale sampling
  for (int y = 0; y < grid_h; y++) {
    for (int x = 0; x < grid_w; x++) {
      int src_x = x * width / grid_w;
      int src_y = y * height / grid_h;

      int ind = (src_y * width + src_x) * 3;

      result.push_back({
          data[ind + 0],
          data[ind + 1],
          data[ind + 2],
      });
    }
  }

  stbi_image_free(data);
  return result;
}
} // namespace core
