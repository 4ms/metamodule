#include "wifi/comm/wifi_interface.hh"

namespace MetaModule
{

void board_m4_fs_init(PatchStorage *patch_storage) {
	WifiInterface::init(patch_storage);
	WifiInterface::start();
}

} // namespace MetaModule
