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
	// TODO
	return -1;
}

int dirfd(DIR *) {
	// TODO
	return -1;
}

DIR *fdopendir(int) {
	// TODO
	return nullptr;
}

int readdir_r(DIR *dir, struct dirent *dirent, struct dirent **) {
	if (dirent) {
		// TODO: is this correct?
		dirent = MetaModule::Filesystem::readdir(dir);
	}
	return dirent ? 0 : -1;
}

void rewinddir(DIR *dir) {
	MetaModule::Filesystem::rewinddir(dir);
}

int scandir(const char *,
			struct dirent ***,
			int (*)(const struct dirent *),
			int (*)(const struct dirent **, const struct dirent **)) {
	// TODO
	return -1;
}

void seekdir(DIR *, long) {
	// TODO
}

long telldir(DIR *) {
	// TODO
	return -1;
}
