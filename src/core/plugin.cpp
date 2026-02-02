#include "plugin.hpp"
#include "color.hpp"
#include "json.hpp"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <sstream>

namespace core {
Plugin::Plugin(std::string label, std::vector<std::string> colorRoles,
               std::string apply_abs_path)
    : name_(std::move(label)), color_roles_(std::move(colorRoles)),
      apply_abs_path_(std::move(apply_abs_path)),
      color_roles_values_(color_roles_.size(), std::nullopt) {

  // map color roles to their index in color role list
  for (std::size_t i = 0; i < color_roles_.size(); i++) {
    color_roles_map_[color_roles_[i]] = i;
  }
}

const std::string &Plugin::getPluginName() const { return name_; }

const std::vector<std::string> &Plugin::getPluginColorRoles() const {
  return color_roles_;
}

const Color *Plugin::getColorForRoleIndex(int index) const {
  if (index < 0 || index >= (int)color_roles_values_.size()) {
    return nullptr;
  }

  const auto &opt = color_roles_values_[index];
  return opt ? &opt.value() : nullptr;
}

void Plugin::setColor(const std::string &colorRole, const Color &color) {
  auto it = color_roles_map_.find(colorRole);
  if (it == color_roles_map_.end()) {
    return;
  }
  color_roles_values_[it->second] = color;
}

void Plugin::resetColor(const std::string &colorRole) {
  auto it = color_roles_map_.find(colorRole);
  if (it == color_roles_map_.end()) {
    return;
  }
  color_roles_values_[it->second] = std::nullopt;
}

void Plugin::resetAllColors() {
  for (auto &color : color_roles_values_) {
    color = std::nullopt;
  }
}

bool Plugin::allColorRolesSet() const {
  for (const auto &val : color_roles_values_) {
    if (!val.has_value()) {
      return false;
    }
  }
  return true;
}

bool Plugin::savePlugin() const {
  using json = nlohmann::json;
  namespace fs = std::filesystem;

  const char *home = std::getenv("HOME");
  if (!home) {
    return false;
  }

  fs::path out_dir = fs::path(home) / ".cache/aesthetix/output";
  fs::path out_file = out_dir / "colors.json";

  // ensure directory exists
  std::error_code ec;
  fs::create_directories(out_dir, ec);
  if (ec) {
    return false;
  }

  json j;
  j["colors"] = json::object();

  for (const auto &[role, index] : color_roles_map_) {
    if (index < 0 || index >= (int)color_roles_values_.size()) {
      continue;
    }
    const auto &opt_color = color_roles_values_[index];
    if (!opt_color.has_value()) {
      continue;
    }
    j["colors"][role] = opt_color.value().ToHex();
  }

  // write json
  std::ofstream ofs(out_file);
  if (!ofs.is_open()) {
    return false;
  }

  ofs << j.dump(2);
  ofs.close();

  // run apply script
  if (!apply_abs_path_.empty()) {
    std::string cmd = apply_abs_path_ + " " + out_file.string();
    int ret = std::system(cmd.c_str());
    if (ret != 0) {
      return false;
    }
  }
  return true;
}
} // namespace core
