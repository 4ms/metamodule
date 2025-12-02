#pragma once

#include "calibrate/calibration_message_handler.hh"
#include "core_intercom/intercore_message.hh"
#include "core_intercom/shared_memory.hh"
#include "drivers/inter_core_comm.hh"
#include "fs/fatfs/fat_file_io.hh"
#include "fs/fatfs/null_disk_ops.hh"
#include "patch_file/patch_storage.hh"

namespace MetaModule
{

struct FilesystemMessages {

	FilesystemMessages(IntercoreStorageMessage *shared_message)
		: intercore_comm{*shared_message} {
	}

	void process() {
		auto message = intercore_comm.get_new_message();

		if (message.message_type != IntercoreStorageMessage::MessageType::None) {
			auto process_receiver = [this, &message](auto &receiver) {
				if (auto response = receiver.handle_message(message); response) {
					// mark message as handled
					message.message_type = IntercoreStorageMessage::MessageType::None;

					// try to send response infinitely
					while (!intercore_comm.send_message(*response))
						;
				}
			};

			process_receiver(patch_storage);
			process_receiver(calibration_handler);

			if (message.message_type != IntercoreStorageMessage::MessageType::None) {
				pr_err("ICC message of type %u not handled\n", message.message_type);
			}
		}
	}

	PatchStorage &get_patch_storage() {
		return patch_storage;
	}

private:
	mdrivlib::InterCoreComm<mdrivlib::ICCRoleType::Responder, IntercoreStorageMessage> intercore_comm;

	FlashLoader flash_loader;

	static inline NullDiskOps null_ops{};
	FatFileIO null_sd{&null_ops, Volume::SDCard};
	FatFileIO null_usb{&null_ops, Volume::USB};

	PatchStorage patch_storage{null_sd, null_usb, SharedMemoryS::ptrs.ramdrive};
	CalibrationMessageHandler calibration_handler{flash_loader};
};

} // namespace MetaModule
