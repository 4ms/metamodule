#pragma once
#include "filesystem/dirent.h"
#include "littlefs/lfs.h"
#include "volumes.hh"
#include <optional>

namespace MetaModule
{

using FileT = lfs_file_t;
using DirT = lfs_dir_t;

struct FileDesc {
	FileT *fil = nullptr;
	Volume vol{Volume::MaxVolumes};
};

struct DirDesc {
	DirT *dir;
	Volume vol;
	struct dirent cur_entry;

	DirDesc()
		: dir{nullptr}
		, vol{Volume::MaxVolumes} {
		cur_entry.d_name[0] = '\0';
	}
};

namespace FileDescManager
{

void init();

std::optional<int> alloc_file();
void dealloc_file(size_t fd);

FileDesc *filedesc(size_t fd);
int isatty(int fd);

DirDesc *alloc_dir();
bool dealloc_dir(DirT *dir);
bool dealloc_dir(DirDesc *dirdesc);

DirDesc *dirdesc(DirT *dir);

} // namespace FileDescManager
} // namespace MetaModule
