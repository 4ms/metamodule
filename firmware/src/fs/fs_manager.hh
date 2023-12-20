#pragma once

#include "core_intercom/intercore_message.hh"
#include "drivers/inter_core_comm.hh"
#include "fs/fatfs/fat_file_io.hh"
#include "fw_update/firmware_file_finder.hh"
#include "patch_file/patch_storage.hh"

namespace MetaModule
{

struct FilesystemManager {

	FilesystemManager(FatFileIO &usb_fileio, FatFileIO &sd_fileio, IntercoreStorageMessage *shared_message)
		: usb_fileio{usb_fileio}
		, sd_fileio{sd_fileio}
		, intercore_comm{*shared_message} {
	}

	void process() {
		auto message = intercore_comm.get_new_message();
		firmware_files.handle_message(message);
		patch_storage.handle_message(message);

		firmware_files.send_pending_message(intercore_comm);
		patch_storage.send_pending_message(intercore_comm);
	}

	void reload_default_patches() {
		patch_storage.reload_default_patches();
	}

private:
	FatFileIO &usb_fileio;
	FatFileIO &sd_fileio;

	mdrivlib::InterCoreComm<mdrivlib::ICCCoreType::Responder, IntercoreStorageMessage> intercore_comm;
	PatchStorage patch_storage{sd_fileio, usb_fileio};
	FirmwareFileFinder firmware_files{sd_fileio, usb_fileio};
};

} // namespace MetaModule
