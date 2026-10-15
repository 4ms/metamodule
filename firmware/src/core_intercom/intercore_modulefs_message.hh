#pragma once
#include "core_intercom/intercore_types.hh"
#include "ff.h"
#include "fs/volumes.hh"
#include "util/static_string.hh"
#include <span>
#include <string_view>
#include <variant>

namespace MetaModule
{

namespace IntercoreModuleFS
{

// These messages cross the core boundary: fixed-width members only (see
// intercore_types.hh). Buffers are InterCoreSpans into non-cacheable RAM.
//
// FatFs objects (FIL/DIR) live on the filesystem core only; the other core
// addresses them with an FsHandle (an index into the fs core's open-object
// tables). Responses to file operations carry FsFileState so the client can
// cache fptr/size/err locally (f_tell/f_size/f_eof don't need a round-trip).

using FsHandle = uint32_t;
inline constexpr FsHandle InvalidFsHandle = 0xFFFF'FFFF;

// File state after an operation, returned by the fs core
struct FsFileState {
	uint64_t fptr{};
	uint64_t objsize{};
	uint32_t err{};
};

struct None {};

struct Open {
	FsHandle fil = InvalidFsHandle; // response: valid handle, or Invalid on failure
	FsFileState state{};
	StaticString<255> path;
	uint8_t access_mode{};
	FRESULT res{};
};

struct Close {
	FsHandle fil = InvalidFsHandle;
	FRESULT res{};
};

struct Read {
	FsHandle fil = InvalidFsHandle;
	FsFileState state{};
	InterCoreSpan<char> buffer;
	uint32_t bytes_read{};
	FRESULT res{};
};

struct GetS {
	FsHandle fil = InvalidFsHandle;
	FsFileState state{};
	InterCoreSpan<char> buffer;
	uint32_t bytes_read{};
	uint32_t res_ok{}; // 1 if f_gets returned non-null (buffer holds the string)
};

struct Seek {
	FsHandle fil = InvalidFsHandle;
	FsFileState state{};
	uint64_t file_offset{};
	enum class Whence : uint32_t { CurrentPos, Beginning, End } whence{Whence::CurrentPos};
	FRESULT res{};
};

struct OpenDir {
	FsHandle dir = InvalidFsHandle; // response: valid handle, or Invalid on failure
	StaticString<255> path;
	FRESULT res{};
};

struct CloseDir {
	FsHandle dir = InvalidFsHandle;
	FRESULT res{};
};

struct ReadDir {
	FsHandle dir = InvalidFsHandle;
	FILINFO info{};
	FRESULT res{};
};

struct Stat {
	StaticString<255> path;
	FILINFO info{};
	FRESULT res{};
};

struct FindFirst {
	FsHandle dir = InvalidFsHandle; // response: valid handle (f_findfirst opens the dir)
	FILINFO info{};
	StaticString<255> path;
	StaticString<63> pattern;
	FRESULT res{};
};

struct FindNext {
	FsHandle dir = InvalidFsHandle;
	FILINFO info{};
	FRESULT res{};
};

struct MkDir {
	StaticString<255> path;
	FRESULT res{};
};

struct Write {
	FsHandle fil = InvalidFsHandle;
	FsFileState state{};
	InterCoreSpan<const char> buffer;
	uint32_t bytes_written{};
	FRESULT res{};
};

struct Sync {
	FsHandle fil = InvalidFsHandle;
	FsFileState state{};
	FRESULT res{};
};

struct Trunc {
	FsHandle fil = InvalidFsHandle;
	FsFileState state{};
	FRESULT res{};
};

struct Puts {
	FsHandle fil = InvalidFsHandle;
	FsFileState state{};
	InterCoreSpan<const char> buffer;
	uint32_t bytes_written{};
};

struct Unlink {
	StaticString<255> path;
	FRESULT res{};
};

struct Rename {
	StaticString<255> old_path;
	StaticString<255> new_path;
	FRESULT res{};
};

struct Utime {
	StaticString<255> path;
	FILINFO info{};
	FRESULT res{};
};

// Business logic uses the std::variant (std::visit etc.); the shared-memory
// representation is the fixed-layout IccMessage. Conversions happen at the
// transport boundary (FsProxy / ModuleFSMessageHandler).
using Message = std::variant<None,
							 Open,
							 Close,
							 Read,
							 GetS,
							 Seek,
							 OpenDir,
							 CloseDir,
							 ReadDir,
							 Stat,
							 FindFirst,
							 FindNext,
							 MkDir,
							 Write,
							 Sync,
							 Trunc,
							 Puts,
							 Unlink,
							 Rename,
							 Utime>;

using IccMessage = InterCoreVariant<None,
									Open,
									Close,
									Read,
									GetS,
									Seek,
									OpenDir,
									CloseDir,
									ReadDir,
									Stat,
									FindFirst,
									FindNext,
									MkDir,
									Write,
									Sync,
									Trunc,
									Puts,
									Unlink,
									Rename,
									Utime>;

static constexpr size_t MessageSize = sizeof(IccMessage);

// Pin the cross-core ABI: identical on both cores' builds (and the simulator).
// FILINFO layout depends on the FatFs config, which must match on both cores.
static_assert(sizeof(FILINFO) == 288, "FatFs configs must match on both cores");
static_assert(std::is_trivially_copyable_v<IccMessage>);
#if !defined(SIMULATOR)
static_assert(MessageSize == 632, "Cross-core struct layout changed: update both cores' builds together");
#endif

} // namespace IntercoreModuleFS

} // namespace MetaModule
