#pragma once
#include "ff.h"
#include "filesystem/dirent.h"
#include "volumes.hh"
#include <optional>

namespace MetaModule
{

struct FileDesc {
	FIL *fatfil = nullptr;
	Volume vol{Volume::MaxVolumes};
};

struct DirDesc {
	DIR *dir = nullptr;
	Volume vol{Volume::MaxVolumes};
	struct dirent cur_entry;
};

namespace FileDescManager
{

void init();

std::optional<int> alloc_file();
void dealloc_file(size_t fd);

FileDesc *filedesc(size_t fd);
int isatty(int fd);

DirDesc *alloc_dir();
bool dealloc_dir(DIR *dir);
bool dealloc_dir(DirDesc *dirdesc);

DirDesc *dirdesc(DIR *dir);

} // namespace FileDescManager
} // namespace MetaModule
