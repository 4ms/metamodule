#include "fs_syscall_proxy.hh"
#include "ff.h"

namespace MetaModule
{

FsSyscallProxy::FsSyscallProxy()
	: impl{std::make_unique<FsProxy>()} {
}

FsSyscallProxy::~FsSyscallProxy() = default;

bool FsSyscallProxy::open(std::string_view path, FIL *fil, uint8_t mode) {
	auto msg = IntercoreModuleFS::Open{
		.fil = *fil, //copy to non-cacheable Message
		.path = path,
		.access_mode = mode,
	};

	pr_trace("A7: open (mode %d) %s => %p\n", msg.access_mode, msg.path.data(), msg.fil);

	if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::Open>(msg, 3000)) {
		pr_trace("A7: Open response = %d\n", response->res);
		*fil = response->fil; //copy back
		return response->res == FR_OK;
	}

	pr_err("Failed to send Open request\n");
	return false;
}

uint64_t FsSyscallProxy::seek(FIL *fil, int offset, int whence) {
	using enum IntercoreModuleFS::Seek::Whence;
	auto msg = IntercoreModuleFS::Seek{
		.fil = *fil,
		.file_offset = (uint64_t)offset,
		.whence = whence == SEEK_CUR ? CurrentPos :
				  whence == SEEK_END ? End :
				  whence == SEEK_SET ? Beginning :
									   CurrentPos,
	};

	pr_trace("A7: seek %p + %d (%d)\n", fil, offset, whence);

	if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::Seek>(msg, 3000)) {
		if (response->res == FR_OK) {
			*fil = response->fil;
			pr_trace("A7: seek response: f_tell is %zu\n", response->fil.fptr);
		}
		pr_err("A7: seek responded with error: %d\n", response->res);
		return response->fil.fptr;
	}

	pr_err("Failed to send seek request\n");
	return 0;
}

std::optional<size_t> FsSyscallProxy::read(FIL *fil, std::span<char> buffer) {
	auto bytes_to_read = buffer.size();

	if (bytes_to_read > impl->file_buffer().size()) {
		pr_err("Cannot f_read %d bytes, max is %zu\n", bytes_to_read, impl->file_buffer().size());
		return {};
	}

	auto msg = IntercoreModuleFS::Read{
		.fil = *fil,
		.buffer = impl->file_buffer().subspan(0, bytes_to_read),
	};

	pr_trace("A7: read %p into {%p, +%zu}\n", fil, buffer.data(), buffer.size());

	if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::Read>(msg, 3000)) {
		std::copy(response->buffer.begin(), std::next(response->buffer.begin(), response->bytes_read), buffer.data());

		*fil = response->fil;
		return response->bytes_read;
	}

	pr_err("Failed to send read request\n");
	return {};
}

int FsSyscallProxy::close(FIL *fil) {
	auto msg = IntercoreModuleFS::Close{
		.fil = *fil,
	};

	pr_trace("A7: close %p\n", fil);

	if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::Close>(msg, 3000)) {
		*fil = response->fil; //copy FIL back
		return response->res;
	}

	pr_err("Failed to send close request\n");
	return -1;
}

bool FsSyscallProxy::stat(std::string_view path, FILINFO *info) {
	auto msg = IntercoreModuleFS::Stat{
		.path = path,
		.info = *info, //copy to non-cacheable message
	};

	pr_trace("A7: stat %s => info %p\n", msg.path.data(), msg.info);

	if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::Stat>(msg, 3000)) {
		pr_trace("A7: Stat response = %d\n", response->res);
		*info = response->info; //copy back
		return response->res == FR_OK;
	}

	pr_err("Failed to send Stat request\n");
	return false;
}

bool FsSyscallProxy::opendir(std::string_view path, DIR *dir) {
	auto msg = IntercoreModuleFS::OpenDir{
		.dir = *dir, //copy to non-cacheable Message
		.path = path,
	};

	pr_trace("A7: opendir %s => %p\n", msg.path.data(), msg.dir);

	if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::OpenDir>(msg, 3000)) {
		pr_trace("A7: Opendir response = %d\n", response->res);
		*dir = response->dir; //copy back
		return response->res == FR_OK;
	}

	pr_err("Failed to send Opendir request\n");
	return false;
}

bool FsSyscallProxy::closedir(DIR *dir) {
	auto msg = IntercoreModuleFS::CloseDir{
		.dir = *dir,
	};

	pr_trace("A7: closedir %p\n", dir);

	if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::CloseDir>(msg, 3000)) {
		*dir = response->dir; //copy DIR back
		return response->res;
	}

	pr_err("Failed to send closedir request\n");
	return false;
}

bool FsSyscallProxy::readdir(DIR *dir, FILINFO *info) {
	auto msg = IntercoreModuleFS::ReadDir{
		.dir = *dir,   //copy
		.info = *info, //copy to non-cacheable message
	};

	pr_trace("A7: ReadDir dir %p => info %p\n", dir, info);

	if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::ReadDir>(msg, 3000)) {
		pr_trace("A7: ReadDir response = %d\n", response->res);
		*dir = response->dir;	//copy back
		*info = response->info; //copy back
		return response->res == FR_OK;
	}

	pr_err("Failed to send ReadDir request\n");
	return false;
}

} // namespace MetaModule
