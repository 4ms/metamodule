#include "ff.h"
#include "fs_proxy.hh"
#include <memory>

namespace MetaModule
{

// Goes between fs syscall wrappers and inter-core comunication.
// For SD and USB, not for RamDisk
class FsSyscallProxy {
public:
	FsSyscallProxy();
	~FsSyscallProxy();

	bool open(std::string_view path, FIL *fil, uint8_t mode);
	int close(FIL *fil);
	uint64_t seek(FIL *fil, int offset, int whence);
	std::optional<size_t> read(FIL *fil, std::span<char> buffer);

private:
	std::unique_ptr<FsProxy> impl;
};

} // namespace MetaModule
