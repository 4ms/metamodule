#include "stream_conf.hh"
#include <string_view>
#include <vector>

namespace MetaModule::Headless
{

std::vector<AudioConf::AudioInFrame> read_wav(std::string_view filename, size_t expected_samples);
void write_wav(std::span<const AudioConf::AudioOutFrame> output, std::string_view filename);

} // namespace MetaModule::Headless
