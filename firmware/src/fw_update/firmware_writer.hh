#pragma once
#include "core_intercom/intercore_message.hh"
#include "drivers/inter_core_comm.hh"
#include "fat_file_io.hh"


namespace MetaModule
{

struct FirmwareWriter {
	using InterCoreComm = mdrivlib::InterCoreComm<mdrivlib::ICCCoreType::Responder, IntercoreStorageMessage>;
	using enum IntercoreStorageMessage::MessageType;

	FirmwareWriter(FatFileIO &sdcard_fileio, FatFileIO &usb_fileio);

	void handle_message(IntercoreStorageMessage &message);

	void send_pending_message(InterCoreComm &comm);

private:
	FatFileIO &sdcard_;
	FatFileIO &usbdrive_;
	
	IntercoreStorageMessage pending_send_message{.message_type = None};

};

} // namespace MetaModule
