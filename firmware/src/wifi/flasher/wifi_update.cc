#include "wifi_update.hh"
#include "flasher.h"

#include <pr_dbg.hh>

extern unsigned int _binary_firmware_bin_start;
extern unsigned int _binary_firmware_bin_end;
extern unsigned int _binary_littlefs_img_start;
extern unsigned int _binary_littlefs_img_end;

const uint32_t FirmwareStartAddress = 0x0;
std::span<const uint8_t> Firmware ((uint8_t*)&_binary_firmware_bin_start, std::size_t((uint8_t*)&_binary_firmware_bin_end - (uint8_t*)&_binary_firmware_bin_start));
const auto FirmwareChecksum = firmware_MD5;

const uint32_t FilesystemStartAddress = 0x200000;
std::span<const uint8_t> Filesystem ((uint8_t*)&_binary_littlefs_img_start, std::size_t((uint8_t*)&_binary_littlefs_img_end - (uint8_t*)&_binary_littlefs_img_start));
const auto FileystemChecksum = littlefs_MD5;


namespace MetaModule
{

void WifiUpdate::checkForUpdate()
{
    auto result = Flasher::init(230400);

    if (result == ESP_LOADER_SUCCESS)
    {
        pr_dbg("Update firmware partition\n");

        result = Flasher::conditional_flash(FirmwareStartAddress, Firmware, FirmwareChecksum);

        pr_dbg("Update filesystem partition\n");

        result = Flasher::conditional_flash(FilesystemStartAddress, Filesystem, FileystemChecksum);
    }
}

}