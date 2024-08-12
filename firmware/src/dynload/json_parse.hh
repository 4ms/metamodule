#pragma once
#include <span>
#include <string>

namespace MetaModule::Plugin
{

struct Manifest {
	std::string slug;
	std::string name;
};

// TODO: use ryml to actually parse the json
// This implementation would fail if there are escaped quotes,
// or if there was a value that was exactly "slug" or "name"
// that preceded the first key "slug" or "name"
// and probably fail in other ways too
inline Manifest parse_json(std::span<char> file_data) {
	Manifest manifest{};

	//"slug"*"[^"*]"

	auto data = std::string_view{file_data.data(), file_data.size()};

	auto value_of_first_matching_key = [&data](std::string_view key) {
		if (auto key_start = data.find(key); key_start != std::string_view::npos) {

			auto key_end = key_start + key.length();

			if (auto val_start = data.find("\"", key_end); val_start != std::string_view::npos) {
				val_start++; //skip the "

				if (auto val_end = data.find("\"", val_start); val_end != std::string_view::npos) {
					return std::string{data.substr(val_start, val_end - val_start)};
				}
			}
		}
		return std::string{};
	};

	manifest.slug = value_of_first_matching_key("\"slug\"");
	manifest.name = value_of_first_matching_key("\"name\"");

	return manifest;
}

} // namespace MetaModule::Plugin
