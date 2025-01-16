#include "audio_files.hh"
#include "audio_wrapper.hh"
#include "file_io.hh"
#include "patch-serial/yaml_to_patch.hh"
#include "settings.hh"
#include <chrono>
#include <span>

namespace MetaModule::Headless
{

PatchData read_patch(std::string_view filename) {
	auto yaml = Headless::FileIO::read_file(filename);
	PatchData patchdata;

	if (yaml.size() > 0) {
		yaml_raw_to_patch(yaml, patchdata);
		printf("Patch loaded: %zu modules\n", patchdata.module_slugs.size());
	} else {
		printf("Error: Failed to read patch file %s\n", filename.data());
	}

	return patchdata;
}

auto measure_time_ms(auto &&process) {
	const auto start = std::chrono::high_resolution_clock::now();

	process();

	using namespace std::literals;
	const auto end = std::chrono::high_resolution_clock::now();
	auto duration = (end - start) / 1ms;
	printf("Process time: %lld ms\n", duration);

	return duration;
}

} // namespace MetaModule::Headless

int main(int argc, char *argv[]) {
	using namespace MetaModule;
	using namespace MetaModule::Headless;

	MetaModuleSim::Settings settings;
	settings.parse(argc, argv);

	const auto samples_to_run = settings.samples_to_run;
	const float effective_play_time = samples_to_run / 48000.f;
	printf("Run for %lu samples (%g sec @ 48kHz)\n", samples_to_run, effective_play_time);

	auto patchdata = read_patch(settings.patch);

	auto input = read_wav(settings.audio_in_file, samples_to_run);

	// Load patch file
	MetaModule::PatchPlayer player;
	player.load_patch(patchdata);

	// Play patch
	AudioWrapper audio{player};
	std::vector<AudioConf::AudioOutFrame> output(samples_to_run);

	auto duration = measure_time_ms([&] {
		const auto inblocks = std::span{input};
		const auto outblocks = std::span{output};
		constexpr size_t block_size = 32;

		for (size_t i = 0; i < samples_to_run; i += block_size) {
			auto in_block = inblocks.subspan(i, block_size);
			auto out_block = outblocks.subspan(i, block_size);

			audio.process(in_block, out_block);
		}
	});
	printf("Effective load (single core): %g percent\n", (float)duration / (effective_play_time * 10));

	// Write output to wav file
	write_wav(output, settings.audio_out_file);

	return 0;
}
