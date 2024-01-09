#include "firmware_wifi_loader.hh"
#include <pr_dbg.hh>

namespace MetaModule
{

bool FirmwareWifiLoader::verify(std::span<char> filedata, StaticString<32> md5, UpdateType image_type) {
		pr_dbg("Wifi image at %p + %zu\n", file.data(), file.size());		
		file = filedata;
		return true;
	}

	bool FirmwareWifiLoader::start() {
		bytes_remaining = file.size();
		return true;
	}

	std::pair<int, FirmwareWifiLoader::Error> FirmwareWifiLoader::load_next_block() {
		//simulate activity
		if (bytes_remaining > 0) {
			pr_dbg("Wifi bytes remaining: %d\n", bytes_remaining);
			bytes_remaining -= 4096;
		}
		return {bytes_remaining, Error::None};
	}

}