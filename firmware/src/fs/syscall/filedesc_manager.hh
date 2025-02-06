#pragma once
#include "ff.h"
#include "volumes.hh"
#include <optional>

namespace MetaModule
{

struct FileDesc {
	FIL *fatfil = nullptr;
	Volume vol{Volume::MaxVolumes};
};

namespace FileDescManager
{

void init();

std::optional<int> alloc_file();
void dealloc_file(size_t fd);

FileDesc *filedesc(size_t fd);
int isatty(int fd);

} // namespace FileDescManager
} // namespace MetaModule
