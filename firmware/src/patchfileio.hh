#pragma once
#include "fatfs/ramdisk_fileio.hh"
#include "patchlist.hh"

namespace MetaModule::PatchFileIO
{
bool factory_reset(Disk disk);
bool create_default_files(Disk disk);
void load_patches_from_disk(Disk disk, PatchList &patch_list);

} // namespace MetaModule::PatchFileIO
