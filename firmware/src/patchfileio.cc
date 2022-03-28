#include "patchfileio.hh"
#include "patchlist.hh"

//TODO: make a DirIterator class in FileIO, so we don't need to include ff.h here
//template<typename Action>
//void for_each_file_regex(Disk disk, std::string_view regex, Action action);
#include "ff.h"

namespace MetaModule::PatchFileIO
{

bool create_default_files(Disk disk) {
	uint8_t *default_patch;

	uint32_t len = PatchList::get_default_patch_data(0, default_patch);
	if (!FileIO::create_file(PatchList::get_default_patch_filename(0), {default_patch, len}))
		return false;

	len = PatchList::get_default_patch_data(1, default_patch);
	if (!FileIO::create_file(PatchList::get_default_patch_filename(1), {default_patch, len}))
		return false;

	return true;
}

void load_patches_from_disk(Disk disk, PatchList &patch_list) {
	//TODO: compare stack buffer vs dynamic buffer
	constexpr size_t MaxFileSize = 32768;
	char buf[MaxFileSize];
	uint32_t filesize;
	DIR dj;
	FILINFO fileinfo;

	patch_list.set_status(PatchList::Status::Loading);
	patch_list.clear_all_patches();

	auto res = f_findfirst(&dj, &fileinfo, "", "*.yml");
	while (res == FR_OK && fileinfo.fname[0]) {
		// Skip dot files
		if (fileinfo.fname[0] == '.')
			continue;
		printf("Found patch file: %s, Reading... ", fileinfo.fname);
		filesize = FileIO::read_file(fileinfo.fname, buf, MaxFileSize);

		if (filesize == MaxFileSize) {
			printf("File exceeds %zu bytes, too big. Skipping\r\n", MaxFileSize);
			continue;
		}
		if (!filesize) {
			printf("File cannot be read. Skipping\r\n");
			continue;
		}
		printf("Read %d bytes.. parsing... ", filesize);
		patch_list.add_patch_from_yaml({buf, filesize});

		res = f_findnext(&dj, &fileinfo);
	}
	// NumPatches = _patch_data.size();

	patch_list.set_status(PatchList::Status::Ready);
}

} // namespace MetaModule::PatchFileIO
