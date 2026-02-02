#include "plugin_loader.hpp"
#include "json.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>

using json = nlohmann::json;
namespace fs = std::filesystem;

namespace core {
std::vector<Plugin>
PluginLoader::LoadFromDirectory(const std::string &plugins_dir) {
  std::vector<Plugin> plugins;

  // std::cout << "plugins directory : " << plugins_dir << std::endl;

  if (!fs::exists(plugins_dir)) {
    std::cout << "plugins dir doesn't exists" << std::endl;
    return plugins;
  }

  for (const auto &entry : fs::directory_iterator(plugins_dir)) {
    // std::cout << "entry : " << entry << std::endl;
    if (!entry.is_directory()) {
      continue;
    }

    fs::path plugin_dir = entry.path();
    fs::path manifest_path = plugin_dir / "manifest.json";

    if (!fs::exists(manifest_path)) {
      continue;
    }

    json j;
    try {
      std::ifstream file(manifest_path);
      file >> j;
    } catch (...) {
      std::cerr << "Failed to parse " << manifest_path << "\n";
      continue;
    }

    // validate minimal fields
    if (!j.contains("name") || !j.contains("apply") || !j.contains("colors")) {
      continue;
    }

    // read fields
    std::string name = j["name"].get<std::string>();

    std::vector<std::string> color_roles;
    for (const auto &role : j["colors"]) {
      color_roles.push_back(role.get<std::string>());
    }

    fs::path apply_rel = j["apply"].get<std::string>();
    fs::path apply_abs = plugin_dir / apply_rel;

    if (!fs::exists(apply_abs)) {
      std::cerr << "Apply script missing: " << apply_abs << "\n";
      continue;
    }

    // construct plugin
    plugins.emplace_back(name, std::move(color_roles),
                         fs::absolute(apply_abs).string());
  }

  return plugins;
}
} // namespace core
