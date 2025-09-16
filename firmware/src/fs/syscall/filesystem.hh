#pragma once
#include <cstdio>
#include <string_view>

struct DIR;
struct dirent;
struct stat;
class FatFileIO;

namespace MetaModule
{

namespace Filesystem
{

void init(FatFileIO &ramdisk);

int open(const char *filename, int flags, int mode);
int lseek(int fd, int offset, int whence);
int read(int fd, char *ptr, int len);
int close(int fd);

int write(int fd, const char *ptr, int len);

int isatty(int fd);
int fstat(int fd, struct stat *st);
int stat(const char *filename, struct stat *st);

int link(const char *oldname, const char *newname);
int unlink(const char *path);
int rename(const char *oldname, const char *newname);

DIR *opendir(std::string_view fullpath);
dirent *readdir(DIR *dir);
void rewinddir(DIR *dir);
int closedir(DIR *dir);

}; // namespace Filesystem

} // namespace MetaModule
