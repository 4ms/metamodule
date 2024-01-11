#include "firmware_wifi_loader.hh"
#include <pr_dbg.hh>

namespace MetaModule
{

FirmwareWifiLoader::FirmwareWifiLoader(std::span<char> filedata, std::size_t address) : file(filedata), bytes_completed(0)
{
}


FileWorkerBase::Error FirmwareWifiLoader::start() {
    return Error::None;
}

std::pair<std::size_t, FirmwareWifiLoader::Error> FirmwareWifiLoader::process() {
    //simulate activity
    if (bytes_completed < file.size()) {
        pr_dbg("Wifi bytes written: %u\n", bytes_completed);
        bytes_completed += 4096;
    }
    return {bytes_completed, Error::None};
}

}