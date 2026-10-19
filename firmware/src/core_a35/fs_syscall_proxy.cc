#include "fs/syscall/fs_syscall_proxy.hh"
#include "pr_dbg.hh"

// MP2 version of src/fs/syscall/fs_syscall_proxy.cc, which sends libc file access on the SD card
// and USB drive (fopen("sdc:/..."), etc) to the M4.
// FIXME: send them to the M33 (it needs to answer IntercoreModuleFS messages, like MP1's M4).
// Until then, files on the SD card and USB can't be opened this way. The RamDisk works: it's
// accessed directly (src/fs/syscall/filesystem.cc).

namespace MetaModule
{

FsSyscallProxy::FsSyscallProxy() = default;
FsSyscallProxy::~FsSyscallProxy() = default;

bool FsSyscallProxy::open(std::string_view path, FIL *, uint8_t) {
	pr_warn("Can't open %.*s: file access on the SD card and USB isn't ported to MP2 yet\n",
			int(path.size()),
			path.data());
	return false;
}

int FsSyscallProxy::close(FIL *) {
	return -1;
}

uint64_t FsSyscallProxy::seek(FIL *, int, int) {
	return 0;
}

std::optional<size_t> FsSyscallProxy::read(FIL *, std::span<char>) {
	return std::nullopt;
}

bool FsSyscallProxy::stat(std::string_view, FILINFO *) {
	return false;
}

bool FsSyscallProxy::opendir(std::string_view, DIR *) {
	return false;
}

bool FsSyscallProxy::closedir(DIR *) {
	return false;
}

bool FsSyscallProxy::readdir(DIR *, FILINFO *) {
	return false;
}

bool FsSyscallProxy::findfirst(DIR *, FILINFO *, std::string_view, std::string_view) {
	return false;
}

bool FsSyscallProxy::findnext(DIR *, FILINFO *) {
	return false;
}

bool FsSyscallProxy::mkdir(std::string_view) {
	return false;
}

std::optional<size_t> FsSyscallProxy::write(FIL *, std::span<const char>) {
	return std::nullopt;
}

bool FsSyscallProxy::sync(FIL *) {
	return false;
}

bool FsSyscallProxy::trunc(FIL *) {
	return false;
}

int FsSyscallProxy::gets(FIL *, std::span<char>) {
	return -1;
}

int FsSyscallProxy::puts(FIL *, std::string_view) {
	return -1;
}

bool FsSyscallProxy::unlink(std::string_view) {
	return false;
}

bool FsSyscallProxy::rename(std::string_view, std::string_view) {
	return false;
}

bool FsSyscallProxy::utime(std::string_view, uint32_t) {
	return false;
}

} // namespace MetaModule
