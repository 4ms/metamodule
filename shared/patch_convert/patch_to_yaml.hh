#pragma once
#include <patch.hh>
#include <patch_data.hh>
#include <span>

std::string patch_to_yaml_string(PatchData const &pd);

// Writes yaml to the given span
size_t patch_to_yaml_buffer(PatchData const &pd, std::span<char> &buffer);

std::string json_to_yml(std::string json);
