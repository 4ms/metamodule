#include "audio_wrapper.hh"
#include "file_io.hh"
#include "patch-serial/yaml_to_patch.hh"
#include "settings.hh"
#include <span>
#include <time.h>

void write_file(std::span<MetaModule::StreamConfSim::Audio::AudioOutFrame> output) {
	//TODO
}

int main(int argc, char *argv[]) {
	using namespace MetaModule;

	MetaModuleSim::Settings settings;
	settings.parse(argc, argv);

	// Read patch
	auto yaml = Headless::FileIO::read_file(settings.patch_path);
	if (yaml.size() == 0) {
		printf("Error: Failed to read patch file %s\n", settings.patch_path.c_str());
		return 1;
	}
	PatchData patchdata;
	yaml_raw_to_patch(yaml, patchdata);

	printf("Patch loaded: %zu modules\n", patchdata.module_slugs.size());

	// Load patch
	MetaModule::PatchPlayer player;
	player.load_patch(patchdata);

	// TODO: read audio input file from settings
	std::vector<StreamConfSim::Audio::AudioInFrame> dummy_input_file(48000 * 10);
	auto samples_to_run = std::min(settings.samples_to_run, dummy_input_file.size());
	printf("Running for %lu samples\n", samples_to_run);

	// Play patch
	std::vector<StreamConfSim::Audio::AudioOutFrame> output(samples_to_run);
	const auto inblocks = std::span{dummy_input_file};
	const auto outblocks = std::span{output};
	constexpr size_t block_size = 32;

	MetaModule::AudioWrapper audio{player};

	using namespace std::literals;
	const auto start = std::chrono::high_resolution_clock::now();

	for (size_t i = 0; i < samples_to_run; i += block_size) {
		auto in_block = inblocks.subspan(i, block_size);
		auto out_block = outblocks.subspan(i, block_size);

		audio.process(in_block, out_block);
	}

	const auto end = std::chrono::high_resolution_clock::now();
	printf("Duration: %lld ms\n", (end - start) / 1ms);

	// TODO: write output to file specified in settings
	write_file(output);

	return 0;
}
