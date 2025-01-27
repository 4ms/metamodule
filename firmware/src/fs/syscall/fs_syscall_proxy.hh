#include "disk_device.hh"
#include "fs_proxy.hh"
#include <memory>

namespace MetaModule
{

// DiskDevice for disks managed via inter-core communication
// (SD and USB, not RamDisk)
class FsSyscallProxy : DiskDevice {
public:
	FsSyscallProxy();
	~FsSyscallProxy();

	bool open(std::string_view path, FIL *fil, uint8_t mode) override;
	int close(FIL *fil) override;
	uint64_t seek(FIL *fil, int offset, int whence) override;
	std::optional<size_t> read(FIL *fil, std::span<char> buffer) override;

	bool stat(std::string_view path, FILINFO *info) override;

	bool opendir(std::string_view path, DIR *dir) override;
	bool closedir(DIR *dir) override;
	bool readdir(DIR *dir, FILINFO *info) override;

private:
	std::unique_ptr<FsProxy> impl;
};

} // namespace MetaModule
