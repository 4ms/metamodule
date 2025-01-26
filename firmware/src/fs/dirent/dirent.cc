#include "filesystem/dirent.h"
#include "ff.h"
#include "fs/syscall/filesystem.hh"

DIR *opendir(const char *path) {
	return MetaModule::Filesystem::opendir(path);
}

int closedir(DIR *dir) {
	return MetaModule::Filesystem::closedir(dir);
}

struct dirent *readdir(DIR *dir) {
	return MetaModule::Filesystem::readdir(dir);
}

int alphasort(const struct dirent **, const struct dirent **) {
	return -1;
}

int dirfd(DIR *) {
	return -1;
}

DIR *fdopendir(int) {
	return nullptr;
}

int readdir_r(DIR *, struct dirent *, struct dirent **) {
	return -1;
}

void rewinddir(DIR *) {
}

int scandir(const char *,
			struct dirent ***,
			int (*)(const struct dirent *),
			int (*)(const struct dirent **, const struct dirent **)) {
	return -1;
}

void seekdir(DIR *, long) {
}

long telldir(DIR *) {
	return -1;
}
