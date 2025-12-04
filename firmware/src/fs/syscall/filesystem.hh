#pragma once
#include "littlefs/norflash_lfs.hh"
#include "norflash_layout.hh"
#include <string_view>

struct DIR;
struct dirent;
struct stat;
class FatFileIO;

namespace MetaModule
{

namespace Filesystem
{

using PatchVolFileIO = LfsFileIO<PatchVolFlashOffset, PatchVolFlashSize>;
void init(PatchVolFileIO &littlefs_io);

int open(const char *filename, int flags, int mode);
int lseek(int fd, int offset, int whence);
int read(int fd, char *ptr, int len);
int close(int fd);

int write(int fd, const char *ptr, int len);

int isatty(int fd);
int fstat(int fd, struct stat *st);
int stat(const char *filename, struct stat *st);

DIR *opendir(std::string_view fullpath);
dirent *readdir(DIR *dir);
void rewinddir(DIR *dir);
int closedir(DIR *dir);

}; // namespace Filesystem

} // namespace MetaModule
