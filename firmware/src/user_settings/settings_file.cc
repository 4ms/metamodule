#include "settings_file.hh"
#include "delay.hh"
#include "fs/general_io.hh"
#include "memory/ram_buffer.hh"
#include "patch_file/file_storage_proxy.hh"
#include "settings_parse.hh"
#include "settings_serialize.hh"

namespace MetaModule::Settings
{

bool write_settings(FileStorageProxy &proxy, UserSettings const &settings, Volume vol) {
	std::array<char, 16384> buffer{};

	auto sz = Settings::serialize(settings, buffer);

	auto yaml_clean = std::span<char>{buffer.data(), sz};

	return FS::write_file(proxy, yaml_clean, {.filename = "settings.yml", .vol = vol});
}

bool read_settings(FileStorageProxy &proxy, UserSettings *settings, Volume vol) {

	auto rawmem = get_ram_buffer();
	auto buffer = std::span{(char *)rawmem.data(), 2048};

	uint32_t timeout = get_time();
	while (!proxy.request_load_file("settings.yml", vol, buffer)) {
		if (get_time() - timeout > 1000) {
			pr_err("Settings file read request not made in 1 second\n");
			return false;
		}
	}

	timeout = get_time();
	while (true) {
		auto msg = proxy.get_message();

		if (msg.message_type == FileStorageProxy::LoadFileOK) {
			pr_dbg(
				"Settings file loaded in %ums, %zu bytes, beginning parsing\n", get_time() - timeout, msg.bytes_read);

			auto yaml = std::span<char>{buffer.data(), msg.bytes_read};

			return parse(yaml, settings);
		}

		else if (msg.message_type == FileStorageProxy::LoadFileFailed)
		{
			pr_info("Settings file not found\n");
			return false;
		}

		if (get_time() - timeout > 3000) {
			pr_err("Settings file read request not responded to in 3 seconds\n");
			return false;
		}
	}
}

} // namespace MetaModule::Settings
