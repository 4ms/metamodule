#include "wifi_update.hh"
#include "flasher.h"

#include <pr_dbg.hh>

extern unsigned int _binary_bootloader_bin_start;
extern unsigned int _binary_bootloader_bin_end;
extern unsigned int _binary_application_bin_start;
extern unsigned int _binary_application_bin_end;
extern unsigned int _binary_filesystem_img_start;
extern unsigned int _binary_filesystem_img_end;

const uint32_t BootloaderStartAddress = 0x0;
std::span<const uint8_t> Bootloader ((uint8_t*)&_binary_bootloader_bin_start, std::size_t((uint8_t*)&_binary_bootloader_bin_end - (uint8_t*)&_binary_bootloader_bin_start));
const auto BootloaderChecksum = bootloader_MD5;

const uint32_t ApplicationStartAddress = 0x10000;
std::span<const uint8_t> Application ((uint8_t*)&_binary_application_bin_start, std::size_t((uint8_t*)&_binary_application_bin_end - (uint8_t*)&_binary_application_bin_start));
const auto ApplicationChecksum = application_MD5;

const uint32_t FilesystemStartAddress = 0x200000;
std::span<const uint8_t> Filesystem ((uint8_t*)&_binary_filesystem_img_start, std::size_t((uint8_t*)&_binary_filesystem_img_end - (uint8_t*)&_binary_filesystem_img_start));
const auto FileystemChecksum = filesystem_MD5;


namespace MetaModule
{

void WifiUpdate::run()
{
    auto result = Flasher::init(230400);

    if (result == ESP_LOADER_SUCCESS)
    {
        #ifdef ENABLE_WIFI_BRIDGE_UPDATE
        checkForUpdate();
        #else
        pr_dbg("Updating wifi module disabled\n");
        Flasher::reboot();
        #endif
    }

    Flasher::deinit();
}

void WifiUpdate::checkForUpdate()
{
    pr_dbg("Update bootloader partition\n");

    auto result = Flasher::conditional_flash(BootloaderStartAddress, Bootloader, BootloaderChecksum);

    if (result == ESP_LOADER_SUCCESS)
    {
        pr_dbg("Update application partition\n");

        auto result = Flasher::conditional_flash(ApplicationStartAddress, Application, ApplicationChecksum);

        if (result == ESP_LOADER_SUCCESS)
        {
            pr_dbg("Update filesystem partition\n");

            result = Flasher::conditional_flash(FilesystemStartAddress, Filesystem, FileystemChecksum);

            if (result == ESP_LOADER_SUCCESS)
            {
                pr_dbg("Reboot wifi bridge\n");
                Flasher::reboot();
                return;
            }
        }
    }

    // pr_err("Keeping wifi bridge in reset since integrity cannot be verifed\n");
    Flasher::reboot();
}

}