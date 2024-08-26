#pragma once
#include "ff.h"
#include "fs/volumes.hh"
#include "util/static_string.hh"
#include <span>
#include <string_view>
#include <variant>

namespace MetaModule
{

// struct IntercoreModuleFSMessage {
// 	enum MessageType : uint32_t {
// 		None,
// 		Open,
// 		Close,
// 		Read,
// 		Seek,
// 		Opendir,
// 		Closedir,
// 		Readdir,
// 		Stat,
// 	};

// 	MessageType message_type = MessageType::None;

// 	std::span<char> buffer;
// 	StaticString<255> path;

// 	FIL *fil{};
// 	DIR *dir{};
// 	uint8_t mode{};
// 	uint64_t file_offset{};
// 	uint32_t bytes_read{};
// 	FRESULT res;
// };

namespace IntercoreModuleFS
{

struct None {};

struct Open {
	FIL fil{};
	StaticString<255> path;
	uint8_t access_mode{};
	FRESULT res{};
};

struct Close {
	FIL fil{};
	FRESULT res{};
};

struct Read {
	FIL fil{};
	std::span<char> buffer;
	uint32_t bytes_read{};
	FRESULT res{};
};

struct GetS {
	FIL fil{};
	std::span<char> buffer;
	uint32_t bytes_read{};
	FRESULT res{};
};

struct Seek {
	FIL fil{};
	uint64_t file_offset{};
	FRESULT res{};
};

struct OpenDir {
	DIR dir{};
	StaticString<255> path;
	FRESULT res{};
};

struct CloseDir {
	DIR dir{};
	FRESULT res{};
};

struct ReadDir {
	DIR dir{};
	//??
	FRESULT res{};
};

struct Stat {
	StaticString<255> path;
	FILINFO info{};
	FRESULT res{};
};

//280B with DIR* FIL* FILINFO*
//880B with DIR FIL FILINFO
using Message = std::variant<None, Open, Close, Read, GetS, Seek, OpenDir, CloseDir, ReadDir, Stat>;

} // namespace IntercoreModuleFS

} // namespace MetaModule
