#include "filesystem.hh"
#include "pr_dbg.hh"
#include <cstdio>

extern "C" {
int _open(const char *filename, int flags, int mode) {
	return MetaModule::Filesystem::open(filename, flags, mode);
}

int _close(int fd) {
	return MetaModule::Filesystem::close(fd);
}

int _lseek(int fd, int offset, int whenc) {
	return MetaModule::Filesystem::lseek(fd, offset, whenc);
}

int _read(int fd, char *ptr, int len) {
	return MetaModule::Filesystem::read(fd, ptr, len);
}

int _fstat(int fd, struct stat *st) {
	return MetaModule::Filesystem::fstat(fd, st);
}

int _isatty(int fd) {
	return MetaModule::Filesystem::isatty(fd);
}
}
