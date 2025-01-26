#include "filedesc_manager.hh"
#include <algorithm>
#include <array>
#include <cstring>
#include <optional>
#include <unistd.h>
#include <vector>

namespace MetaModule::FileDescManager
{

static constexpr auto MaxOpenFiles = 64;
static constexpr auto MaxOpenDirs = 8;

// Newlib uses particular file descriptors for stdout, stdin, and stderr:
static constexpr auto FirstFileFD = 3;
static_assert(FirstFileFD > STDIN_FILENO);
static_assert(FirstFileFD > STDOUT_FILENO);
static_assert(FirstFileFD > STDERR_FILENO);

static std::array<FileDesc, MaxOpenFiles> descriptors{};
static std::array<DirDesc, MaxOpenDirs> dir_scriptors{};

static int index(size_t fd) {
	return fd - FirstFileFD;
}

static bool fd_is_file(int fd) {
	return (index(fd) >= 0 && index(fd) < MaxOpenFiles && descriptors[index(fd)].fatfil != nullptr);
}

int isatty(int fd) {
	return fd == STDOUT_FILENO || fd == STDIN_FILENO || fd == STDERR_FILENO;
}

void init() {
	for (auto &f : descriptors) {
		f.fatfil = nullptr;
		f.vol = Volume::MaxVolumes;
	}

	for (auto &d : dir_scriptors) {
		d.dir = nullptr;
		d.cur_entry.d_name[0] = '\0';
	}
}

std::optional<int> alloc_file() {
	auto it = std::ranges::find_if(descriptors, [](auto &f) { return f.fatfil == nullptr; });

	if (it != descriptors.end()) {
		auto fd_idx = std::distance(descriptors.begin(), it);
		descriptors[fd_idx].fatfil = new FIL;
		return fd_idx + FirstFileFD;
	} else {
		return {};
	}
}

void dealloc_file(size_t fd) {
	if (fd_is_file(fd)) {
		delete descriptors[index(fd)].fatfil;
		descriptors[index(fd)].fatfil = nullptr;
		descriptors[index(fd)].vol = Volume::MaxVolumes;
	}
}

FileDesc *filedesc(size_t fd) {
	if (fd_is_file(fd)) {
		return &descriptors[index(fd)];
	} else {
		return nullptr;
	}
}

DirDesc *alloc_dir() {
	auto it = std::ranges::find(dir_scriptors, nullptr, &DirDesc::dir);

	if (it != dir_scriptors.end()) {
		auto d_idx = std::distance(dir_scriptors.begin(), it);
		dir_scriptors[d_idx].dir = new DIR;
		return &dir_scriptors[d_idx];
	} else {
		return nullptr;
	}
}

void dealloc_dir(DirDesc *dir) {
	if (!dir)
		return;

	auto it = std::ranges::find(dir_scriptors, dir->dir, &DirDesc::dir);

	if (it != dir_scriptors.end()) {
		auto d_idx = std::distance(dir_scriptors.begin(), it);
		if (d_idx >= 0 && d_idx < (int)dir_scriptors.size()) {
			delete dir_scriptors[d_idx].dir;
			dir_scriptors[d_idx].dir = nullptr;
			dir_scriptors[d_idx].vol = Volume::MaxVolumes;
			dir_scriptors[d_idx].cur_entry.d_name[0] = '\0';
		}
	}
}

DirDesc *dirdesc(DIR *dir) {
	if (!dir)
		return nullptr;

	auto it = std::ranges::find(dir_scriptors, dir, &DirDesc::dir);

	if (it != dir_scriptors.end()) {
		auto d_idx = std::distance(dir_scriptors.begin(), it);
		if (d_idx >= 0 && d_idx < (int)dir_scriptors.size())
			return &dir_scriptors[d_idx];
	}

	return nullptr;
}

}; // namespace MetaModule::FileDescManager
