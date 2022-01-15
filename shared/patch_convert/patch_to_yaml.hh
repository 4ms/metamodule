#pragma once
#include "patch/patch.hh"
#include "patch_data.hh"

std::string patch_to_yaml_string(PatchHeader const &ph, PatchData const &pd);
