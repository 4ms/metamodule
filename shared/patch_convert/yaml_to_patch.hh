#pragma once
#include <patch.hh>
#include <patch_data.hh>
#include <span>

bool yaml_raw_to_patch(std::span<char> yaml, PatchData &pd);
bool yaml_raw_to_patch(char *yaml, size_t size, PatchData &pd);
bool yaml_string_to_patch(std::string yaml, PatchData &pd);
