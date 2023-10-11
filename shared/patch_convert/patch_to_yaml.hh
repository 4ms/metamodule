#pragma once
#include "patch/patch.hh"
#include "patch/patch_data.hh"

std::string patch_to_yaml_string(PatchData const &pd);

std::string json_to_yml(std::string json);
