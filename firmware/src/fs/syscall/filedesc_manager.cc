#include "filedesc_manager.hh"
#include "pr_dbg.hh"
#include "util/pool.hh"
#include "util/thread_safe_pool.hh"
#include <algorithm>
#include <array>
#include <cstdio>
#include <cstring>
#include <optional>
#include <reent.h>
#include <unistd.h>

namespace MetaModule::FileDescManager
{

static constexpr auto MaxOpenFiles = 64;
static constexpr auto MaxOpenDirs = 8;

// Newlib uses particular file descriptors for stdout, stdin, and stderr:
static constexpr auto FirstFileFD = 3;
static_assert(FirstFileFD > STDIN_FILENO);
static_assert(FirstFileFD > STDOUT_FILENO);
static_assert(FirstFileFD > STDERR_FILENO);

static cpputil::ThreadSafePool<FileDesc, MaxOpenFiles> descriptors{};
static std::array<FIL, MaxOpenFiles> fatfil_pool{};

static cpputil::ThreadSafePool<DirDesc, MaxOpenDirs> dir_scriptors{};
static std::array<DIR, MaxOpenDirs> dir_pool{};

static int index(size_t fd) {
	return fd - FirstFileFD;
}

static bool fd_is_file(int fd) {
	return (index(fd) >= 0 && index(fd) < MaxOpenFiles && descriptors.is_used(index(fd)));
}

int isatty(int fd) {
	return fd == STDOUT_FILENO || fd == STDIN_FILENO || fd == STDERR_FILENO;
}

void init() {
	descriptors.clear();
	dir_scriptors.clear();

	// Bind each FileDesc to its FIL slot once. The pointer is never mutated again,
	// so concurrent alloc/dealloc on different cores have no plain stores to race on.
	for (size_t i = 0; i < MaxOpenFiles; i++) {
		descriptors[i].fatfil = &fatfil_pool[i];
	}

	for (size_t i = 0; i < MaxOpenDirs; i++) {
		dir_scriptors[i].dir = &dir_pool[i];
	}
}

// Residual stale-fd risk: if newlib double-closes an fd that has already been recycled
// to a new owner, our CAS-destroy can spuriously succeed and free the new owner's slot.
// The new owner's fd then becomes invalid and subsequent ops return -1, but no field
// can be clobbered, so this no longer crashes — it just fails the in-flight operation.

std::optional<int> alloc_file() {
	if (auto fd_idx = descriptors.create()) {
		// Re-init happens here because we have exclusive ownership.
		// This avoids non-atomic stores if we were to init the fields in dealloc_file()
		fatfil_pool[*fd_idx] = FIL{};
		descriptors[*fd_idx].vol = Volume::MaxVolumes;
		pr_trace("FileDescManager: alloc fd %zu\n", *fd_idx + FirstFileFD);
		return static_cast<int>(*fd_idx + FirstFileFD);
	} else {
		pr_err("FileDescManager::alloc_file failed to create a file\n");
		return {};
	}
}

void dealloc_file(size_t fd) {
	if (fd_is_file(fd)) {
		if (!descriptors.destroy(index(fd))) {
			pr_err("FileDescManager error: descriptor %zu was already dealloced\n", fd);
		} else {
			pr_trace("FileDescManager: dealloc fd %zu\n", fd);
		}
	}
}

FileDesc *filedesc(size_t fd) {
	if (fd_is_file(fd)) {
		return &descriptors[index(fd)];
	} else {
		return nullptr;
	}
}

// See comments above alloc_file(), same issue is possible with dirs.
DirDesc *alloc_dir() {
	// Thread-safe way to find first empty descriptor
	if (auto d_idx = dir_scriptors.create()) {
		// Re-init happens here because we have exclusive ownership.
		dir_pool[*d_idx] = DIR{};
		dir_scriptors[*d_idx].vol = Volume::MaxVolumes;
		dir_scriptors[*d_idx].cur_entry.d_name[0] = '\0';
		return &dir_scriptors[*d_idx];
	} else
		return nullptr;
}

bool dealloc_dir(DIR *dir) {
	if (!dir)
		return false;

	for (auto i = 0u; i < dir_scriptors.size(); i++) {
		if (dir_scriptors[i].dir == dir) {
			if (dir_scriptors.destroy(i))
				return true;
			break;
		}
	}

	pr_warn("FileDescManager error: dir was already dealloced\n");
	return false;
}

bool dealloc_dir(DirDesc *dirdesc) {
	if (!dirdesc)
		return false;

	return dealloc_dir(dirdesc->dir);
}

DirDesc *dirdesc(DIR *dir) {
	if (!dir)
		return nullptr;

	// Note: could replace this with auto idx = dir - &dir_pool[0];
	// But we'd be more at risk to injected/corrupted pointers
	for (auto i = 0u; i < dir_scriptors.size(); i++) {
		if (dir_scriptors[i].dir == dir) {
			if (dir_scriptors.is_used(i))
				return &dir_scriptors[i];
			break;
		}
	}

	return nullptr;
}

}; // namespace MetaModule::FileDescManager
