#pragma once
#include <string>
#include <string_view>

namespace rack::plugin
{
struct Plugin;
} // namespace rack::plugin

namespace rack::asset
{

std::string system(std::string_view filename = "");
std::string user(std::string_view filename = "");
std::string plugin(plugin::Plugin *plugin, std::string_view filename = "");

extern std::string systemDir;
extern std::string userDir;
extern std::string bundlePath;

} // namespace rack::asset
