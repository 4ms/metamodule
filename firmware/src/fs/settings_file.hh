#pragma once
#include "gui/pages/view_settings.hh"
#include "patch_file/file_storage_proxy.hh"
#include "ryml.hpp"
#include "ryml_std.hpp"

namespace MetaModule::Settings
{

void read_settings(FileStorageProxy &proxy, ViewSettings &settings) {
	alignas(64) std::array<char, 4096> buffer;

	while (!proxy.request_load_file("settings.yml", Volume::NorFlash, buffer)) {
		; //wait for M4 to start taking requests
	}

	bool response = false;
	while (!response) {
		auto msg = proxy.get_message();
		if (msg.message_type == FileStorageProxy::LoadFileToRamSuccess) {
			pr_dbg("Settings file loaded, parsing\n");

			ryml::Tree tree = ryml::parse_in_place(ryml::substr(buffer.data(), msg.bytes_read));
			response = true;
		}
		if (msg.message_type == FileStorageProxy::LoadFileToRamFailed) {
			pr_info("Settings file not found, using defaults\n");
			settings = ViewSettings{};
			response = true;
		}
	}
}

} // namespace MetaModule::Settings
