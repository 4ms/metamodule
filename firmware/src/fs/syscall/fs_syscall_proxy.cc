#include "fs_syscall_proxy.hh"
#include "ff.h"

namespace MetaModule
{

// #define fs_trace pr_dbg
#define fs_trace(...)

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

	fs_trace("A7: open (mode %d) %s => %p\n", msg.access_mode, msg.path.data(), msg.fil);

	if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::Open>(msg, 3000)) {
		fs_trace("A7: Open response = %d\n", response->res);
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

	pr_dbg("A7: seek %p + %d (%s)\n", fil, offset, whence == SEEK_CUR ? "cur" : whence == SEEK_END ? "end" : "set");

	if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::Seek>(msg, 3000)) {
		if (response->res == FR_OK) {
			*fil = response->fil;
			fs_trace("A7: seek response: f_tell is %llu\n", response->fil.fptr);
		} else
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

	fs_trace("A7: read %p into {%p, +%zu}\n", fil, buffer.data(), buffer.size());

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

	fs_trace("A7: close %p\n", fil);

	if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::Close>(msg, 3000)) {
		*fil = response->fil; //copy FIL back
		return response->res == FR_OK;
	}

	pr_err("Failed to send close request\n");
	return -1;
}

bool FsSyscallProxy::stat(std::string_view path, FILINFO *info) {
	auto msg = IntercoreModuleFS::Stat{
		.path = path,
		.info = *info, //copy to non-cacheable message
	};

	fs_trace("A7: stat %s => info %p\n", msg.path.data(), msg.info);

	if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::Stat>(msg, 3000)) {
		fs_trace("A7: Stat response = %d\n", response->res);
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

	fs_trace("A7: opendir %s => %p\n", msg.path.data(), msg.dir);

	if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::OpenDir>(msg, 3000)) {
		fs_trace("A7: Opendir response = %d\n", response->res);
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

	fs_trace("A7: closedir %p\n", dir);

	if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::CloseDir>(msg, 3000)) {
		*dir = response->dir; //copy DIR back
		return response->res == FR_OK;
	}

	pr_err("Failed to send closedir request\n");
	return false;
}

bool FsSyscallProxy::readdir(DIR *dir, FILINFO *info) {
	auto msg = IntercoreModuleFS::ReadDir{
		.dir = *dir,   //copy
		.info = *info, //copy to non-cacheable message
	};

	fs_trace("A7: ReadDir dir %p => info %p\n", dir, info);

	if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::ReadDir>(msg, 3000)) {
		fs_trace("A7: ReadDir response = %d, name='%.255s'\n", response->res, response->info.fname);
		*dir = response->dir;	//copy back
		*info = response->info; //copy back
		return response->info.fname[0] != '\0';
	}

	pr_err("Failed to send ReadDir request\n");
	return false;
}

std::optional<size_t> FsSyscallProxy::write(FIL *fil, std::span<const char> buffer) {

	auto bytes_remaining = buffer.size();
	auto chunk_start = buffer.begin();

	pr_dbg("A7: write %zu bytes starting with %p, max %zu\n", bytes_remaining, chunk_start, impl->file_buffer().size());

	while (bytes_remaining > 0) {
		auto bytes_to_write = std::min(bytes_remaining, impl->file_buffer().size());

		// Copy given buffer -> impl internal buffer and advance chunk
		auto chunk_end = std::next(chunk_start, bytes_to_write);
		std::copy(chunk_start, chunk_end, impl->file_buffer().begin());

		auto msg = IntercoreModuleFS::Write{
			.fil = *fil,
			.buffer = impl->file_buffer().subspan(0, bytes_to_write),
		};

		pr_dbg("A7: write %p from {%p - %p [+%zu]}\n", fil, chunk_start, chunk_end, bytes_to_write);
		chunk_start = chunk_end;

		if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::Write>(msg, 8000)) {
			*fil = response->fil;

			if (response->bytes_written < bytes_to_write) {
				pr_err("Failed to write, only %zu bytes written. Disk is full?\n", response->bytes_written);
				return {};
			} else if (response->bytes_written == bytes_to_write) {
				bytes_remaining -= bytes_to_write;
			} else {
				pr_err("Internal error: wrote more bytes than requested: %zu\n", response->bytes_written);
				return {};
			}
		} else {
			pr_err("Failed to send write request\n");
			return {};
		}
	}

	return buffer.size();
}

bool FsSyscallProxy::sync(FIL *fil) {
	auto msg = IntercoreModuleFS::Sync{
		.fil = *fil,
	};

	fs_trace("A7: sync %p\n", fil);

	if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::Sync>(msg, 8000)) {
		*fil = response->fil;
		return (response->res == FR_OK);
	}

	pr_err("Failed to send sync request\n");
	return false;
}

bool FsSyscallProxy::mkdir(std::string_view path) {
	if (path.length() == 0)
		return false;

	auto msg = IntercoreModuleFS::MkDir{
		.path = path,
	};

	fs_trace("A7: mkdir %.*s\n", path.data(), path.size());

	if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::MkDir>(msg, 8000)) {
		return response->res == FR_OK;
	}

	pr_err("Failed to send mkdir request\n");
	return false;
}

bool FsSyscallProxy::unlink(std::string_view path) {
	if (path.length() == 0)
		return false;

	auto msg = IntercoreModuleFS::Unlink{
		.path = path,
	};

	fs_trace("A7: unlink %.*s\n", path.data(), path.size());

	if (auto response = impl->get_response_or_timeout<IntercoreModuleFS::Unlink>(msg, 2000)) {
		return response->res == FR_OK;
	}

	pr_err("Failed to send unlink request\n");
	return false;
}

// TODO: implement these and provide a public API

bool FsSyscallProxy::rename(std::string_view old_path, std::string_view new_path) {
	pr_err("FsSyscallProxy::rename not implemented\n");
	return false;
}

bool FsSyscallProxy::findfirst(DIR *dir, FILINFO *info, std::string_view path, std::string_view pattern) {
	pr_err("FsSyscallProxy::findfirst not implemented\n");
	return false;
}

bool FsSyscallProxy::findnext(DIR *dir, FILINFO *info) {
	pr_err("FsSyscallProxy::findnext not implemented\n");
	return false;
}

bool FsSyscallProxy::trunc(FIL *fil) {
	pr_err("FsSyscallProxy::trunc not implemented\n");
	return false;
}

int FsSyscallProxy::gets(FIL *fil, std::span<char> data) {
	pr_err("FsSyscallProxy::gets not implemented\n");
	return -1;
}

int FsSyscallProxy::puts(FIL *fil, std::string_view data) {
	pr_err("FsSyscallProxy::puts not implemented\n");
	return -1;
}

bool FsSyscallProxy::utime(std::string_view path, uint32_t timestamp) {
	pr_err("FsSyscallProxy::utime not implemented\n");
	return false;
}

} // namespace MetaModule
