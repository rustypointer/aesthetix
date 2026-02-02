#pragma once
#include "color.hpp"
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace core {
class Plugin {
public:
  Plugin(std::string label, std::vector<std::string> colorRoles,
         std::string apply_abs_path);

  const std::string &getPluginName() const;
  const std::vector<std::string> &getPluginColorRoles() const;
  const Color *getColorForRoleIndex(int index) const;

  void setColor(const std::string &colorRole, const Color &c);
  void resetColor(const std::string &colorRole);
  void resetAllColors();
  bool allColorRolesSet() const;
  bool savePlugin() const;

private:
  std::string name_;

  // stores list of color roles from the plugin json
  std::vector<std::string> color_roles_;

  // stores the values selected by the user for each color role
  std::vector<std::optional<Color>> color_roles_values_;

  // absolute path for the apply script of the plugin
  std::string apply_abs_path_;

  // map of color role to its index in color roles list
  std::unordered_map<std::string, int> color_roles_map_;
};
} // namespace core
