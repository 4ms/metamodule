#pragma once
#include "volumes.hh"
#include <algorithm>
#include <string>
#include <string_view>
#include <vector>

namespace MetaModule
{

// given a string of comma-separated extensions, examples: ".wav, .WAV, .raw"
// creates a vector of extensions: {".wav", ".WAV", ".raw"}
std::vector<std::string> parse_extensions(std::string_view str, std::string const &delimiters = ",");

std::pair<std::string_view, Volume> split_volume(const char *filename);
std::pair<std::string_view, Volume> split_volume(std::string_view filename);

} // namespace MetaModule
