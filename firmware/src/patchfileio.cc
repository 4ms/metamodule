#include "patchfileio.hh"
#include "patchlist.hh"
#include "printf.h"

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

bool factory_reset(Disk disk) {
	bool ok = FileIO::format_disk(disk);
	if (ok)
		ok = PatchFileIO::create_default_files(disk);
	if (ok)
		ok = FileIO::unmount_disk(disk);
	if (ok)
		return true;

	printf("Failed to create filesystem and default patches\r\n");
	return false;
}

void load_patches_from_disk(Disk disk, PatchList &patch_list) {
	constexpr size_t MaxFileSize = 32768;
	//TODO: compare stack buffer vs dynamic buffer
	char buf[MaxFileSize];

	patch_list.set_status(PatchList::Status::Loading);
	patch_list.clear_all_patches();

	FileIO::for_each_file_regex(disk, "*.yml", [&](const char *fname) {
		if (fname[0] == '.')
			return;

		printf("Found patch file: %s, Reading... ", fname);
		uint32_t filesize = FileIO::read_file(fname, buf, MaxFileSize);

		if (filesize == MaxFileSize) {
			printf("File exceeds %zu bytes, too big. Skipping\r\n", MaxFileSize);
			return;
		}
		if (!filesize) {
			printf("File cannot be read. Skipping\r\n");
			return;
		}
		printf("Read %d bytes.. parsing... ", filesize);
		patch_list.add_patch_from_yaml({buf, filesize});
	});

	patch_list.set_status(PatchList::Status::Ready);
}

} // namespace MetaModule::PatchFileIO
