/*
 * sample_file.c - Handles filesystem stuff around sample (wav) files
 *
 * Author: Dan Green (danngreen1@gmail.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * See http://creativecommons.org/licenses/MIT/ for more information.
 *
 * -----------------------------------------------------------------------------
 */

#pragma once
#include "elements.hh"
#include "ff.h"
#include "sample_type.hh"
#include "sdcard.hh"
#include <array>

namespace SamplerKit
{

using Bank = std::array<Sample, NumSamplesPerBank>;
using SampleList = std::array<Bank, MaxNumBanks>;

constexpr auto SampleSize = sizeof(Sample);
constexpr auto SampleListSize = sizeof(SampleList);

FRESULT reload_sample_file(FIL *fil, Sample *s_sample, Sdcard &sd);
FRESULT create_dir(Sdcard &sd, DIR *dir, const char *dir_name);
FRESULT new_filename(uint8_t bank_idx, uint8_t sample_num, char *path, Sdcard &sd, Bank &bank);

} // namespace SamplerKit
