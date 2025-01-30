#include "helpers.hh"
#include "console/pr_dbg.hh"

namespace MetaModule
{

std::vector<std::string> parse_extensions(std::string_view str, std::string const &delimiters) {
	std::vector<std::string> tokens;

	// Matching *.* means no filtering: return an empty vector
	if (str.contains("*.*")) {
		pr_dbg("M4: filter contains *.*, ignoring filter\n");
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
		pr_dbg("M4: filter on '%s'\n", s.c_str());
		tokens.push_back(s);

		// Skip delimiters.
		last_pos = str.find_first_not_of(delimiters, pos);

		// Find next non-delimiter.
		pos = str.find_first_of(delimiters, last_pos);
	}

	return tokens;
}

std::pair<std::string_view, Volume> split_volume(const char *filename) {
	auto sv = std::string_view{filename};
	return split_volume(sv);
}

std::pair<std::string_view, Volume> split_volume(std::string_view filename) {
	if (filename.starts_with("ram:"))
		return {filename.substr(4), Volume::RamDisk};

	if (filename.starts_with("usb:") || filename.starts_with("USB:"))
		return {filename.substr(4), Volume::USB};

	if (filename.starts_with("sdc:"))
		return {filename.substr(4), Volume::SDCard};

	if (filename.starts_with("SD Card:"))
		return {filename.substr(8), Volume::SDCard};

	if (filename.starts_with("nor:"))
		return {filename.substr(4), Volume::NorFlash};

	// Default (no volume given) is RamDisk
	return {filename, Volume::RamDisk};
}

} // namespace MetaModule
