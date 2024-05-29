#pragma once
#include "patch/patch.hh"
#include "patch/patch_data.hh"
#include <span>

namespace MetaModule
{

bool yaml_raw_to_patch(std::span<char> yaml, PatchData &pd);
bool yaml_raw_to_patch(char *yaml, size_t size, PatchData &pd);
bool yaml_string_to_patch(std::string yaml, PatchData &pd);

} // namespace MetaModule
