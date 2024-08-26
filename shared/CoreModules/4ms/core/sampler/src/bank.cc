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

#include "bank.hh"
#include "sample_file.hh"
#include "str_util.h"
#include "sts_filesystem.hh"

namespace SamplerKit
{

//
// Moving banks
//

void BankManager::copy_bank(Bank &dst, const Bank &src) {
	// TODO: =>memcpy
	uint8_t *p_dst;
	uint8_t *p_src;
	uint32_t i;

	p_dst = (uint8_t *)(dst.data());
	p_src = (uint8_t *)(src.data());
	for (i = 0; i < (sizeof(Sample) * NumSamplesPerBank); i++)
		*p_dst++ = *p_src++;
}

//
// Copy bank+40 to bank+50, bank+30 to bank+40, etc...
// The goal is to open up the given bank so we can place a new set of files in there
// FixMe: This must be changed manually if MaxNumBanks changes
//
void BankManager::bump_down_banks(uint8_t bank) {
	uint8_t t_bank;

	if (bank < 10) {
		copy_bank(samples[bank + 50], samples[bank + 40]);
		bank_status[bank + 50] = bank_status[bank + 40];
	}

	if (bank < 20) {
		copy_bank(samples[bank + 40], samples[bank + 30]);
		bank_status[bank + 40] = bank_status[bank + 30];
	}

	if (bank < 30) {
		copy_bank(samples[bank + 30], samples[bank + 20]);
		bank_status[bank + 30] = bank_status[bank + 20];
	}

	if (bank < 40) {
		copy_bank(samples[bank + 20], samples[bank + 10]);
		bank_status[bank + 20] = bank_status[bank + 10];
	}

	if (bank < 50) {
		copy_bank(samples[bank + 10], samples[bank]);
		bank_status[bank + 10] = bank_status[bank];
	}

	else
	{ // bank>=50 would get bumped out, so try to place it elsewhere
		t_bank = prev_disabled_bank(MaxNumBanks);
		copy_bank(samples[t_bank], samples[bank]);
		bank_status[t_bank] = bank_status[bank];
	}
}

///
/// Searching banks
///

//
// Returns the "predominant" path of the samples in a bank
// Todo: make go through all samples in the bank, and set path to the most common path
// For now, it sets path to the path of the first non-empty slot
// Returns 1 if path is set
// Returns 0 if no slots are filled
//
uint8_t BankManager::get_bank_path(uint8_t bank, char *path) {
	uint8_t samplenum;
	char tmp_filename[FF_MAX_LFN + 1];

	for (samplenum = 0; samplenum < NumSamplesPerBank; samplenum++) {
		if (samples[bank][samplenum].filename[0]) {
			if (str_split(samples[bank][samplenum].filename, '/', path, tmp_filename) == 0)
				path[0] = '\0'; // no slashes exist in filename, so path is the root dir

			// Todo untested code:
			// path_is_new = 1;
			// for (i=0;i<candidate_i;i++)
			// {
			// 	if (str_cmp(path_candidates[i], path))
			// 	{
			// 		candidate_occurances[i]++;
			// 		path_is_new = 0;
			// 		break;
			// 	}
			// }
			// if (path_is_new)
			// {
			// 	str_cpy(path_candidates[candidate_i], path); //add it to the candidate array
			// 	candidate_occurances[candidate_i] = 0;
			// 	candidate_i++;
			// }

			return 1; // at least one slot is filled
		}
	}
	path[0] = '\0';
	return 0; // no slots are filled

	// if (!candidate_i)
	// {
	// 	path[0]='\0';
	// 	return(0); //no slots are filled
	// }

	// //Find the top hit
	// top = 0;
	// for (i=0;i<candidate_i;i++)
	// {
	// 	if (candidate_occurances[i] > top)
	// 	{
	// 		top = candidate_occurances[i];
	// 		str_cpy(path, path_candidates[i]);
	// 	}
	// }
	// return(1);
}

//
// Returns the sample number inside the given bank, whose filename matches the given filename
// If not found, returns 0xFF
//
uint8_t BankManager::find_filename_in_bank(uint8_t bank, const char *filename) {
	uint8_t sample;

	if (bank >= MaxNumBanks)
		return 0xFF; // invalid bank
	if (!is_bank_enabled(bank))
		return 0xFF; // bank not enabled

	for (sample = 0; sample < NumSamplesPerBank; sample++) {
		if (str_cmp(samples[bank][sample].filename, filename))
			return sample;
	}

	return 0xFF; // not found
}

// Searches all banks for a filename
// Returns bank# if filename exists in ANY sample in that bank
// Returns 0xFF if filename is not found anywhere
// bank is the first bank to look in, setting this to a likely candidate will save CPU time
//
uint8_t BankManager::find_filename_in_all_banks(uint8_t bank, const char *filename) {
	uint8_t orig_bank;

	if (is_bank_enabled(bank))
		orig_bank = bank;
	else
		orig_bank = next_enabled_bank(bank);

	do {
		if (find_filename_in_bank(bank, filename) != 0xFF)
			return bank;

		bank = next_enabled_bank(bank);
	} while (bank != orig_bank);

	return 0xFF; // not found
}

///
/// Bank Navigation
///

uint8_t BankManager::next_bank(uint8_t bank) {
	bank++;
	if (bank >= MaxNumBanks)
		return 0;
	return bank;
}

uint8_t BankManager::prev_bank(uint8_t bank) {
	return (bank == 0) ? MaxNumBanks - 1 : bank - 1;
}

// Give a bank number, return the next enabled bank
// If bank==0xFF, return the first enabled bank
//
uint8_t BankManager::next_enabled_bank(uint8_t bank) {
	uint8_t orig_bank = bank;
	if (orig_bank >= MaxNumBanks)
		orig_bank = MaxNumBanks - 1; // otherwise we will have an infinite loop

	do {
		bank++;
		if (bank >= MaxNumBanks)
			bank = 0;
		if (bank == orig_bank)
			return 0; // no banks are enabled -->> bail out and return the first bank
	} while (!bank_status[bank]);

	return bank;
}

// Same as next_enabled_bank but acts as if there
// was an enabled bank number 255 (0xFF) after the last bank
//
uint8_t BankManager::next_enabled_bank_0xFF(uint8_t bank) {
	do {
		bank++;
		if (bank >= MaxNumBanks)
			return 0xFF;
	} while (!bank_status[bank]);

	return bank;
}

// Given a bank number, returns the previous enabled bank
// If there are no enabled banks, return 0 (which is the first bank)
//
uint8_t BankManager::prev_enabled_bank(uint8_t bank) {
	uint8_t orig_bank = bank;
	if (orig_bank >= MaxNumBanks)
		orig_bank = MaxNumBanks - 1; // otherwise we will have an infinite loop

	do {
		if (bank == 0)
			bank = MaxNumBanks - 1;
		else
			bank--;
		if (bank == orig_bank)
			return 0; // no banks are enabled -->> bail out and return the first bank
	} while (!bank_status[bank]);

	return bank;
}

// Same as prev_enabled_bank but acts as if there
// was an enabled bank number 255 (0xFF) before the first bank
//
uint8_t BankManager::prev_enabled_bank_0xFF(uint8_t bank) {
	if (bank == 0xFF)
		bank = MaxNumBanks;
	do {
		if (bank == 0)
			return 0xFF;
		bank -= 1;
	} while (!bank_status[bank]);

	return bank;
}

// Given a bank number, return the next disabled bank
// If we give bank==0xFF, then return the first disabled bank
//
uint8_t BankManager::next_disabled_bank(uint8_t bank) {
	uint8_t orig_bank = bank;
	if (orig_bank >= MaxNumBanks)
		orig_bank = MaxNumBanks - 1; // otherwise we will have an infinite loop
	do {
		bank++;
		if (bank >= MaxNumBanks)
			bank = 0;
		if (bank == orig_bank)
			return 0; // no banks are disabled -->> bail out and return the first bank
	} while (bank_status[bank]);

	return bank;
}

// Given a bank number, return the previous disabled bank
// If we give bank==0xFF, then return the first disabled bank
//
uint8_t BankManager::prev_disabled_bank(uint8_t bank) {
	uint8_t orig_bank = bank;

	if (bank >= MaxNumBanks)
		bank = MaxNumBanks;

	do {
		if (bank == 0)
			bank = MaxNumBanks;
		bank--;
		if (bank == orig_bank)
			return bank; // no banks are disabled -->> bail out and return the same bank given
	} while (!bank_status[bank]);

	return bank;
}

// Go through all banks, and enable/disable each one:
// If the bank has at least one slot with a filename and file_found==1, then enable the bank
// Otherwise disable it
void BankManager::check_enabled_banks(void) {
	for (uint32_t bank = 0; bank < MaxNumBanks; bank++) {
		bank_status[bank] = 0; // does not exist
		for (uint32_t sample_num = 0; sample_num < NumSamplesPerBank; sample_num++) {
			if (samples[bank][sample_num].filename[0] != 0 &&
				samples[bank][sample_num].file_status == FileStatus::Found)
			{
				bank_status[bank] = 1;
				break;
			}
		}
	}
}

bool BankManager::is_bank_enabled(uint8_t bank) {
	if (bank >= MaxNumBanks)
		return 0;

	return bank_status[bank] ? 1 : 0;
}

void BankManager::enable_bank(uint8_t bank) {
	bank_status[bank] = 1;
}
void BankManager::disable_bank(uint8_t bank) {
	bank_status[bank] = 0;
}

/// Initialization

// void BankManager::init_banks() {

// 	load_all_banks(false);

// }
} // namespace SamplerKit
