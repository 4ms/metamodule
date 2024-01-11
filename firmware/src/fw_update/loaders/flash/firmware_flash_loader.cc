#include "firmware_flash_loader.hh"

namespace MetaModule
{

FirmwareFlashLoader::FirmwareFlashLoader(std::span<char> filedata, std::size_t address) : BaseAddress(address), file(filedata)
{
}


FileWorkerBase::Error FirmwareFlashLoader::start() {

    flash = std::make_unique<FlashLoader>();

    if (!flash || !flash->check_flash_chip())
        return Error::Failed;

    bytes_completed = 0;
    cur_flash_addr = BaseAddress;

    cur_read_block = file.subspan(0, flash_sector_size);

    return Error::None;
}

std::pair<std::size_t, FirmwareFlashLoader::Error> FirmwareFlashLoader::process() {
    if (bytes_completed < file.size()) {

        if (!flash->write_sectors(cur_flash_addr, cur_read_block)) {
            return {bytes_completed, Error::Failed};
        }

        cur_flash_addr += flash_sector_size;
        bytes_completed += flash_sector_size;
        cur_read_block =
            cur_read_block.subspan(flash_sector_size, std::min<int>(flash_sector_size, file.size() - bytes_completed));
    }

    return {bytes_completed, Error::None};
}

}