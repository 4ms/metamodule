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
        printf("Bootloader ready\n");

        printf("Firmware image at   %p-%p\n", &_binary_firmware_bin_start, &_binary_firmware_bin_end);
        printf("Filesystem image at %p-%p\n", &_binary_littlefs_img_start, &_binary_littlefs_img_end);

        result = Flasher::verify(FirmwareStartAddress, Firmware.size(), FirmwareChecksum);

        if (result == ESP_LOADER_SUCCESS)
        {
            printf("Firmware binary already matches\n");
            return;
        }
        else if (result == ESP_LOADER_ERROR_INVALID_MD5)
        {
            result = Flasher::flash(FirmwareStartAddress, Firmware);

            if (result == ESP_LOADER_SUCCESS)
            {
                printf("Firmware flashed\n");
            }
            else
            {
                printf("Flashing failed with %u\n", result);
            }
        }
        else
        {
            printf("Cannot get md5\n");
        }
    }
}



}