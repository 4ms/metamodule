/*
 * sts_sampleindex.cc - interaction with the sample index file
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

#include "sts_sampleindex.hh"
#include "bank_util.hh"
#include "elements.hh"
#include "ff.h"
#include "log.hh"
#include "sample_header.hh"
#include "str_util.h"

namespace SamplerKit
{

#define ALL_BANKS MaxNumBanks

#define SAMPLE_SLOT 1
#define PLAY_START 2
#define PLAY_SIZE 3
#define PLAY_GAIN 4

#define PLAYDATTAG_SLOT "- sample slot"
#define PLAYDATTAG_START "- play start"
#define PLAYDATTAG_SIZE "- play size"
#define PLAYDATTAG_GAIN "- play gain"

#define SAMPLELIST_FILE "__Sample List__.html"
#define SAMPLE_INDEX_FILE "sample_index.dat"
#define SAMPLE_BAK_FILE "sample_index-bak.dat"
#define SAMPLE_BOOTBAK_FILE "sample_index_boot-bak.dat"
#define RENAME_LOG_FILE "renamed_folders.txt"

#define EOF_TAG "End of file"
#define EOF_PAD 10 // number of characters that can be left after EOF_TAG

// Checks if string ends in ".wav" (case-insensitive)
static uint8_t is_wav(char *string) {

	char *cp;
	char a = 0, b = 0, c = 0, d = 0;

	for (cp = string; *cp != 0; cp++) {
		a = b;
		b = c;
		c = d;
		d = *cp;
	}
	if ((a == '.') && (upper(b) == 'W') && (upper(c) == 'A') && (upper(d) == 'V'))
		return 1;
	else
		return 0;
}

FRESULT SampleIndex::write_sampleindex_file() {
	FIL temp_file;
	FRESULT res;
	uint8_t i, j;
	char b_color[11];
	char bank_path[FF_MAX_LFN + 1];
	char filename_ptr[FF_MAX_LFN + 1];
	char path[FF_MAX_LFN + 1];

	// CREATE INDEX FILE
	// previous index files are replaced
	// f_open, f_sync and f_rpintf are functions from
	// ...the module application interface
	// ...for the Generic FAT file system module  (ff.h)

	// WRITE SAMPLES DATA TO INDEX FILE

	// file index path
	str_cat(path, SYS_DIR_SLASH, SAMPLE_INDEX_FILE);

	// backup index at boot
	// if (flags[BootBak]) {
	// 	str_cat(bootbakpath, SYS_DIR_SLASH, SAMPLE_BOOTBAK_FILE); // compute path to boot backups
	// 	f_unlink(bootbakpath);									  // delete existing boot backups
	// 	f_rename(path, bootbakpath); // set boot backup to sample index, as found on the SD card
	// 	flags[BootBak] = 0;			 // do not update boot backup file until next boot
	// }

	// (re)create sample.index file and its pointer &temp_file
	res = f_open(&temp_file, path, FA_WRITE | FA_CREATE_ALWAYS);
	if (res != FR_OK)
		return res;

	// write firmware version
	f_printf(&temp_file, "Firmware Version: %d.%d\n\n", FirmwareMajorVersion, FirmwareMinorVersion);

	// write banks/sample to index file
	for (i = 0; i < MaxNumBanks; i++) // For each bank
	{
		// Print bank Color to index file
		bank_to_color(i, b_color);
		f_printf(&temp_file, "--------------------\n%s\n--------------------\n", b_color);
		// f_sync(&temp_file);

		for (j = 0; j < NumSamplesPerBank; j++) // For each sample in bank
		{

			// FixMe: if samples[i][j] contains a filename with no slashes (example: "ChordHits1.wav")
			// then the next line will return filename_ptr as null, and so the sample entry will not be written to
			// the index, but the sample will play and be written to the HTML file Perhaps we could add a slash to
			// the beginning of samples[][].filename if no slash is found?

			str_split(samples[i][j].filename, '/', path, filename_ptr); // split path and filename
			if (filename_ptr[0] != '\0')								// Skip empty slots
			{
				// Print bank path to index file
				if (j == 0) {
					str_cpy(bank_path, path);
					f_printf(&temp_file, "path: %s\n\n", path);
					// f_sync(&temp_file);
				}

				// Print sample name to index file
				if (str_cmp(path, bank_path))
					f_printf(&temp_file, "%s\n", filename_ptr);
				else
					f_printf(&temp_file, "%s\n", samples[i][j].filename);
				// f_sync(&temp_file);

				// write sample header info to index file
				switch (samples[i][j].numChannels) {
					case 1:
						f_printf(&temp_file,
								 "sample info: %dHz, %d-bit, mono,   %d samples\n",
								 samples[i][j].sampleRate,
								 samples[i][j].sampleByteSize * 8,
								 samples[i][j].sampleSize);
						// f_sync(&temp_file);
						break;
					case 2:
						f_printf(&temp_file,
								 "sample info: %dHz, %d-bit, stereo, %d samples\n",
								 samples[i][j].sampleRate,
								 samples[i][j].sampleByteSize * 8,
								 samples[i][j].sampleSize);
						// f_sync(&temp_file);
						break;
				}

				// write play data to index file
				f_printf(&temp_file,
						 "%s: %d\n%s: %d\n%s: %d\n%s(%%): %d\n\n",
						 PLAYDATTAG_SLOT,
						 j + 1,
						 PLAYDATTAG_START,
						 samples[i][j].inst_start,
						 PLAYDATTAG_SIZE,
						 samples[i][j].inst_size,
						 PLAYDATTAG_GAIN,
						 (int)(100 * samples[i][j].inst_gain));
				// f_sync(&temp_file);
			}
		}
		f_printf(&temp_file, "\n");
		// f_sync(&temp_file);
	}

	// Write global info to file
	f_printf(&temp_file, "Timestamp: %d\n", get_fattime()); // timestamp
	f_printf(&temp_file, EOF_TAG);							// end of file tag
	f_printf(&temp_file, "\n"); // text editors report an error if file does not end in newline

	// CLOSE INDEX FILE
	f_sync(&temp_file);
	f_close(&temp_file);
	return FR_OK;
}

// WRITE SAMPLE LIST HTML
// previous files are replaced
FRESULT SampleIndex::write_samplelist(void) {

	FIL temp_file;
	FRESULT res;
	uint8_t i, j;
	uint32_t minutes, seconds;
	uint8_t bank_is_empty;
	char b_color[11]; // Lavender-5\0

	// create file
	res = f_open(&temp_file, SAMPLELIST_FILE, FA_WRITE | FA_CREATE_ALWAYS);
	if (res != FR_OK)
		return res;

	f_sync(&temp_file);

	// WRITE 'SAMPLES' INFO TO SAMPLE LIST
	f_printf(&temp_file,
			 "<!DOCTYPE html>\n<html>\n\
<head>\n<style type=\"text/css\">\n@media print\n{\n   div{page-break-inside: avoid;}\n   body {font-size:7pt;}\n   h2 {font-size:11pt;}\n   h1 {font-size:13pt;}\n}\n</style>\n</head>\n\
<body style=\"padding-left: 100px; background-color:#F8F9FD;\">\n<br>Firmware Version: %d.%d<br>\n<h1>SAMPLE LIST</h1><br>\n",
			 FirmwareMajorVersion,
			 FirmwareMinorVersion);
	f_sync(&temp_file);

	// For each bank
	for (i = 0; i < MaxNumBanks; i++) {

		// check if bank is empty
		bank_is_empty = 1;
		j = 0;
		while (j < NumSamplesPerBank) {
			if (samples[i][j].filename[0] != 0) {
				bank_is_empty = 0;
				break;
			}
			j++;
		}

		// if bank isn't empty
		if (!bank_is_empty) {

			// Print bank name to file
			bank_to_color(i, b_color);
			if (i > 0) {
				f_printf(&temp_file, "<br>\n");
				f_sync(&temp_file);
			}
			f_printf(&temp_file, "\n<div>\n<h2>%s</h2>\n<table>\n", b_color);
			f_sync(&temp_file);

			// Print sample name to sample list, for each sample in bank
			for (j = 0; j < NumSamplesPerBank; j++) {
				seconds = (samples[i][j].sampleSize / samples[i][j].blockAlign) / samples[i][j].sampleRate;
				minutes = seconds / 60;
				seconds -= minutes * 60;
				if (!minutes && !seconds)
					seconds = 1;
				if (samples[i][j].filename[0] != 0)
					f_printf(&temp_file,
							 "<tr>\n<td>%d]  %s</td>\n<td>........... [%02d:%02d]</td>\n</tr>\n",
							 j + 1,
							 samples[i][j].filename,
							 minutes,
							 seconds);
				else
					f_printf(&temp_file, "<tr>\n<td>%d]&nbsp;&nbsp;(empty slot)</td>\n<td>&nbsp;</td>\n</tr>\n", j + 1);
				f_sync(&temp_file);
			}

			f_printf(&temp_file, "</table><br>\n</div>\n");
			f_sync(&temp_file);
		}
	}
	f_printf(&temp_file, "</body>\n</html>");
	f_sync(&temp_file);

	// CLOSE FILE
	f_close(&temp_file);
	return FR_OK;
}

FRESULT SampleIndex::backup_sampleindex_file(void) {
	// ToDo: could just duplicate data and open resulting pointer
	// ... if dup is not available
	// FILE *fp2 = fdopen (dup (fileno (fp)), "r");

	FIL indexfile, backupindex;
	FRESULT res_index, res_bak;
	char read_buff[512];
	UINT bytes_read, bytes_written;
	char idx_full_path[FF_MAX_LFN + 1];
	char bak_full_path[FF_MAX_LFN + 1];

	// Open index
	str_cat(idx_full_path, SYS_DIR_SLASH, SAMPLE_INDEX_FILE);
	res_index = f_open(&indexfile, idx_full_path, FA_READ);
	if (res_index != FR_OK) {
		f_close(&indexfile);
		return res_index;
	}

	// Open Backup file
	str_cat(bak_full_path, SYS_DIR_SLASH, SAMPLE_BAK_FILE);
	res_bak = f_open(&backupindex, bak_full_path, FA_WRITE | FA_CREATE_ALWAYS);
	if (res_bak != FR_OK) {
		f_close(&indexfile);
		f_close(&backupindex);
		return res_bak;
	}

	while (1) {
		// Read index file
		f_read(&indexfile, read_buff, 512, &bytes_read);

		// Write into backup file
		f_write(&backupindex, read_buff, bytes_read, &bytes_written);
		f_sync(&backupindex);

		if (bytes_written != bytes_read) // error
		{
			f_close(&indexfile);
			f_close(&backupindex);
			return FR_INT_ERR; // ToDo: there should be a way to report this error more accurately
		}

		if (f_eof(&indexfile)) {
			f_close(&indexfile);
			f_close(&backupindex);
			return FR_OK;
		}
	}
}

// Returns 0 if invalid file (file can't be opened/read, or no EOF_TAG at end of file)
// Returns 1 if we read EOF_TAG at the end of the file
bool SampleIndex::check_sampleindex_valid(const char *indexfilename) {
	FIL temp_file;
	FRESULT res;
	char full_path[FF_MAX_LFN + 1];
	char readdata[FF_MAX_LFN + 1];
	uint8_t l;
	UINT br;

	str_cat(full_path, SYS_DIR_SLASH, SAMPLE_INDEX_FILE);
	res = f_open(&temp_file, full_path, FA_READ);

	if (res != FR_OK) {
		return false;
	} // file can't open

	// Verify it's a complete file, with EOF_TAG at the end
	l = str_len(EOF_TAG) + EOF_PAD;

	res = f_lseek(&temp_file, f_size(&temp_file) - l);
	if (res != FR_OK) {
		f_close(&temp_file);
		return false;
	} // can't seek to end: file/disk error

	res = f_read(&temp_file, readdata, l, &br);
	if (res != FR_OK) {
		f_close(&temp_file);
		return false;
	} // can't read from file: file/disk error

	if (br != l) {
		f_close(&temp_file);
		return false;
	} // didn't read proper number of bytes: disk/read error

	// Check for EOF_TAG within last read buffer
	readdata[br] = '\0';
	if (!str_found(readdata, EOF_TAG)) {
		f_close(&temp_file);
		return false;
	} // no EOF_TAG found at end of file: index is incomplete

	// Index file is ok
	f_close(&temp_file);
	return true;
}

// load_sampleindex_file
// Author: Hugo Paris
//
// Loads a sample index file
// Sets samples[][] for all banks, or just one bank (specified with banks=bank# or banks=MaxNumBanks --> all banks)
//
// Can request the normal index file, or the backup file (use_backup=USE_INDEX_FILE or USE_BACKUP_FILE)
// Note: if we request backup file, but it's invalid/missing, then we exit with an error
// On the other hand, if we request the index file but it's invalid/missing, then we use the backup file instead
//
// FIXME: This is illegible, rewrite
FRESULT SampleIndex::load_sampleindex_file(SampleIndex::IndexSelection use_backup, uint8_t banks) {
	FIL temp_file, temp_wav_file;
	FRESULT res;
	uint8_t head_load;
	char read_buffer[FF_MAX_LFN + 1], folder_path[FF_MAX_LFN + 2], file_name[FF_MAX_LFN + 1], full_path[FF_MAX_LFN + 1];
	uint8_t cur_bank = 0, cur_sample = 0, arm_bank = 0, load_data = 0, loaded_header = 0, read_name = 0;
	uint32_t num_buff = UINT32_MAX;
	char token[FF_MAX_LFN + 1];
	uint8_t l;
	bool sample_was_loaded = false;
	uint8_t skip_cur_bank = 0;
	uint8_t separator = 0;
	uint8_t invalid_banknum = 0;

	// handle backup vs normal index file, and open
	if (use_backup == USE_INDEX_FILE) {
		if (!check_sampleindex_valid(SAMPLE_INDEX_FILE))
			use_backup = USE_BACKUP_FILE;
	} // If normal non-backup file requested but isn't a valid file, use the backup file instead

	if (use_backup == USE_BACKUP_FILE) {
		if (!check_sampleindex_valid(SAMPLE_BAK_FILE))
			return FR_INT_ERR;
	} // If we requested the backup file (or if we requested the normal file, and it was invalid, Then see if the backup
	  // file is valid. If not, then we exit with an error

	if (use_backup) {
		str_cat(full_path, SYS_DIR_SLASH, SAMPLE_BAK_FILE);
	} else {
		str_cat(full_path, SYS_DIR_SLASH, SAMPLE_INDEX_FILE);
	}

	res = f_open(&temp_file, full_path, FA_READ);
	if (res != FR_OK) {
		pr_dbg("Index file not found: %.255s\n", full_path);
		return FR_NO_FILE; // file not found
	}

	pr_log("Found index file at: %.255s\n", full_path);
	pr_log("Parsing\n");

	uint32_t dot_cnt = 0;
	// Read File
	while (!f_eof(&temp_file)) // until we reach the eof
	{
		f_gets(read_buffer, FF_MAX_LFN + 1, &temp_file); // Read next line
		pr_log(".");
		if (dot_cnt++ > 60) {
			flags.set(Flag::StartupParsing);
			pr_log("\n");
			dot_cnt = 0;
		}
		if (read_buffer[str_len(read_buffer) - 1] == '\n')
			read_buffer[str_len(read_buffer) - 1] = 0; // Remove \n from buffer (mac)
		if (read_buffer[str_len(read_buffer) - 1] == '\r')
			read_buffer[str_len(read_buffer) - 1] = 0; // Remove \r from end of buffer as needed (PC)
		if (str_found(read_buffer, EOF_TAG)) {
			pr_dbg("End of File\n");
			break; // Check if it's the end of the file
		}
		if ((read_name < 1) && (load_data == 0)) {
			str_tok(read_buffer, ' ', token);
			// tokenize at space if we're not trying to read_name which is both [reading name] and
			// [reading play  data] cases
		} else
			str_cpy(token, read_buffer); // otherwise, copy read buffer into token

		pr_dbg("Token: %s\n", token);
		separator = str_cmp(token, "--------------------"); // set separator value

		// Read full line from file
		while (token[0] != '\0') // While we're not finished reading line
		{
			// Load bank data
			if ((!loaded_header) && (!skip_cur_bank)) {
				// Bank name start: "--------------------"
				if (separator && !arm_bank) {
					arm_bank++;
					invalid_banknum = 0;
					str_tok(read_buffer, ' ', token);
				}

				// Bank number
				else if (!separator && arm_bank)
				{
					cur_bank = color_to_bank(token); // define bank number
					pr_dbg("Processing bank: %12s, %d\n", token, cur_bank);
					if (banks != MaxNumBanks) {
						if (banks != cur_bank)
							skip_cur_bank = 1;
					} // request bank to be skipped if it is not to be loaded
					if (cur_bank >= MaxNumBanks) {
						invalid_banknum = 1;
					} // if bank number invalid, mark as such
					str_tok(read_buffer, ' ', token);
				}
				// Bank name end: "--------------------"
				else if (separator && arm_bank)
				{
					arm_bank = 0;
					str_tok(read_buffer, ' ', token);
				}

				// Folder path
				else if (str_cmp(token, "path:"))
				{
					str_cpy(folder_path, read_buffer);
					loaded_header = 1;
					cur_sample = 0;
					token[0] = '\0';
					read_name = 1;
				}
			}

			// Load file name
			else if ((!separator && (read_name == 1)) && (!skip_cur_bank))
			{

				// save file name
				str_cpy(file_name, token);
				pr_dbg("Filename: %255s\n", file_name);

				// move on to reading data only if file name is valid
				if (file_name[0] != '-') {
					read_name++;
				}

				token[0] = '\0';
			}

			// Load .wav header data information and play data
			else if (((!separator) && (read_name > 1)) && (!skip_cur_bank))
			{

				// HANDLE MISSING PLAY DATA
				if (is_wav(read_buffer)) // check if read buffer is a filename.
				{
					// load missing play data on current file
					if (!load_data || load_data == SAMPLE_SLOT) // if no slot for previous sample
					{
						// load previous sample in next available slot (will be overwitten if a following file
						// specifically assigned there)
						while (samples[cur_bank][cur_sample].file_status !=
							   FileStatus::NotFound) // until empty slot found
						{
							if (cur_sample < NumSamplesPerBank - 1) {
								cur_sample++;
							} // move to next sample slot
							else
							{
								load_data = 0;
								read_name = 1;
								break;
							} // exit if cur_sample==NumSamplesPerBank
						}
						if (samples[cur_bank][cur_sample].file_status == FileStatus::NotFound) // if empty slot found
						{
							// TRY AND OPEN FILE
							res = FR_INT_ERR;
							if (str_pos('/', file_name) != 0xFFFFFFFF) {
								str_cpy(full_path, file_name);
								// DEBUG0_ON;
								res = f_open(&temp_wav_file, full_path, FA_READ);
								// DEBUG0_OFF;
							}
							if (res != FR_OK) // if file wasn't found
							{
								l = str_len(folder_path); // add a slash to folder_path if it doesn't have one, and
														  // file_name doesn't start with one
								if (folder_path[l - 1] != '/' && file_name[0] != '/') {
									folder_path[l] = '/';
									folder_path[l + 1] = '\0';
								}
								str_cat(full_path, folder_path, file_name);
								// DEBUG0_ON;
								res = f_open(&temp_wav_file, full_path, FA_READ); // try to open folder_path/file_name
																				  //  DEBUG0_OFF;
							}
							if (res == FR_OK) // file found
							{
								pr_dbg("File found: %255s\n", full_path);
								if (!invalid_banknum) // Sanity check: cur_bank must be within range
								{
									str_cpy(samples[cur_bank][cur_sample].filename,
											full_path);		  // open file_name (not read_buffer)
									sample_was_loaded = true; // At least a sample was loaded
									head_load = load_sample_header(&samples[cur_bank][cur_sample], &temp_wav_file);
									f_close(&temp_wav_file); // close wav file
									if (head_load != FR_OK) {
										load_data = 0;
										read_name = 1;
										pr_dbg("Failed to load\n");
										break;
									} // if header information couldn't load, treat file as if it couldn'tbe found
									else
									{
										pr_dbg("Loaded OK\n");
										samples[cur_bank][cur_sample].file_status = FileStatus::Found;
										load_data = PLAY_START;
									} // othewise set file as found and move on to next play data
								} else {
									f_close(&temp_wav_file);
									load_data = 0;
									read_name = 1;
									break;
								}					 // exit if cur_bank out of range
							} else if (res != FR_OK) // file not found
							{
								pr_dbg("File not found: %255s\n", full_path);
								if (!invalid_banknum) {
									str_cpy(samples[cur_bank][cur_sample].filename, full_path);
									// Copy the file name into the sample struct element - This is
									// used to find the missing file, or other files in its folder
									samples[cur_bank][cur_sample].file_status =
										FileStatus::NotFound; // Mark file as not found
								} else {
									f_close(&temp_wav_file);
									load_data = 0;
									read_name = 1;
									break;
								} // exit if cur_bank out of range
								load_data = 0;
								read_name = 1;
								break; // skip loading sample play information
							}
						} else // otherwise, if no empty slot available
						{
							samples[cur_bank][cur_sample].file_status = FileStatus::NotFound; // mark file as not found
							load_data = 0;
							read_name = 1;
							break; // skip loading sample play information
						}
					}
					// Set default values for start/end/size/gain
					if (load_data == PLAY_START) {
						samples[cur_bank][cur_sample].inst_start = 0;
						load_data++;
					}
					if (load_data == PLAY_SIZE) {
						samples[cur_bank][cur_sample].inst_size = samples[cur_bank][cur_sample].sampleSize;
						samples[cur_bank][cur_sample].inst_end = samples[cur_bank][cur_sample].sampleSize;
						load_data++;
					}
					if (load_data == PLAY_GAIN) {
						samples[cur_bank][cur_sample].inst_gain = 1;
						load_data = 0;
						read_name = 1;
						str_cpy(token, read_buffer);
						continue;
					} // use read_buffer to load next file name
				}

				// HANDLE DEFINED PLAY DATA
				else if (read_buffer[0] == '-')
				{
					num_buff = str_xt_int(read_buffer);
					if (!load_data) {
						if (str_startswith_nocase(read_buffer, PLAYDATTAG_SLOT)) {
							load_data = SAMPLE_SLOT;
						}

						// HANDLE MISSING SLOT ENTRY
						else
						{
							// find next available slot
							while (samples[cur_bank][cur_sample].file_status !=
								   FileStatus::NotFound) // until empty slot found
							{
								if (cur_sample < NumSamplesPerBank - 1) {
									cur_sample++;
								} // move to next sample slot
								else
								{
									break;
								} // exit if cur_sample==NumSamplesPerBank
							}
							if (samples[cur_bank][cur_sample].file_status == FileStatus::Found) // if no empty slot
							{
								str_cpy(samples[cur_bank][cur_sample].filename, full_path); // keep track of unused file
								samples[cur_bank][cur_sample].file_status = FileStatus::NotFound;
								load_data = 0;
								token[0] = '\0';
								read_name = 1;
								break; // skip loading sample play information
							} else {
								num_buff = cur_sample + 1;
								load_data = SAMPLE_SLOT;
							} // keep on loading play data
						}
					}

					if (load_data == SAMPLE_SLOT) // if the data loading has just been armed
					{
						if (num_buff == UINT32_MAX) { // if no slot number not indicated
							samples[cur_bank][cur_sample].file_status = FileStatus::NotFound;
							load_data = 0;
							token[0] = '\0';
							read_name = 1;
							break; // skip loading sample play information
						}

						// Update sample bank number
						cur_sample = num_buff - 1;

						// ToDo (H) Move slot number check here
						// ToDo (H) check requested slot number against what's already used and update accordingly

						// If filename contains a slash, then try the filename as written
						//--- if it doesn't contain a slash, then it's not a path, so don't assume it's in root
						res = FR_INT_ERR; // not FR_OK
						if (str_pos('/', file_name) != 0xFFFFFFFF) {
							str_cpy(full_path, file_name);
							// DEBUG1_ON;
							res = f_open(&temp_wav_file, full_path, FA_READ);
							// DEBUG1_OFF;
						}
						if (res != FR_OK) {
							// add a slash to folder_path if it doesn't have one, and file_name doesn't start with one
							l = str_len(folder_path);
							if (folder_path[l - 1] != '/' && file_name[0] != '/') {
								folder_path[l] = '/';
								folder_path[l + 1] = '\0';
							}

							// try to open folder_path/file_name
							str_cat(full_path, folder_path, file_name);
							// DEBUG1_ON;
							res = f_open(&temp_wav_file, full_path, FA_READ);
							// DEBUG1_OFF;
						}

						if (res == FR_OK) // file found
						{
							// Sanity check: cur_bank and cur_sample must be in range, or we risk memory corruption
							if (!invalid_banknum && cur_sample < NumSamplesPerBank) {
								str_cpy(samples[cur_bank][cur_sample].filename,
										full_path); // use whatever file_name was opened
								samples[cur_bank][cur_sample].file_status = FileStatus::Found;
								sample_was_loaded = true; // At least a sample was loaded
								head_load = load_sample_header(&samples[cur_bank][cur_sample], &temp_wav_file);
								f_close(&temp_wav_file);
							} else {
								f_close(&temp_wav_file);
								load_data = 0;
								token[0] = '\0';
								read_name = 1;
								break;
							} // exit if cur_bank and/or cur_sample are out of range

							// if header information couldn't load, treat file as if it couldn'tbe found
							if (head_load != FR_OK) {
								if (!invalid_banknum && cur_sample < NumSamplesPerBank) {
									samples[cur_bank][cur_sample].file_status = FileStatus::NotFound;
								}
								load_data = 0;
								token[0] = '\0';
								read_name = 1;
								break; // skip loading sample play information, and read next file
							}
							load_data++;
							token[0] = '\0'; // read next line
						}

						else if (res != FR_OK) // file not found
						{
							if (!invalid_banknum && cur_sample < NumSamplesPerBank) {
								str_cpy(samples[cur_bank][cur_sample].filename,
										full_path); // Copy the file name into the sample struct element
								samples[cur_bank][cur_sample].file_status = FileStatus::NotFound;
								// Mark file as not found, later used to find missing file, or other files in its
								// folder
							}
							load_data = 0;
							token[0] = '\0';
							read_name = 1;
							break; // skip loading sample play information
						}
					}

					else if (load_data == PLAY_START)
					{
						if (num_buff > samples[cur_bank][cur_sample].sampleSize)
							samples[cur_bank][cur_sample].inst_start =
								0; // bound check on start pos. set it to the default value of 0 if greater than the
								   // allowed sampleSize
						else
							samples[cur_bank][cur_sample].inst_start = num_buff;
						load_data++;
						token[0] = '\0';
						break; // read next line
					}

					else if (load_data == PLAY_SIZE)
					{
						if ((num_buff < 88) || (num_buff > samples[cur_bank][cur_sample].sampleSize))
							samples[cur_bank][cur_sample].inst_size =
								samples[cur_bank][cur_sample]
									.sampleSize; // bound check on play size/ is too short (<2ms @ 44kHz) or too long,
												 // set it to the default value of sampleSize
						else
							samples[cur_bank][cur_sample].inst_size = num_buff;

						samples[cur_bank][cur_sample].inst_end =
							samples[cur_bank][cur_sample].inst_size +
							samples[cur_bank][cur_sample].inst_start; // Set the inst_end based on start and size

						if (samples[cur_bank][cur_sample].inst_end > samples[cur_bank][cur_sample].sampleSize ||
							samples[cur_bank][cur_sample].inst_end < 88) // Boundary check the inst_end
							samples[cur_bank][cur_sample].inst_end = samples[cur_bank][cur_sample].sampleSize;

						load_data++;
						token[0] = '\0';
						break; // read next line
					}

					else if (load_data == PLAY_GAIN)
					{
						if (num_buff < 10 || num_buff > 500) {
							num_buff = 100;
						} // bound check on gain
						samples[cur_bank][cur_sample].inst_gain = num_buff / 100.0f;
						load_data = 0;
						token[0] = '\0';
						read_name = 1;
						break; // read next line, and look for for sample name
					}
				} else {
					token[0] = '\0';
					break;
				} // read next line
			}

			// Move to next bank
			else if (separator)
			{
				skip_cur_bank = 0;
				read_name = 0;
				loaded_header = 0;
				read_buffer[0] = '\0';
			}

			// If nothing is recognized, read new line
			if (((!loaded_header && !((separator && !arm_bank) || (!separator && arm_bank) || (separator && arm_bank) ||
									  (str_cmp(token, "path:")))) ||
				 skip_cur_bank))
			{
				token[0] = '\0';
			}
		}
	}

	pr_log("\n");

	// close sample index file
	f_close(&temp_file);

	// returns 0 if index is valid (one sample was loaded, at least)
	return sample_was_loaded ? FR_OK : FR_INT_ERR;
}

} // namespace SamplerKit
