#include "audio_files.hh"
#include "wav_file.hh"

namespace MetaModule::Headless
{

std::vector<AudioConf::AudioInFrame> read_wav(std::string_view filename, size_t expected_samples) {
	std::vector<AudioConf::AudioInFrame> input(expected_samples);

	WavReader wav{filename};

	if (!wav.is_valid()) {
		printf("Input file not valid, using silence\n");

	} else if (wav.num_channels() != AudioConf::NumInChans) {
		printf("Input file has wrong number of channels, using silence\n");

	} else if (wav.size() != expected_samples) {
		printf("Input file has %u samples, expected %zu, using silence\n", wav.size(), expected_samples);

	} else if (!wav.read<AudioConf::AudioInFrame>(input)) {
		printf("Cannot read expected amount of data from input file, input signal may be corrupted\n");

	} else {
		printf("Read input file, %u samples x %u channels\n", wav.size(), wav.num_channels());
	}

	return input;
}

void write_wav(std::span<const AudioConf::AudioOutFrame> output, std::string_view filename) {
	WavWriter wav{filename, output.size(), AudioConf::NumOutChans, 48000};
	wav.write(output);
}

} // namespace MetaModule::Headless
