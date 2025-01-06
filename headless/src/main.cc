#include "frame.hh"
#include "settings.hh"
#include <span>

void write_file(std::span<Frame> output) {
	//TODO
}

int main(int argc, char *argv[]) {
	MetaModuleSim::Settings settings;

	settings.parse(argc, argv);

	// lv_init();
	// lv_port_disp_init(320, 240, settings.zoom);

	// SDLAudio<Frame> audio_out{settings.audioout_dev};

	// auto sdcard_path = std::filesystem::absolute(settings.sdcard_path);

	// auto flash_path = std::filesystem::absolute(settings.flash_path);

	// auto asset_tar_path = std::filesystem::absolute(settings.asset_file);

	// MetaModule::Ui ui{sdcard_path.string(), flash_path.string(), asset_tar_path.string(), audio_out.get_block_size()};

	// audio_out.set_callback([&ui](auto playback_buffer) { ui.play_patch(playback_buffer); });
	// audio_out.unpause();

	// // Run until get Quit event
	// while (ui.update()) {
	// }

	// audio_out.pause();

	// lv_port_disp_deinit();
	// lv_deinit();

	// audio_out.set_callback([&ui](auto playback_buffer) { ui.play_patch(playback_buffer); });

	std::vector<Frame> dummy_input_file(48000 * 10);
	auto samples_to_run = std::min(settings.samples_to_run, dummy_input_file.size());

	std::vector<Frame> output(samples_to_run);

	constexpr size_t block_size = 32;
	const auto inblocks = std::span<const Frame>{dummy_input_file};
	const auto outblocks = std::span<Frame>{output};

	for (size_t i = 0; i < samples_to_run; i += block_size) {
		auto in_block = inblocks.subspan(i, block_size);
		auto out_block = outblocks.subspan(i, block_size);

		audio.process(in_block, out_block);
	}

	// write output
	write_file(output);

	return 0;
}
