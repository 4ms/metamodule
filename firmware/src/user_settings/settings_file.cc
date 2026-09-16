#include "settings_file.hh"
#include "fs/general_io.hh"
#include "patch_file/file_storage_proxy.hh"
#include "settings_parse.hh"
#include "settings_serialize.hh"

namespace MetaModule::Settings
{

constexpr unsigned NumReadAttempts = 3;

bool write_settings(FileStorageProxy &proxy, UserSettings const &settings, Volume vol) {
	std::array<char, 16384> buffer{};

	auto sz = Settings::serialize(settings, buffer);

	auto yaml_clean = std::span<char>{buffer.data(), sz};

	return FS::write_file(proxy, yaml_clean, {.filename = "settings.yml", .vol = vol});
}

bool read_settings(FileStorageProxy &proxy, UserSettings *settings, Volume vol) {
	std::string buffer;

	for (auto attempt = 0u; attempt < NumReadAttempts; attempt++) {

		if (auto bytes_read = FS::read_file(proxy, buffer, PatchLocation{"settings.yml", vol})) {
			pr_dbg("Settings file loaded: %u bytes, beginning parsing\n", (unsigned)*bytes_read);

			auto yaml = std::span<char>{buffer.data(), *bytes_read};
			return parse(yaml, settings);
		}

		pr_err("Error reading settings file (attempt %u of %u)\n", attempt + 1, NumReadAttempts);
	}

	return false;
}

} // namespace MetaModule::Settings
