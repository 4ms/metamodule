#pragma once
#include "patch/patch.hh"
#include "patch_data.hh"

bool yaml_string_to_patch(std::string yaml, PatchHeader &ph, PatchData &pd);
bool yaml_string_to_patchheader(std::string yaml, PatchHeader &ph);
