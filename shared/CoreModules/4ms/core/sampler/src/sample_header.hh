#pragma once
#include "ff.h"
#include "sample_type.hh"
#include <cstdint>

namespace SamplerKit
{
uint32_t load_sample_header(Sample *s_sample, FIL *sample_file);
}
