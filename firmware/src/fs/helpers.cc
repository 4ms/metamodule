#include "helpers.hh"
#include "console/pr_dbg.hh"

namespace MetaModule
{

std::vector<std::string> parse_extensions(std::string_view str, std::string const &delimiters) {
	std::vector<std::string> tokens;

	// Matching *.* means no filtering: return an empty vector
	if (str.contains("*.*")) {
		pr_trace("M4: filter contains *.*, ignoring filter\n");
		return tokens;
	}

	auto last_pos = str.find_first_not_of(delimiters, 0);

	auto pos = str.find_first_of(delimiters, last_pos);

	while (pos != std::string::npos || last_pos != std::string::npos) {
		// Found a token, add it to the vector.
		// Skip leading spaces
		if (str[last_pos] == ' ')
			last_pos++;
		auto s = std::string(str.substr(last_pos, pos - last_pos));
		pr_trace("M4: filter on '%s'\n", s.c_str());
		tokens.push_back(s);

		// Skip delimiters.
		last_pos = str.find_first_not_of(delimiters, pos);

		// Find next non-delimiter.
		pos = str.find_first_of(delimiters, last_pos);
	}

	return tokens;
}

constexpr auto volume_labels = std::array{
	std::pair<std::string_view, Volume>{{"ram:"}, {Volume::RamDisk}},
	std::pair<std::string_view, Volume>{{"usb:"}, {Volume::USB}},
	std::pair<std::string_view, Volume>{{"sdc:"}, {Volume::SDCard}},
	std::pair<std::string_view, Volume>{{"nor:"}, {Volume::NorFlash}},
	// Alternative labels:
	std::pair<std::string_view, Volume>{{"USB:"}, {Volume::USB}},
	std::pair<std::string_view, Volume>{{"SD Card:"}, {Volume::SDCard}},
	std::pair<std::string_view, Volume>{{"Internal:"}, {Volume::NorFlash}},
};

constexpr std::string_view vol_label(Volume vol) {
	for (auto &label : volume_labels) {
		if (vol == label.second) {
			return label.first;
		}
	}
	return "";
}

std::pair<std::string_view, Volume> split_volume(const char *filename) {
	auto sv = std::string_view{filename};
	return split_volume(sv);
}

std::pair<std::string_view, Volume> split_volume(std::string_view filename) {

	Volume vol = Volume::RamDisk;
	std::string_view path = filename;

	auto strip_slash = [](auto f) {
		return f[0] == '/' ? f.substr(1) : f;
	};

	for (auto &label : volume_labels) {
		if (filename.starts_with(label.first)) {
			path = filename.substr(label.first.length());
			path = strip_slash(path);
			vol = label.second;
		}
	}

	return {path, vol};
}

} // namespace MetaModule
