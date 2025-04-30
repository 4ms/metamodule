#include "fs/volumes.hh"
#include <map>
#include <string>
#include <string_view>

namespace MetaModule
{

namespace
{
std::map<Volume, std::string> roots;
}

void register_volume_host_path(Volume vol, std::string_view path) {
	roots[vol] = std::string(path);
	printf("Registered vol %d with path '%s'\n", (int)vol, path.data());
}

std::map<Volume, std::string> get_volume_host_paths() {
	return roots;
}

} // namespace MetaModule
