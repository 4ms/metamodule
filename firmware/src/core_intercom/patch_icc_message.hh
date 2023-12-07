#pragma once
#include "fs/volumes.hh"
#include <array>
#include <cstdint>

namespace MetaModule
{
// ICC = Message passed between cores using InterCoreComm, to load patches and lists of patches
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
	std::array<char, 255> filename;
	Volume vol_id;

	// Note: return type is void because gcc gives a warning for `volatile T&operator=(const T&){...}`
	// warning: implicit dereference will not access object of type 'volatile T' in statement
	// This is because the dereference in `*this` causes a read of memory, but the read value is ignored.
	void operator=(const IntercoreStorageMessage &msg) volatile { //NOLINT
		message_type = msg.message_type;
		bytes_read = msg.bytes_read;
		patch_id = msg.patch_id;
		vol_id = msg.vol_id;
	}

	IntercoreStorageMessage &operator=(volatile IntercoreStorageMessage &msg) { //NOLINT
		this->message_type = msg.message_type;
		this->bytes_read = msg.bytes_read;
		this->patch_id = msg.patch_id;
		this->vol_id = msg.vol_id;
		return *this;
	}
};
} // namespace MetaModule
