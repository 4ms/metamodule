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
 * Startup procedure: All button LEDs turn colors to indicate present operation:
 * Load index file: some color representing minor version number
 * Look for missing files and new folders: ORANGE
 * --Or: No index found, create all new banks from folders: WHITE
 * Write index file: MAGENTA
 * Write html file: LAVENDER
 * Done: OFF
 *
 *
 */

#include "sts_filesystem.hh"
#include "bank_util.hh"
#include "elements.hh"
#include "ff.h"
#include "log.hh"
#include "sample_header.hh"
#include "str_util.h"
#include "sts_sampleindex.hh"

namespace SamplerKit
{

uint8_t SampleIndexLoader::load_all_banks(bool force_reload) {

	// Load the index file, marking files found or not found with samples[][].file_found = 1/0;
	flags.set(Flag::StartupLoadingIndex);

	if (!force_reload) {
		pr_log("Loading index file\n");
		force_reload = (index.load_sampleindex_file(SampleIndex::USE_INDEX_FILE, MaxNumBanks) != FR_OK);
	}

	if (!force_reload) // sampleindex file was ok
	{
		pr_log("Valid sample index found\n");
		// Look for new folders and missing files

		// Update the list of banks that are enabled
		// Banks with no file_found will be disabled (but filenames will be preserved, for use in
		// load_missing_files)
		pr_log("Checking for empty banks\n");
		banks.check_enabled_banks();

		// Check for new folders, and turn them into banks if possible
		pr_log("Scanning new folders for samples\n");
		load_new_folders();

		// Check for files that have file_found==0
		// Look for a file to fill this slot
		pr_log("Looking for samples to replace missing files\n");
		load_missing_files();

		// Check for empty slots
		pr_log("Looking for samples to fill empty slots\n");
		load_empty_slots();

	}

	else // sampleindex file was not ok, or we requested to force a full reload from disk
	{
		index_needs_writeback = true;
		pr_log("No valid sample index found, or reload was requested\n");

		// Ignore index and create new banks from disk:
		flags.set(Flag::StartupNewIndex);

		// First pass: load all the banks that have default folder names
		pr_log("Looking for dirs with color names\n");
		load_banks_by_default_colors();

		// Second pass: look for folders that start with a bank name, example "Red - My Samples/"
		pr_log("Looking for dirs with color names and a number suffix\n");
		load_banks_by_color_prefix();

		// Third pass: go through all remaining folders and try to assign them to banks
		pr_log("Looking for other dirs containing samples\n");
		load_banks_with_noncolors();

		banks.check_enabled_banks();
	}

	if (index_needs_writeback) {
		if (auto res = write_index_and_html(); res != FR_OK)
			return res;
		index_needs_writeback = false;
	}

	flags.set(Flag::StartupDone);
	pr_log("Done!\n");

	return FR_OK;
}

void SampleIndexLoader::handle_events() {
	if (flags.read(Flag::WriteIndexToSD)) {
		write_index_and_html();
		flags.clear(Flag::WriteIndexToSD);
	}
}

uint8_t SampleIndexLoader::write_index_and_html() {
	// Write samples struct to index
	// ... so sample info gets updated with latest .wav header content
	// Buttons are red for index file, then orange for html file

	// Check for system dir
	FRESULT res = sd.check_sys_dir();
	if (res != FR_OK) {
		flags.set(Flag::StartupDone);
		return res;
	}

	// WRITE INDEX FILE
	pr_log("Writing sample index\n");
	flags.set(Flag::StartupWritingIndex);
	res = index.write_sampleindex_file();
	if (res != FR_OK) {
		// g_error |= CANNOT_WRITE_INDEX;
		flags.set(Flag::StartupDone);
		pr_log("Cannot write index\n");
		return res;
	}

	// WRITE SAMPLE LIST HTML FILE
	pr_log("Writing HTML index\n");
	flags.set(Flag::StartupWritingHTML);
	res = index.write_samplelist();
	if (res != FR_OK) {
		// g_error |= CANNOT_WRITE_INDEX;
		pr_log("Cannot write html file\n");
		flags.set(Flag::StartupDone);
		return res;
	}

	return FR_OK;
}

// Go through all enabled banks, looking for empty sample slots
// Search within the bank's folder, looking for a file to fill the slot
//
void SampleIndexLoader::load_empty_slots(void) {
	uint8_t bank, samplenum;
	char bankpath[FF_MAX_LFN + 1];
	char bankpath_noslash[FF_MAX_LFN + 1];
	char filename[FF_MAX_LFN + 1];
	char fullpath[FF_MAX_LFN + 1];

	FIL temp_file;
	FRESULT res = FR_OK;

	for (bank = 0; bank < MaxNumBanks; bank++) // Scan samples[][] for blank filenames
	{
		if (!banks.is_bank_enabled(bank))
			continue; // Skip disabled banks

		if (!banks.get_bank_path(bank, bankpath)) // Get the bank's predominant path
		{
			banks.disable_bank(bank);
			continue;
		} // Disable and skip banks with no samples

		str_cpy(bankpath_noslash, bankpath);
		trim_slash(bankpath_noslash);

		for (samplenum = 0; samplenum < NumSamplesPerBank; samplenum++) {
			if (!samples[bank][samplenum].filename[0]) // For each empty slot:
			{
				sd.find_next_ext_in_dir_alpha(0, 0, 0, Sdcard::Sdcard::FIND_ALPHA_INIT_FOLDER);
				samples[bank][samplenum].file_status = FileStatus::NotFound;

				while (samples[bank][samplenum].file_status == FileStatus::NotFound)
				{ // Search alphabetically for any wav file in bankpath
					uint8_t f = sd.find_next_ext_in_dir_alpha(
						bankpath_noslash, ".wav", filename, Sdcard::Sdcard::FIND_ALPHA_DONT_INIT);
					if (f != FR_OK) {
						samplenum = NumSamplesPerBank;
						break;
					} // When we hit the end of the folder, stop searching this bank [exit while() and for() loops]

					str_cat(fullpath, bankpath, filename); // Append filename to path

					if (banks.find_filename_in_bank(bank, fullpath) != 0xFF)
						continue; // Skip files that are already used in this bank

					res = sd.f_open(&temp_file, fullpath, FA_READ); // Open the file

					if (res == FR_OK) {
						auto ires = load_sample_header(&(samples[bank][samplenum]), &temp_file, sd);

						if (ires == FR_OK) // If we can load the file's wav header, then success!
						{
							str_cpy(samples[bank][samplenum].filename, fullpath); // Set the filename (full path)
							samples[bank][samplenum].file_status = FileStatus::Found;
							index_needs_writeback = true;
							pr_dbg("Found file to fill empty slot %d in bank %d, index will be re-written\n",
								   samplenum,
								   bank);
						}
					}
					sd.f_close(&temp_file);

				} // while !file_found
			}	  // if filename is blank
		}		  // for each sample
	}			  // for each bank
}

// Go through all banks and samples,
// If file_found==0, then look for a file to fill the slot:
// For example, let samples[][].filename == "path/file.wav":
//  - Scan all .wav files in path alphabetically (path/*.wav), in two passes:
//    --First pass: Look for a .wav file that isn't assigned anywhere
//    --Second pass: Look for a .wav file that isn't assigned in this bank (but may be assigned in some other bank)
//  - If still none found, keep file_found=0 and exit
//
void SampleIndexLoader::load_missing_files(void) {
	uint8_t bank, samplenum;
	char path[FF_MAX_LFN + 1];
	char path_noslash[FF_MAX_LFN + 1];
	char filename[FF_MAX_LFN + 1];
	char fullpath[FF_MAX_LFN + 1];

	FIL temp_file;
	uint8_t first_pass = 1;

	for (bank = 0; bank < MaxNumBanks; bank++) // Scan samples[][] for non-blank filename with file_found==0
	{

		for (samplenum = 0; samplenum < NumSamplesPerBank; samplenum++) {
			if (samples[bank][samplenum].filename[0] && samples[bank][samplenum].file_status == FileStatus::NotFound) {
				// split filename into path and filename
				if (str_split(samples[bank][samplenum].filename, '/', path, filename) == 0) {
					// no slashes exist in filename, so path is the root dir
					path[0] = '\0'; // root dir
					str_cpy(filename, samples[bank][samplenum].filename);
				}

				// Create a copy of path string that doesn't end in a slash
				str_cpy(path_noslash, path);
				trim_slash(path_noslash);

				sd.find_next_ext_in_dir_alpha(0, 0, 0, Sdcard::Sdcard::FIND_ALPHA_INIT_FOLDER);

				while (samples[bank][samplenum].file_status == FileStatus::NotFound) // for each file not found:
				{
					// Search alphabetically for any wav file in original file's path
					auto res =
						sd.find_next_ext_in_dir_alpha(path_noslash, ".wav", filename, Sdcard::FIND_ALPHA_DONT_INIT);

					if (res != FR_OK) // First pass: When our alphabetical search hits the end of the folder,
					{				  // initialize the search and do another pass
						if (first_pass) {
							first_pass = 0;
							sd.find_next_ext_in_dir_alpha(0, 0, 0, Sdcard::FIND_ALPHA_INIT_FOLDER);
						} else
							break; // Second pass: When we hit the end of the folder, stop searching
					}

					str_cat(fullpath, path, filename); // Append filename to path

					if (first_pass) {
						if (banks.find_filename_in_all_banks(bank, fullpath) != 0xFF)
							continue;
					} // First pass: skip files that are used in *any* bank
					else
					{
						if (banks.find_filename_in_bank(bank, fullpath) != 0xFF)
							continue;
					} // Second pass: Skip files that are used in *this* bank

					res = sd.f_open(&temp_file, fullpath, FA_READ); // Open the file

					if (res == FR_OK) {
						// Load the sample header info into samples[][]
						res = load_sample_header(&(samples[bank][samplenum]), &temp_file, sd);

						if (res == FR_OK) {
							str_cpy(samples[bank][samplenum].filename, fullpath); // Set the filename (full path)
							samples[bank][samplenum].file_status = FileStatus::Found;
							index_needs_writeback = true;
							pr_log("Filled slot with missing file (slot %d in bank %d), index will be re-written\n",
								   samplenum,
								   bank);
							banks.enable_bank(bank);
						}
					}
					sd.f_close(&temp_file);
				}

				// If no files are found, try searching anywhere for the filename
				if (samples[bank][samplenum].file_status == FileStatus::NotFound) {
					samples[bank][samplenum].filename[0] = '\0'; // not found: blank out filename
					// ToDo: If we change indexing, we may not want to blank out the filename here
					// so that we can write "path/notfoundfile.wav -- NOT FOUND" in the index text file
					// For now, we leave this because sometimes we use a blank filename to indicate file is
					// not able to be loaded
				}

			} // if file_found==0

		} // for each sample
	}	  // for each bank
}

//
// Given a path to a directory, see if any of the files in it are assigned to a sample slot
//
// Instead of going through each file in the directory in the filesystem
// and checking all the sample slots if it matches a filename,
// it's faster to search the samples[][] array for filenames that begin with this directory path + "/"
//
// Returns 1 if some sample slot uses this directory
// 0 if not
//
// Note: path must end in a slash! We don't add the slash here because we don't know if path[str_len(path)+1] is a
// valid memory location This is important because path="Blue" could return a false positive for "Blue
// Loops/mysound.wav", when we really are looking for "Blue/*.wav" If we want to check the root dir, give "/" for
// path. This will search for samples who's entry starts with "/", or have no slash in their full path
uint8_t SampleIndexLoader::dir_contains_assigned_samples(const char *path) {
	uint8_t bank, samplenum;
	uint8_t l;

	l = str_len(path);
	if (path[l - 1] != '/')
		return 0xFF; // fail, path must end in a slash

	for (bank = 0; bank < MaxNumBanks; bank++) {
		for (samplenum = 0; samplenum < NumSamplesPerBank; samplenum++) {
			if (samples[bank][samplenum].filename[0] != 0)
				if (str_startswith_nocase(samples[bank][samplenum].filename, path) == 1) //
					return 1; // found! at least one sample filename begins with path
		}
	}

	return 0; // no filenames start with path
}

//
//
//
void SampleIndexLoader::load_new_folders(void) {
	DIR root_dir, test_dir;
	FRESULT res;
	char foldername[FF_MAX_LFN + 1];
	char default_bankname[FF_MAX_LFN];
	uint8_t bank;
	uint8_t bank_loaded;
	uint8_t l;
	uint8_t checked_root = 0;

	// reset dir object, so it can be used by get_next_dir
	root_dir.obj.fs = 0;

	while (1) {
		bank_loaded = 0;
		if (!checked_root) {
			checked_root = 1; // only check root the first time

			// Check the root dir first
			foldername[0] = '\0'; // root
			l = 0;

			// Check if root dir contains any .wav files
			res = sd.f_opendir(&test_dir, foldername);

			if (res != FR_OK) {
				sd.f_closedir(&test_dir);
				continue;
			}
			if (sd.find_next_ext_in_dir(&test_dir, ".wav", default_bankname) != FR_OK) {
				sd.f_closedir(&test_dir);
				continue;
			}

			// Check if it contains any assigned samples
			if (dir_contains_assigned_samples("/"))
				continue;

		} else {
			// Get the name of the next folder inside the root dir
			res = sd.get_next_dir(&root_dir, "", foldername);

			// exit if no more dirs found
			if (res != FR_OK) {
				pr_dbg("No more dirs found\n");
				sd.f_closedir(&root_dir);
				break;
			}

			pr_dbg("Checking next dir in root: %.255s\n", foldername);

			// Check if foldername contains any .wav files
			res = sd.f_opendir(&test_dir, foldername);
			if (res != FR_OK) {
				pr_dbg("Failed to open\n");
				continue;
			}
			if (sd.find_next_ext_in_dir(&test_dir, ".wav", default_bankname) != FR_OK) {
				pr_dbg("No .wav files found\n");
				continue;
			}

			// add a slash to folder_path if it doesn't have one
			l = str_len(foldername);
			if (foldername[l - 1] != '/') {
				foldername[l] = '/';
				foldername[l + 1] = '\0';
			}

			if (dir_contains_assigned_samples(foldername)) {
				pr_dbg("Already contains assigned samples\n");
				continue;
			}
		}

		// If we got here, we found a directory that contains wav files, and none of the files are assigned as
		// samples Now we will try to add this as a new bank

		// Strip the ending slash
		foldername[l] = '\0';

		// Try to load it as a bank, to make sure there's actually some valid files inside (i.e. headers are not
		// corrupted)
		Bank test_bank;
		pr_dbg("Trying to load as a bank...\n");
		if (uint8_t num_samples_loaded = load_bank_from_disk(test_bank, foldername)) {
			pr_dbg("Loaded %d samples\n", num_samples_loaded);
			// First see if the foldername begins with a color or color-blink name:
			// Search banks from end to start, so we look for "Yellow-2" before "Yellow"
			for (bank = (MaxNumBanks - 1); bank != 0xFF; bank--) {
				bank_to_color(bank, default_bankname);

				if (str_startswith_nocase(foldername, default_bankname)) {
					pr_dbg("Starts with a bank name: %s, bank#%d\n", default_bankname, bank);
					// If the bank is already being used (e.g. "Yellow-2" is already used)
					// Then bump down Yellow-2 ==> Yellow-3, Yellow-3 ==> Yellow-4, etc..
					if (banks.is_bank_enabled(bank)) {
						banks.bump_down_banks(bank);
						pr_dbg("Already in use, bumping down banks\n");
					}

					// Copy the test_bank into bank
					banks.copy_bank(samples[bank], test_bank);
					banks.enable_bank(bank);
					bank_loaded = 1;
					index_needs_writeback = true;
					pr_dbg("Index will be re-written\n");
					break; // exit the for loop
				}
			}

			// If it's not a color/blink name, then load it into the first unused bank
			if (!bank_loaded) {
				bank = banks.next_disabled_bank(MaxNumBanks);
				banks.copy_bank(samples[bank], test_bank);
				banks.enable_bank(bank);
				bank_loaded = 1;
				index_needs_writeback = true;
				pr_dbg("Not a recognized color name, loading into %d\n", bank);
				pr_dbg("Index will be re-written\n");
			}
		} else {
			pr_dbg("Failed to load folder as a bank\n");
		}
	}
}

//
// Go through all default bank folder names,
// and see if each one is an actual folder
// If so, open it up.
//
uint8_t SampleIndexLoader::load_banks_by_default_colors(void) {
	uint8_t bank;
	char bankname[FF_MAX_LFN], bankname_case[FF_MAX_LFN];
	uint8_t banks_loaded;

	banks_loaded = 0;
	for (bank = 0; bank < MaxNumBanks; bank++) {
		bank_to_color(bank, bankname);

		// Color
		if (load_bank_from_disk((samples[bank]), bankname)) {
			banks.enable_bank(bank);
			banks_loaded++;
		} else {
			// COLOR
			str_to_upper(bankname, bankname_case);
			if (load_bank_from_disk((samples[bank]), bankname_case)) {
				banks.enable_bank(bank);
				banks_loaded++;
			} else {
				// color
				str_to_lower(bankname, bankname_case);
				if (load_bank_from_disk((samples[bank]), bankname_case)) {
					banks.enable_bank(bank);
					banks_loaded++;
				} else {
					banks.disable_bank(bank);
				}
			}
		}
	}
	return banks_loaded;
}

uint8_t SampleIndexLoader::load_banks_by_color_prefix(void) {
	uint8_t bank;
	char foldername[FF_MAX_LFN];
	char default_bankname[FF_MAX_LFN];
	uint8_t banks_loaded;

	FRESULT res;
	DIR rootdir;
	DIR testdir;

	uint8_t test_path_loaded = 0;
	uint8_t existing_prefix_len, len;

	banks_loaded = 0;

	rootdir.obj.fs = 0; // get_next_dir() needs us to do this, to reset it

	while (1) {
		// Find the next directory in the root folder
		res = sd.get_next_dir(&rootdir, "", foldername);

		if (res != FR_OK)
			break; // no more directories, exit the while loop

		test_path_loaded = 0;

		// Check if folder contains any .wav files
		res = sd.f_opendir(&testdir, foldername);
		if (res != FR_OK)
			continue;
		if (sd.find_next_ext_in_dir(&testdir, ".wav", default_bankname) != FR_OK)
			continue;

		// See if the folder we found is a default bank name
		// This would mean it's already loaded (with load_banks_by_default_colors())
		if (color_to_bank(foldername) < MaxNumBanks)
			test_path_loaded = 1;

		// Go through all the numbered bank names (Red-1, Pink-1, etc...)
		// see if the folder we found has a numbered bank name as a prefix
		// This finds things like "Red-3 - TV Clips" (but not "Red - Movie Clips")
		// color-number fodlername
		for (bank = 10; (!test_path_loaded && bank < MaxNumBanks); bank++) {
			bank_to_color(bank, default_bankname);

			if (str_startswith_nocase(foldername, default_bankname)) {
				// Make sure the bank is not already being used
				if (!banks.is_bank_enabled(bank)) {
					// ...and if not, then try to load it as a bank
					if (load_bank_from_disk((samples[bank]), foldername)) {
						banks.enable_bank(bank);
						banks_loaded++;
						test_path_loaded = 1;
						break; // continue with the next folder
					}
				}
			}
		}

		// Go through all the non-numbered default bank names (Red, White, Pink, etc...)
		// and see if this bank has one of them as a prefix
		// If the bank is a non-numbered bank name (ie bank< 9, for example: "Red" or "Blue", but not "Red-9" or
		// "Blue-4") Then check to see if subsequent numbered banks of the same color are available (so check for
		// Red-2, Red-3, Red-4) This allows us to have "Red - Synth Pads/" become Red bank, and "Red - Drum Loops/"
		// become Red-2 bank
		//
		for (bank = 0; (!test_path_loaded && bank < 10); bank++) {
			existing_prefix_len = bank_to_color(bank, default_bankname);

			if (str_startswith_nocase(foldername, default_bankname)) {
				// We found a prefix for this folder
				// If the base color name bank is still empty, load it there...
				// E.g. if we found "Red - Synth Pads" and Red bank is still available, load it there
				if (!banks.is_bank_enabled(bank)) {
					if (load_bank_from_disk((samples[bank]), foldername)) {
						banks.enable_bank(bank);
						banks_loaded++;
						test_path_loaded = 1;
						break; // continue with the next folder
					}
				}
				//...Otherwise try loading it into the next higher-numbered bank (Red-2, Red-3...)
				else
				{
					// TODO: can we remove this loop since we don't do rename_queue anymore?
					bank += 10; // add 10 to go to the next numbered bank of the same color
					while (bank < MaxNumBanks) {
						if (!banks.is_bank_enabled(bank)) {
							if (load_bank_from_disk((samples[bank]), foldername)) {
								banks.enable_bank(bank);
								banks_loaded++;
								test_path_loaded = 1;

								// Queue the renaming of the bank's folder
								// Create the new name by removing the existing color prefix, and adding the actual
								// bank prefix e.g. "White - More Loops" becomes "White-3  - More Loops"
								//
								// In the special case where we have two banks that begin with a numbered bank
								// prefix: e.g. "Red-2 Drums" and "Red-2 Synths" Then the first one found (Red-2
								// Drums) will go into Red-2, according to the previous for-loop. The second one
								// will be found in this for-loop because it is a folder name prefixed by "Red".
								// Thus it will think "-2 Synths" is the suffix. Assuming Red-3 is available, the
								// renaming will rename it to "Red-3" + "-2 Synths" = "Red-3 2 Synths" (dash is
								// trimmed) Should we detect a suffix as such and remove it? Or leave it to help the
								// user know what it used to be?

								len = bank_to_color(bank, default_bankname);
								default_bankname[len++] = ' ';
								default_bankname[len++] = '-';
								default_bankname[len++] = ' ';

								// trim spaces and dashes off the beginning of the suffix
								while (foldername[existing_prefix_len] == ' ' || foldername[existing_prefix_len] == '-')
									existing_prefix_len++;

								str_cpy(&(default_bankname[len]), &(foldername[existing_prefix_len]));

								// append_rename_queue(bank, foldername, default_bankname);

								break; // exit inner while loop and continue with the next folder
							}
						}
						bank += 10;
					}
				}
			}
		}
	}

	return banks_loaded;
}

uint8_t SampleIndexLoader::load_banks_with_noncolors(void) {
	uint8_t bank;
	uint8_t len;
	char foldername[FF_MAX_LFN];
	char default_bankname[FF_MAX_LFN];
	uint8_t banks_loaded;
	uint8_t test_path_loaded;
	uint8_t checked_root;

	FRESULT res;
	DIR rootdir;
	DIR testdir;

	banks_loaded = 0;

	checked_root = 0;
	rootdir.obj.fs = 0; // get_next_dir() needs us to do this, to reset it

	while (1) {
		if (!checked_root) {
			checked_root = 1;	  // only check root the first time
			foldername[0] = '\0'; // root
		} else {
			// Find the next directory in the root folder
			res = sd.get_next_dir(&rootdir, "", foldername);

			if (res != FR_OK)
				break; // no more directories, exit the while loop
		}

		test_path_loaded = 0;

		// Open the folder
		res = sd.f_opendir(&testdir, foldername);
		if (res != FR_OK)
			continue;

		// Check if folder contains any .wav files
		if (sd.find_next_ext_in_dir(&testdir, ".wav", default_bankname) != FR_OK) {
			sd.f_closedir(&testdir);
			continue;
		}

		// See if it starts with a default bank color string
		for (bank = 0; bank < 10; bank++) {
			bank_to_color(bank, default_bankname);
			if (str_startswith_nocase(foldername, default_bankname)) {
				test_path_loaded = 1;
				break;
			}
		}

		// Since we didn't find a bank for this folder yet, just put it in the first available bank

		for (bank = 0; (!test_path_loaded && bank < MaxNumBanks); bank++) {
			if (!banks.is_bank_enabled(bank)) {
				if (load_bank_from_disk((samples[bank]), foldername)) {
					banks.enable_bank(bank);
					banks_loaded++;
					test_path_loaded = 1;

					// Queue the renaming of the bank's folder
					// Create the new name by adding the bank name as a prefix
					// e.g. "Door knockers" becomes "Cyan-3 - Door knockers"
					len = bank_to_color(bank, default_bankname);
					default_bankname[len++] = ' ';
					// if (bank<10)
					// {
					default_bankname[len++] = '-';
					default_bankname[len++] = ' ';
					// }
					str_cpy(&(default_bankname[len]), foldername);

					// append_rename_queue(bank, foldername, default_bankname);

					break; // continue with the next folder
				} else
					break; // if load_bank_from_disk() fails for this foldername, try the next folder
			}
		}
	}

	return banks_loaded;
}

//
// Tries to open the folder bankpath and load 10 files into samples[][]
// into the specified bank
//
// Returns number of samples loaded (0 if folder not found, and sample[bank][] will be cleared)
//

uint8_t SampleIndexLoader::load_bank_from_disk(Bank &sample_bank, char *path_noslash) {
	uint32_t i;
	uint32_t sample_num;

	FIL temp_file;
	FRESULT res;

	uint8_t path_len;
	char path[FF_MAX_LFN];
	char filename[256];

	for (i = 0; i < NumSamplesPerBank; i++)
		sample_bank[i].clear();

	// Remove trailing slash
	trim_slash(path_noslash);

	// path_len = str_len(path_noslash);
	// if (path_noslash[path_len-1] == '/')
	// 	path_noslash[path_len-1]='\0';

	// Copy path_noslash into path and add a slash
	str_cpy(path, path_noslash);
	path_len = str_len(path);
	path[path_len++] = '/';
	path[path_len] = '\0';

	sample_num = 0;
	filename[0] = 0;

	// Initialize alphabetical searching in folder
	sd.find_next_ext_in_dir_alpha(path_noslash, ".wav", 0, Sdcard::FIND_ALPHA_INIT_FOLDER);

	while (sample_num < NumSamplesPerBank) // for every sample slot in bank
	{
		// find next file alphabetically
		auto findres = sd.find_next_ext_in_dir_alpha(path_noslash, ".wav", filename, Sdcard::FIND_ALPHA_DONT_INIT);
		if (findres != FR_OK) {
			break;
		} // Stop if no more files found/available or there's an error

		str_cpy(&(path[path_len]), filename);		// Append filename to path
		res = sd.f_open(&temp_file, path, FA_READ); // Open file
		sd.f_sync(&temp_file);

		if (res == FR_OK) {
			if (load_sample_header(&(sample_bank[sample_num]), &temp_file, sd) == FR_OK)
				str_cpy(sample_bank[sample_num++].filename, path); // Set the filename (full path)
		}
		sd.f_close(&temp_file);
	}
	return sample_num;
}

} // namespace SamplerKit
