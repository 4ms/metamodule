#include "audio_wrapper.hh"
#include "frame.hh"
#include "settings.hh"
#include <span>

void write_file(std::span<MetaModule::StreamConfSim::Audio::AudioOutFrame> output) {
	//TODO
}

int main(int argc, char *argv[]) {
	using namespace MetaModule;

	MetaModuleSim::Settings settings;

	settings.parse(argc, argv);

	std::vector<StreamConfSim::Audio::AudioInFrame> dummy_input_file(48000 * 10);
	auto samples_to_run = std::min(settings.samples_to_run, dummy_input_file.size());

	std::vector<StreamConfSim::Audio::AudioOutFrame> output(samples_to_run);

	constexpr size_t block_size = 32;
	const auto inblocks = std::span{dummy_input_file};
	const auto outblocks = std::span{output};

	MetaModule::PatchPlayer player;
	MetaModule::AudioWrapper audio{player};

	for (size_t i = 0; i < samples_to_run; i += block_size) {
		auto in_block = inblocks.subspan(i, block_size);
		auto out_block = outblocks.subspan(i, block_size);

		audio.process(in_block, out_block);
	}

	// write output
	write_file(output);

	return 0;
}
