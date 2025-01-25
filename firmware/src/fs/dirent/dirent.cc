#include "filesystem/dirent.h"
#include "ff.h"

int alphasort(const struct dirent **, const struct dirent **) {
	return -1;
}

int closedir(DIR *) {
	return -1;
}

int dirfd(DIR *) {
	return -1;
}

DIR *fdopendir(int) {
	return nullptr;
}

DIR *opendir(const char *) {
	return nullptr;
}

struct dirent *readdir(DIR *) {
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
