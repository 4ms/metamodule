#include "filesystem.hh"
#include <cstdio>

// These are used by newlib to provide libc filesystem and io functions

extern "C" {
int _open(const char *filename, int flags, int mode) {
	auto res = MetaModule::Filesystem::open(filename, flags, mode);
	if (res < 0) {
		// Can debug fs errors here
	}
	return res;
}

int _close(int fd) {
	auto res = MetaModule::Filesystem::close(fd);
	if (res < 0) {
		// Can debug fs errors here
	}
	return res;
}

int _lseek(int fd, int offset, int whenc) {
	auto res = MetaModule::Filesystem::lseek(fd, offset, whenc);
	if (res < 0) {
		// Can debug fs errors here
	}
	return res;
}

int _read(int fd, char *ptr, int len) {
	auto res = MetaModule::Filesystem::read(fd, ptr, len);
	if (res < 0) {
		// Can debug fs errors here
	}
	return res;
}

int _fstat(int fd, struct stat *st) {
	auto res = MetaModule::Filesystem::fstat(fd, st);
	if (res < 0) {
		// Can debug fs errors here
	}
	return res;
}

int _isatty(int fd) {
	auto res = MetaModule::Filesystem::isatty(fd);
	if (res < 0) {
		// Can debug fs errors here
	}
	return res;
}

int _stat(const char *filename, struct stat *st) {
	auto res = MetaModule::Filesystem::stat(filename, st);
	if (res < 0) {
		// Can debug fs errors here
	}
	return res;
}

int _write(int fd, const char *ptr, int len) {
	auto res = MetaModule::Filesystem::write(fd, ptr, len);
	if (res < 0) {
		// Can debug fs errors here
	}
	return res;
}
}
