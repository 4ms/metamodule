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
	return (index(fd) >= 0 && index(fd) < MaxOpenFiles && descriptors[index(fd)].fatfil != nullptr);
}

int isatty(int fd) {
	return fd == STDOUT_FILENO || fd == STDIN_FILENO || fd == STDERR_FILENO;
}

void init() {
	descriptors.clear();
	dir_scriptors.clear();
}

// Potential for race condition if newlib is holding a stale fd
// (that is, it attempts to double-close a file), and we have 3 threads.
// E.g. thread 1 and thread 2 both try to close filedesc 8, and thread 3 tries to open a file:
// T2: fd_is_file(8) → true         // passes check, then stalls
// T1: fd_is_file(8) → true, nulls fields, CAS destroy → OK
// T3: alloc_file()   → CAS create wins slot, writes new pointer
// T2: resumes → nulls fields (clobbers T3's pointer!)
//     CAS destroy succeeds (used_flags was true from T3) → no error logged
// T3 now holds a “live” fd whose fatfil is nullptr and used_flags is false

std::optional<int> alloc_file() {
	// Thread-safe way to find first empty descriptor
	if (auto fd_idx = descriptors.create()) {
		// Default-init a FIL
		fatfil_pool[*fd_idx] = FIL{};
		descriptors[*fd_idx].fatfil = &fatfil_pool[*fd_idx];
		pr_trace("FileDescManager: alloc fd %zu\n", *fd_idx + FirstFileFD);
		return static_cast<int>(*fd_idx + FirstFileFD);
	} else {
		pr_err("FileDescManager::alloc_file failed to create a file\n");
		return {};
	}
}

void dealloc_file(size_t fd) {
	if (fd_is_file(fd)) {
		fatfil_pool[index(fd)].obj.fs = nullptr;
		descriptors[index(fd)].fatfil = nullptr;
		descriptors[index(fd)].vol = Volume::MaxVolumes;

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

DirDesc *alloc_dir() {
	// Thread-safe way to find first empty descriptor
	if (auto d_idx = dir_scriptors.create()) {
		// Default-init a FIL
		dir_pool[*d_idx] = DIR{};
		dir_scriptors[*d_idx].dir = &dir_pool[*d_idx];
		return &dir_scriptors[*d_idx];
	} else
		return nullptr;
}

bool dealloc_dir(DIR *dir) {
	if (!dir)
		return false;

	for (auto i = 0u; i < dir_scriptors.size(); i++) {
		if (dir_scriptors[i].dir == dir) {
			if (dir_scriptors.destroy(i)) {
				dir_scriptors[i].dir = nullptr;
				dir_scriptors[i].vol = Volume::MaxVolumes;
				dir_scriptors[i].cur_entry.d_name[0] = '\0';
				return true;
			}
			// else keep trying
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

	for (auto i = 0u; i < dir_scriptors.size(); i++) {
		if (dir_scriptors[i].dir == dir) {
			return &dir_scriptors[i];
		}
	}

	return nullptr;
}

}; // namespace MetaModule::FileDescManager
