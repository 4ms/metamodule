#pragma once
#include "core_intercom/intercore_message.hh"
#include "drivers/inter_core_comm.hh"
#include "fat_file_io.hh"


namespace MetaModule
{

struct FirmwareWriter {
	using InterCoreComm = mdrivlib::InterCoreComm<mdrivlib::ICCCoreType::Responder, IntercoreStorageMessage>;
	using enum IntercoreStorageMessage::MessageType;
	using Checksum_t = std::string_view;

public:
	FirmwareWriter(FatFileIO &sdcard_fileio, FatFileIO &usb_fileio);

	void handle_message(IntercoreStorageMessage &message);

	void send_pending_message(InterCoreComm &comm);

private:
	IntercoreStorageMessage compareChecksumWifi(uint32_t, uint32_t, Checksum_t);
	IntercoreStorageMessage flashWifi(FatFileIO* fileio, std::string_view filename, uint32_t address, const uint32_t length, uint32_t& bytesWritten);
	IntercoreStorageMessage compareChecksumQSPI(uint32_t, uint32_t, Checksum_t);
	IntercoreStorageMessage flashQSPI(FatFileIO* fileio, std::string_view filename, uint32_t address, const uint32_t length, uint32_t& bytesWritten);

private:
	FatFileIO &sdcard_;
	FatFileIO &usbdrive_;
	
	IntercoreStorageMessage pending_send_message{.message_type = None};

};

} // namespace MetaModule
