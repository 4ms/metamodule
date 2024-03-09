#pragma once
#include "conf/qspi_flash_conf.hh"
#include "fs/littlefs/norflash_lfs.hh"
#include "fs/littlefs/norflash_ops.hh"

namespace MetaModule
{

struct AssetFS {
	mdrivlib::QSpiFlash flash{qspi_patchflash_conf};
	LfsFileIO<AssetVolFlashOffset> lfs_io{flash};

	AssetFS() {
		lfs_io.initialize();
		std::array<char, 1024> buffer;
		auto br = lfs_io.read_file("README.txt", buffer, 0);
		pr_dbg("README = %zu bytes\n", br);
		pr_dbg("%s\n", buffer);
	}
};

} // namespace MetaModule
