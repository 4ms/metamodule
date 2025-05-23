#pragma once
#include "core_intercom/intercore_message.hh"
#include "drivers/inter_core_comm.hh"
#include "fat_file_io.hh"
#include "flash_loader/flash_loader.hh"
#include <optional>

namespace MetaModule
{

struct FirmwareWriter {
	using enum IntercoreStorageMessage::MessageType;
	using Checksum_t = std::string_view;

public:
	FirmwareWriter(FatFileIO &sdcard_fileio, FatFileIO &usb_fileio, FlashLoader &flash_loader);

	std::optional<IntercoreStorageMessage> handle_message(const IntercoreStorageMessage &message);

private:
	IntercoreStorageMessage compareChecksumWifi(uint32_t, uint32_t, Checksum_t);
	IntercoreStorageMessage flashWifi(std::span<uint8_t>, uint32_t address, std::optional<uint32_t> uncompressed_size, uint32_t &bytesWritten);
	IntercoreStorageMessage compareChecksumQSPI(uint32_t, uint32_t, Checksum_t, uint32_t &bytesWritten);
	IntercoreStorageMessage flashQSPI(std::span<uint8_t>, uint32_t address, uint32_t &bytesWritten);

	FatFileIO &sdcard_;
	FatFileIO &usbdrive_;

	FlashLoader &loader_;
};

} // namespace MetaModule
