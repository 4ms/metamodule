/*
 * sts_filesystem.c - Bank and folder system for STS
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
#include "bank.hh"
#include "ff.h"
#include "flags.hh"
#include "palette.hh"
#include "sample_file.hh"
#include "sdcard.hh"
#include "sts_sampleindex.hh"

namespace SamplerKit
{

// TODO: constexpr these, move them into SampleBankFiles

#define RENAME_TMP_FILE "sts-renaming-queue.tmp"
#define ERROR_LOG_FILE "error-log.txt"
#define SETTINGS_FILE "settings.txt"

struct SampleIndexLoader {

	SampleIndexLoader(Sdcard &sd, SampleList &samples, BankManager &banks, Flags &flags)
		: sd{sd}
		, samples{samples}
		, banks{banks}
		, index{samples, flags, sd}
		, flags{flags} {
	}

	void load_new_folders();
	void load_missing_files();

	uint8_t load_banks_by_color_prefix();
	uint8_t load_banks_by_default_colors();
	uint8_t load_banks_with_noncolors();

	uint8_t load_all_banks(bool force_reload = false);

	uint8_t load_bank_from_disk(Bank &sample_bank, char *path_noslash);

	uint8_t dir_contains_assigned_samples(const char *path);

	uint8_t write_index_and_html();

	void handle_events();

private:
	Sdcard &sd;
	SampleList &samples;
	BankManager &banks;
	SampleIndex index;
	Flags &flags;

	bool index_needs_writeback = false;

	void load_empty_slots();
};
} // namespace SamplerKit
