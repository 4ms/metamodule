/*
 * banks.c - bank functions (naming, enabling, and more)
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

#include "sample_file.hh"

namespace SamplerKit
{
struct BankManager {
	uint8_t bank_status[MaxNumBanks];

	BankManager(SampleList &samples)
		: samples{samples} {
	}

	//?? These use samples:
	SampleList &samples;
	void bump_down_banks(uint8_t bank);
	void copy_bank(Bank &dst, const Bank &src);
	uint8_t get_bank_path(uint8_t bank, char *path);
	uint8_t find_filename_in_bank(uint8_t bank, const char *filename);
	uint8_t find_filename_in_all_banks(uint8_t bank, const char *filename);

	// These use bank_status:
	uint8_t next_bank(uint8_t bank);
	uint8_t next_enabled_bank(uint8_t bank);
	uint8_t next_enabled_bank_0xFF(uint8_t bank);
	uint8_t next_disabled_bank(uint8_t bank);

	uint8_t prev_bank(uint8_t bank);
	uint8_t prev_enabled_bank(uint8_t bank);
	uint8_t prev_enabled_bank_0xFF(uint8_t bank);
	uint8_t prev_disabled_bank(uint8_t bank);

	void check_enabled_banks();
	bool is_bank_enabled(uint8_t bank);
	void enable_bank(uint8_t bank);
	void disable_bank(uint8_t bank);

	// void init_banks();
};

} // namespace SamplerKit
