#include "filedesc_manager.hh"
#include <algorithm>
#include <array>
#include <optional>
#include <unistd.h>

namespace MetaModule::FileDescManager
{

static constexpr auto MaxOpenFiles = 64;

// Newlib uses particular file descriptors for stdout, stdin, and stderr:
static constexpr auto FirstFileFD = 3;
static_assert(FirstFileFD > STDIN_FILENO);
static_assert(FirstFileFD > STDOUT_FILENO);
static_assert(FirstFileFD > STDERR_FILENO);

static std::array<FileDesc, MaxOpenFiles> descriptors{};

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
	for (auto &d : descriptors) {
		d.fatfil = nullptr;
		d.vol = Volume::MaxVolumes;
	}
}

std::optional<int> alloc_file() {
	auto it = std::find_if(descriptors.begin(), descriptors.end(), [](auto &f) { return f.fatfil == nullptr; });

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
	}
}

FileDesc *filedesc(size_t fd) {
	if (fd_is_file(fd)) {
		return &descriptors[index(fd)];
	} else {
		return nullptr;
	}
}

}; // namespace MetaModule::FileDescManager
