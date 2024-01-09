#include "firmware_wifi_loader.hh"
#include <pr_dbg.hh>

namespace MetaModule
{

FirmwareWifiLoader::FirmwareWifiLoader(std::span<char> filedata)
{
    file = filedata;
}

bool FirmwareWifiLoader::verify(StaticString<32> md5) {
    pr_dbg("Wifi image at %p + %zu\n", file.data(), file.size());		
    return true;
}

bool FirmwareWifiLoader::start() {
    bytes_completed = 0;
    return true;
}

std::pair<std::size_t, FirmwareWifiLoader::Error> FirmwareWifiLoader::load_next_block() {
    //simulate activity
    if (bytes_completed < file.size()) {
        pr_dbg("Wifi bytes written: %u\n", bytes_completed);
        bytes_completed += 4096;
    }
    return {bytes_completed, Error::None};
}

}