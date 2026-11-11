#pragma once
// Host stand-in for src/core_a7/fs_proxy.hh
// Plays the M4 side of the module FS intercore messages against an in-memory file,
// so FsSyscallProxy can be unit tested without IPCC hardware.

#include "core_intercom/intercore_modulefs_message.hh"
#include "pr_dbg.hh"
#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <optional>
#include <span>
#include <string_view>
#include <vector>

namespace MetaModule
{

// Test controls and observations for the fake M4
struct FakeM4 {
	static inline std::vector<char> file;

	// Number of Read requests seen since reset()
	static inline int read_calls = 0;

	// Largest Read request seen since reset()
	static inline size_t max_request = 0;

	// 1-based index of the Read request that fails. -1 means never
	static inline int timeout_on_call = -1;
	static inline int diskerr_on_call = -1;

	static void reset() {
		read_calls = 0;
		max_request = 0;
		timeout_on_call = -1;
		diskerr_on_call = -1;
	}
};

struct FsProxy {
	static inline std::array<char, 128 * 1024> backing_buffer;

	static std::span<char> file_buffer() {
		return backing_buffer;
	}

	template<typename ResponseT>
	static std::optional<ResponseT> get_response_or_timeout(IntercoreModuleFS::Message const &message,
															uint32_t timeout = 3000) {
		auto msg = message;

		if (auto *read = std::get_if<IntercoreModuleFS::Read>(&msg)) {
			FakeM4::read_calls++;
			FakeM4::max_request = std::max(FakeM4::max_request, read->buffer.size());

			if (FakeM4::read_calls == FakeM4::timeout_on_call)
				return {};

			// Poison the shared buffer so bytes left over from an earlier chunk
			// cannot pass for fresh ones
			std::memset(backing_buffer.data(), 0xEE, backing_buffer.size());

			if (FakeM4::read_calls == FakeM4::diskerr_on_call) {
				read->res = FR_DISK_ERR;
				read->fil.err = FR_DISK_ERR;
				read->bytes_read = 0;
			} else {
				size_t pos = std::min<size_t>(read->fil.fptr, FakeM4::file.size());
				size_t num_bytes = std::min(read->buffer.size(), FakeM4::file.size() - pos);
				std::memcpy(read->buffer.data(), FakeM4::file.data() + pos, num_bytes);
				read->fil.fptr += num_bytes;
				read->bytes_read = num_bytes;
				read->res = FR_OK;
			}
		}

		if (auto *response = std::get_if<ResponseT>(&msg))
			return *response;

		return {};
	}
};

} // namespace MetaModule
