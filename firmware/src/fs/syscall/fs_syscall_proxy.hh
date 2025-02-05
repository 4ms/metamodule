#include "ff.h"
#include "fs_proxy.hh"
#include <memory>

namespace MetaModule
{

// Goes between fs syscall wrappers and inter-core comunication.
// For SD and USB, not for RamDisk
// TODO: make this a DiskDevice* (see TODO in fileio_t.hh)
class FsSyscallProxy {
public:
	FsSyscallProxy();
	~FsSyscallProxy();

	bool open(std::string_view path, FIL *fil, uint8_t mode);
	int close(FIL *fil);
	uint64_t seek(FIL *fil, int offset, int whence);
	std::optional<size_t> read(FIL *fil, std::span<char> buffer);

	bool stat(std::string_view path, FILINFO *info);

	bool opendir(std::string_view path, DIR *dir);
	bool closedir(DIR *dir);
	bool readdir(DIR *dir, FILINFO *info);

	bool findfirst(DIR *dir, FILINFO *info, std::string_view path, std::string_view pattern);
	bool findnext(DIR *dir, FILINFO *info);

	bool mkdir(std::string_view path);
	std::optional<size_t> write(FIL *fil, std::span<const char> data);
	bool sync(FIL *fil);
	bool trunc(FIL *fil);

	int gets(FIL *fil, std::span<char> data);
	int puts(FIL *fil, std::string_view data);

	bool unlink(std::string_view path);
	bool rename(std::string_view old_path, std::string_view new_path);
	bool utime(std::string_view path, uint32_t timestamp);

private:
	std::unique_ptr<FsProxy> impl;
};

} // namespace MetaModule
