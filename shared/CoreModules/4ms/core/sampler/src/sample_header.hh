#pragma once
#include "sample_type.hh"
#include "sdcard.hh"
#include <cstdint>

namespace SamplerKit
{
uint32_t load_sample_header(Sample *s_sample, FIL *sample_file, Sdcard &sd);
}
