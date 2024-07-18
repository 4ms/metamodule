#include "debug.hh"
#include "delay.hh"
#include "drivers/cache.hh"
#include "fs/settings_parse.hh"
#include "fs/settings_serialize.hh"
#include "gui/pages/view_settings.hh"
#include "patch_file/file_storage_proxy.hh"

namespace MetaModule::Settings
{

bool write_settings(FileStorageProxy &proxy, ViewSettings const &settings) {
	alignas(64) std::array<char, 1024> buffer;

	auto sz = serialize(settings, buffer);

	auto yaml_clean = std::span<char>{buffer.data(), sz};

	mdrivlib::SystemCache::clean_dcache_by_range((void *)(yaml_clean.data()), yaml_clean.size());

	uint32_t timeout = get_time();
	while (proxy.request_write_file(yaml_clean, Volume::NorFlash, "settings.yml") ==
		   FileStorageProxy::WriteResult::Busy)
	{
		if (get_time() - timeout > 1000) {
			pr_err("Settings file write request not made in 1 second\n");
			return false;
		}
	}

	timeout = get_time();
	while (true) {
		auto msg = proxy.get_message();

		if (msg.message_type == FileStorageProxy::WriteFileOK) {
			pr_dbg("Settings file written\n");
			return true;

		} else if (msg.message_type == FileStorageProxy::WriteFileFail) {
			pr_err("Settings file write failed\n");
			return false;
		}

		if (get_time() - timeout > 1000) {
			pr_err("Settings file write request not responded to in 1 second\n");
			return false;
		}
	}
}

bool read_settings(FileStorageProxy &proxy, ViewSettings *settings) {
	alignas(64) std::array<char, 1024> buffer{};

	static_assert(buffer.size() % 64 == 0, "Buffer must not share cache lines with other data");

	mdrivlib::SystemCache::clean_dcache_by_range(buffer.data(), buffer.size());

	uint32_t timeout = get_time();
	while (!proxy.request_load_file("settings.yml", Volume::NorFlash, buffer)) {
		if (get_time() - timeout > 1000) {
			pr_err("Settings file read request not made in 1 second\n");
			return false;
		}
	}

	timeout = get_time();
	while (true) {
		auto msg = proxy.get_message();

		if (msg.message_type == FileStorageProxy::LoadFileOK) {
			pr_dbg("Settings file loaded, beginning parsing\n");

			auto yaml = std::span<char>{buffer.data(), msg.bytes_read};

			mdrivlib::SystemCache::invalidate_dcache_by_range(yaml.data(), yaml.size());

			return parse(yaml, settings);
		}

		else if (msg.message_type == FileStorageProxy::LoadFileFailed)
		{
			pr_info("Settings file not found\n");
			return false;
		}

		if (get_time() - timeout > 1000) {
			pr_err("Settings file read request not responded to in 1 second\n");
			return false;
		}
	}
}

} // namespace MetaModule::Settings
