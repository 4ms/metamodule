#pragma once
#include "dynload/plugin_file_list.hh"
#include "fs/volumes.hh"
#include "patch_file/patch_dir_list.hh"
#include "util/static_string.hh"
#include <array>
#include <cstdint>
#include <span>
#include <variant>

namespace MetaModule
{
struct PatchFileList;

// ICC = Message passed between A7 and M4 cores using InterCoreComm, to access storage media (SD/USB) from A7
struct IntercoreStorageMessage {
	enum MessageType : uint32_t {
		None,

		RequestRefreshPatchList,
		PatchListChanged,
		PatchListUnchanged,

		RequestLoadFile,
		LoadFileFailed,
		LoadFileOK,

		RequestFirmwareFile,
		FirmwareFileNotFound,
		FirmwareFileFound,

		StartChecksumCompare,
		ChecksumMatch,
		ChecksumMismatch,
		ChecksumFailed,

		StartFlashing, // write to Flash or WifiExpander
		FlashingOk,
		FlashingFailed,

		RequestReadFlash,
		ReadFlashOk,
		ReadFlashFailed,

		RequestWriteFile,
		WriteFileFail,
		WriteFileOK,

		RequestFactoryResetPatches,
		FactoryResetPatchesDone,

		RequestPluginFileList,
		PluginFileListOK,
		PluginFileListFail,

		RequestCopyPluginAssets,
		CopyPluginAssetsOK,
		CopyPluginAssetsFail,

		RequestDeleteFile,
		DeleteFileFailed,
		DeleteFileSuccess,

		NumRequests,
	};

	MessageType message_type = MessageType::None;

	uint32_t bytes_read{};
	Volume vol_id;
	bool force_refresh;
	std::span<char> buffer;
	PatchDirList *patch_dir_list;
	StaticString<255> filename;

	uint32_t address;
	uint32_t length;
	StaticString<32> checksum;
	uint32_t *bytes_processed;
	enum FlashTarget : uint8_t { WIFI, QSPI };
	FlashTarget flashTarget;

	PluginFileList *plugin_file_list;
};

constexpr static auto IntercoreStorageMessageSize = sizeof(IntercoreStorageMessage);

///////////////////////////////////////
// TODO: Use this instead of MessageType

// struct PatchListMsg {
// 	PatchFileList &patch_list;
// 	enum class Result { Unchanged, Changed } result;
// };
// struct PatchData;
// struct PatchDataLoadMsg {
// 	PatchData &patch_data;
// 	Volume vol;
// 	unsigned patch_id; //change to filename
// 	// StaticString<255> filename;
// 	std::span<char> buffer;
// 	enum class Result { LoadFailed, LoadOK } result;
// };
// struct FirmwareFindMsg {
// 	StaticString<255> filename;
// 	Volume vol_id;
// 	uint32_t filesize;
// 	enum class Result { Unchanged, FileFound, NotFound } result;
// };
// struct FileLoadMsg {
// 	std::span<char> buffer;
// 	StaticString<255> filename;
// 	Volume vol_id;
// 	enum class Result { Failed, Success } result;
// };

// using Message = std::variant<PatchListMsg, PatchDataLoadMsg, FirmwareFindMsg, FileLoadMsg>;

} // namespace MetaModule
