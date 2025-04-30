#pragma once
#include "fs/volumes.hh"
#include <map>
#include <string_view>

namespace MetaModule
{

void register_volume_host_path(Volume vol, std::string_view);

std::map<Volume, std::string> get_volume_host_paths();

} // namespace MetaModule
