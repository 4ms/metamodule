#pragma once
#include "fs/volumes.hh"
#include "util/static_string.hh"
#include <array>
#include <cstdint>
#include <span>
#include <variant>

namespace MetaModule
{
// ICC = Message passed between A7 and M4 cores using InterCoreComm, to access storage media (SD/USB) from A7
struct IntercoreStorageMessage {
	enum MessageType : uint32_t {
		None,

		RequestRefreshPatchList,
		PatchListChanged,
		PatchListUnchanged,

		RequestPatchData,
		PatchDataLoadFail,
		PatchDataLoaded,

		RequestFirmwareFile,
		FirmwareFileUnchanged,
		FirmwareFileNotFound,
		FirmwareFileFound,

		RequestLoadFirmwareToRam,
		LoadFirmwareToRamFailed,
		LoadFirmwareToRamSuccess,

		NumRequests,
	};
	MessageType message_type;

	uint32_t bytes_read;
	uint32_t patch_id; //DEPRECATE: use filename
	StaticString<255> filename;
	Volume vol_id;
	std::span<char> buffer;
	uint32_t write_address;

	///////////////////////////////////////
	// TODO: Use this instead of MessageType

	struct PatchFileList;
	struct PatchData;

	struct PatchListMsg {
		PatchFileList &patch_list;
		enum class Result { Unchanged, Changed } result;
	};
	struct PatchDataLoadMsg {
		PatchData &patch_data;
		Volume vol;
		unsigned patch_id; //change to filename
		// StaticString<255> filename;
		enum class Result { LoadFailed, LoadOK } result;
	};
	struct FirmwareFindMsg {
		StaticString<255> filename;
		Volume vol_id;
		uint32_t filesize;
		enum class Result { Unchanged, FileFound, NotFound } result;
	};
	struct FileLoadMsg {
		std::span<char> buffer;
		StaticString<255> filename;
		Volume vol_id;
		enum class Result { Failed, Success } result;
	};

	using Message = std::variant<PatchListMsg, PatchDataLoadMsg, FirmwareFindMsg, FileLoadMsg>;
	////////////////////////////////////////

	// Note: return type is void because gcc gives a warning for `volatile T&operator=(const T&){...}`
	// warning: implicit dereference will not access object of type 'volatile T' in statement
	// This is because the dereference in `*this` causes a read of memory, but the read value is ignored.
	// void operator=(const IntercoreStorageMessage &msg) { //NOLINT
	// 	this->message_type = msg.message_type;
	// 	this->bytes_read = msg.bytes_read;
	// 	this->patch_id = msg.patch_id;
	// 	this->filename.copy(msg.filename);
	// 	this->vol_id = msg.vol_id;
	// 	this->buffer = msg.buffer;
	// 	this->write_address = msg.write_address;
	// }

	// IntercoreStorageMessage &operator=(IntercoreStorageMessage &msg) { //NOLINT
	// 	this->message_type = msg.message_type;
	// 	this->bytes_read = msg.bytes_read;
	// 	this->patch_id = msg.patch_id;
	// 	this->filename.copy(msg.filename);
	// 	this->vol_id = msg.vol_id;
	// 	this->buffer = msg.buffer;
	// 	this->write_address = msg.write_address;
	// 	return *this;
	// }
};

constexpr static auto IntercoreStorageMessageSize = sizeof(IntercoreStorageMessage);

} // namespace MetaModule
