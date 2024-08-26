#pragma once
#include "CoreModules/fs_access.hh"
#include "elements.hh"
#include "str_util.h"
#include <string_view>

namespace SamplerKit
{

struct Sdcard : MetaModule::FS {
	constexpr static std::string_view SYS_DIR = "_STS.system";
	constexpr static std::string_view SYS_DIR_SLASH = "_STS.system/";

	enum INIT_FIND_ALPHA_ACTIONS { FIND_ALPHA_DONT_INIT, FIND_ALPHA_INIT_FOLDER };
	enum { INVALID_FILENAME = 0xFE, NO_MORE_AVAILABLE_FILES = 0xFF };

	Sdcard(std::string_view root)
		: FS(root) {
	}

	bool reload_disk(std::string_view base_dir = "") {
		// base_dir will be "" or "Sample-1", etc.

		// First look for a root with base_dir + STS system dir
		std::string sys_dir = base_dir.length() ? std::string(base_dir) + "/" + std::string(SAMPLE_INDEX_FILE_PATH) :
												  std::string(SAMPLE_INDEX_FILE_PATH);
		if (find_valid_root(sys_dir))
			return true;

		// If not found, then look for a root where the base_dir exists
		// If base_dir is "" then...?
		if (find_valid_root(base_dir))
			return true;

		return false;
	}

	//
	// Create a fast-lookup table (linkmap)
	//
	uint32_t chan_clmt[10][256];

	FRESULT create_linkmap(FIL *fil, uint8_t samplenum) {
		FRESULT res = FR_OK;

		fil->cltbl = chan_clmt[samplenum];
		chan_clmt[samplenum][0] = 256;

		res = f_lseek(fil, CREATE_LINKMAP);
		return res;
	}

	// Create the sys dir if not existing already
	FRESULT check_sys_dir() {
		FRESULT res;
		DIR dir;

		res = f_opendir(&dir, SYS_DIR.data());

		if (res != FR_OK) {
			return FR_INT_ERR; // fail
		}

		return FR_OK;
	}

	// Returns the next directory in the parent_dir
	//
	// To reset to the first directory, pass dir->obj.fs=0
	// Following that, pass the same dir argument each time it's called, and
	// the string path of the next directory in the parent_dir will be returned.
	// If no more directories exist, it will return 0
	//
	FRESULT get_next_dir(DIR *dir, const char *parent_path, char *next_dir_path) {
		FRESULT res = FR_OK;
		FILINFO fno;
		uint8_t i;

		if (dir->obj.fs == 0) {
			// Open the directory
			res = f_opendir(dir, parent_path);
		}
		if (res == FR_OK) {
			for (;;) {
				// Read a directory item
				res = f_readdir(dir, &fno);
				if (res != FR_OK || fno.fname[0] == 0)
					break;

				// It's a directory that doesn't start with a dot
				if ((fno.fattrib & AM_DIR) && (fno.fname[0] != '.')) {

					str_cpy(next_dir_path, parent_path);

					i = str_len(next_dir_path);

					// Append the directory name to the end of parent_path
					str_cpy(&(next_dir_path[i]), fno.fname);
					return (FR_OK);
				}
			}
			return FR_NO_FILE;
		}
		return FR_NO_PATH;
	}

	uint8_t find_next_ext_in_dir(DIR *dir, const char *ext, char *fname) {
		FRESULT res;
		FILINFO fno;
		uint32_t i;

		fname[0] = 0; // null string

		// loop through dir until we find a file ending in ext
		for (;;) {

			res = f_readdir(dir, &fno);

			if (res != FR_OK)
				return res; // filesystem error
			if (fno.fname[0] == 0) {
				fname[0] = 0;
				return 0xFF;
			} // no more files found

			if (fno.fname[0] == '.')
				continue; // ignore files starting with a .

			i = str_len(fno.fname);
			if (i == 0xFFFFFFFF)
				return 0xFE; // file name invalid

			if (fno.fname[i - 4] == ext[0] && upper(fno.fname[i - 3]) == upper(ext[1]) &&
				upper(fno.fname[i - 2]) == upper(ext[2]) && upper(fno.fname[i - 1]) == upper(ext[3]))
			{
				str_cpy(fname, fno.fname);
				return (FR_OK);
			}
		}

		return 0xFD; // should not reach here, error
	}

	// find_next_ext_in_dir_alpha()
	// - finds next file in 'path' alphabetically
	// - sets fname as the filename for that file
	// - Returns FRESULT representing whether a file was available or not, and the reason if not.
	// - files that are already assigned are kept track of in the static array used_from_folder[MAX_FILES_IN_FOLDER]
	// - set do_init to FIND_ALPHA_INIT_FOLDER to reset the alphabetical searching, or when calling this function with a
	// new path

	uint8_t find_next_ext_in_dir_alpha(char *path, const char *ext, char *fname, INIT_FIND_ALPHA_ACTIONS do_init) {
		constexpr uint32_t MAX_FILES_IN_FOLDER = 500;

		FRESULT res;
		FILINFO fno;
		uint32_t i;
		DIR dir;

		uint32_t firstf_num = 0xFFFF;
		uint32_t fnum = 0;
		char firstf_name[FF_MAX_LFN + 1];
		static uint8_t used_from_folder[MAX_FILES_IN_FOLDER];

		// Initialize variables
		if (do_init == FIND_ALPHA_INIT_FOLDER) {
			for (i = 0; i < MAX_FILES_IN_FOLDER; i++) {
				used_from_folder[i] = 0;
			} // Reset folder tracking
			return FR_OK;
		}

		for (i = 0; i < FF_MAX_LFN + 1; i++) {
			firstf_name[i] = 127;
		} // last possible file name, alphabetically
		fname[0] = 0; // null string

		// Open folder
		res = f_opendir(&dir, path);
		if (res != FR_OK)
			return res;

		// Loop through folder content
		for (;;) {
			res = f_readdir(&dir, &fno); // next file in firectory
			if (res != FR_OK)
				return res; // filesystem error

			if (fno.fname[0] == 0) {
				fname[0] = 0;
				break;
			} // no more files found -> exit loop

			if (fno.fname[0] == '.')
				continue; // ignore files starting with a .

			i = str_len(fno.fname);
			if (i == 0xFFFFFFFF)
				return INVALID_FILENAME; // invalid file name

			// check for extension at the end of filename
			if (fno.fname[i - 4] == ext[0] && upper(fno.fname[i - 3]) == upper(ext[1]) &&
				upper(fno.fname[i - 2]) == upper(ext[2]) && upper(fno.fname[i - 1]) == upper(ext[3]))
			{
				fnum++;
				if (used_from_folder[fnum - 1]) {
					continue;
				} // if file already used, move on to next file
				else
				{
					if (str_len(fno.fname) > (FF_MAX_LFN - 2)) {
						used_from_folder[fnum - 1] = 1;
						continue;
					} // if filename is too long: Mark as 'used' and look for next file
					if ((str_cmp_alpha(firstf_name, fno.fname) > 0)) // if found file comes first alphabetically
					{
						firstf_num = fnum - 1;			 // set number of the first file to the current file number
						str_cpy(firstf_name, fno.fname); // set the name of the first file to the current file name
					}
				}
			}
		}

		// Close folder
		f_closedir(&dir);

		if (firstf_num == 0xFFFF)
			return NO_MORE_AVAILABLE_FILES; // if no more files available: return accordingly

		// Return next filename, in alphabetical order
		str_cpy(fname, firstf_name);	  // use first filename found alphabetically
		used_from_folder[firstf_num] = 1; // mark file as found
		return FR_OK;
	}
};
