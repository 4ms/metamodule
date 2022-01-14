#pragma once
#include "patch/patch.hh"
#include "ryml_all.hpp"

void write(ryml::NodeRef *n, Jack const &jack);
void write(ryml::NodeRef *n, PatchHeader const &ph);
