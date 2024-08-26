#pragma once
#include "ff.h"
#include "fs/volumes.hh"
#include <span>
#include <string_view>

namespace MetaModule
{

struct IntercoreModuleFSMessage {
	enum MessageType : uint32_t {
		None,
		FatFsOpMessage,

		NumRequests,
	};

	enum FatFsOp : uint8_t { Noop, Open, Close, Read, Seek, Opendir, Closedir, Readdir, Stat };

	MessageType message_type = MessageType::None;
	std::span<char> buffer;
	std::string_view path;

	uint32_t fatfs_req_id{};
	FatFsOp fatfs_op{FatFsOp::Noop};
	FIL *fil{};
	DIR *dir{};
	uint8_t mode{};
	uint64_t file_offset{};
	FRESULT res;
};

} // namespace MetaModule
