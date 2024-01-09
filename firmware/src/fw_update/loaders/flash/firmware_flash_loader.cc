#include "firmware_flash_loader.hh"
#include "uimg_header.hh"
#include "ld.h"

namespace MetaModule
{

FirmwareFlashLoader::FirmwareFlashLoader(std::span<char> filedata)
{
    file = filedata;
}

bool FirmwareFlashLoader::verify( StaticString<32> md5_chars) {

    if (file.size() > VIRTDRIVE_SZ) {
        pr_err("image is too large %zu > %zu\n", file.size(), VIRTDRIVE_SZ);
        return false;
    }
    if (file.size() < sizeof(BootImageDef::ImageHeader)) {
        pr_err("image too small to be uimg\n");
        return false;
    }

    //TODO: check md5
    uint32_t md5[4];
    for (auto i = 0u; i < 4; i++) {
        auto s = std::string{std::string_view{md5_chars}.substr(8 * i, 8)};
        md5[i] = std::strtoul(s.c_str(), nullptr, 16);
    }
    pr_trace("MD5 is %s (%08x %08x %08x %08x)\n", md5_chars.c_str(), md5[0], md5[1], md5[2], md5[3]);

    auto *uimg_header = reinterpret_cast<BootImageDef::ImageHeader *>(file.data());
    // BootImageDef::debug_print_raw_header(*uimg_header);

    if (uimg_header->ih_magic != BootImageDef::IH_MAGIC_BE) {
        pr_err("image magic is wrong %zu != %zu\n", uimg_header->ih_magic, BootImageDef::IH_MAGIC_BE);
        return false;
    }

    if ((BootImageDef::be_to_le(uimg_header->ih_size)) > (file.size() + 64)) {
        pr_err("Header says image size is %zu, which is larger than the file size (%zu)\n",
                BootImageDef::be_to_le(uimg_header->ih_size),
                file.size());
        return false;
    }

    return true;
}

bool FirmwareFlashLoader::start() {

    flash = std::make_unique<FlashLoader>();

    if (!flash || !flash->check_flash_chip())
        return false;

    bytes_remaining = file.size();

    cur_read_block = file.subspan(0, flash_sector_size);

    return true;
}

std::pair<int, FirmwareFlashLoader::Error> FirmwareFlashLoader::load_next_block() {
    if (bytes_remaining > 0) {

        if (!flash->write_sectors(cur_flash_addr, cur_read_block)) {
            return {bytes_remaining, Error::Failed};
        }

        cur_flash_addr += flash_sector_size;
        bytes_remaining -= flash_sector_size;
        cur_read_block =
            cur_read_block.subspan(flash_sector_size, std::min<int>(flash_sector_size, bytes_remaining));
    }

    return {bytes_remaining, Error::None};
}

}