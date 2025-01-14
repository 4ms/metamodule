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

std::atomic<bool> run{true};

int main(int argc, char *argv[]) {
	using namespace MetaModule;
	using namespace MetaModule::Headless;

	MetaModuleSim::Settings settings;
	settings.parse(argc, argv);

	auto patchdata = read_patch(settings.patch);

	// Load patch file
	MetaModule::PatchPlayer player;
	player.load_patch(patchdata);

	// Play patch
	AudioWrapper audio{player};

	if (!audio.start()) {
		printf("Failed to start audio driver\n");
	}

	while (run) {
	}

	audio.stop();

	return 0;
}
