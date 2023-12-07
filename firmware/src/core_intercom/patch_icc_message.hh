#pragma once
#include "fs/volumes.hh"
#include "util/static_string.hh"
#include <array>
#include <cstdint>

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
		FirmwareFileNotFound,
		FirmwareFileFound,

		NumRequests,
	};
	MessageType message_type;
	uint32_t bytes_read;
	uint32_t patch_id;
	StaticString<255> filename;
	Volume vol_id;

	// Note: return type is void because gcc gives a warning for `volatile T&operator=(const T&){...}`
	// warning: implicit dereference will not access object of type 'volatile T' in statement
	// This is because the dereference in `*this` causes a read of memory, but the read value is ignored.
	void operator=(const IntercoreStorageMessage &msg) volatile { //NOLINT
		message_type = msg.message_type;
		bytes_read = msg.bytes_read;
		patch_id = msg.patch_id;
		filename.copy(msg.filename);
		vol_id = msg.vol_id;
	}

	IntercoreStorageMessage &operator=(volatile IntercoreStorageMessage &msg) { //NOLINT
		this->message_type = msg.message_type;
		this->bytes_read = msg.bytes_read;
		this->patch_id = msg.patch_id;
		this->filename.copy(msg.filename);
		this->vol_id = msg.vol_id;
		return *this;
	}
};

constexpr static auto IntercoreStorageMessageSize = sizeof(IntercoreStorageMessage);

} // namespace MetaModule
