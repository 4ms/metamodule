#include "audio_stream.hh"
#include "bank.hh"
#include "calibration_storage.hh"
#include "conf/board_conf.hh"
#include "controls.hh"
#include "debug.hh"
#include "drivers/timekeeper.hh"
#include "flags.hh"
#include "hardware_tests/hardware_tests.hh"
#include "params.hh"
#include "sampler.hh"
#include "sdcard.hh"
#include "system.hh"
#include "test_audio.hh"
#include "user_settings_storage.hh"
#include "wav_recording.hh"

namespace
{
// Initialize the system before main()
SamplerKit::System _init;
} // namespace

void main() {
	using namespace SamplerKit;
	using namespace mdrivlib;
	using AudioInBlock = AudioStreamConf::AudioInBlock;
	using AudioOutBlock = AudioStreamConf::AudioOutBlock;

	Controls controls;
	CalibrationStorage cal_storage;
	if (Board::PlayButton::PinT::read() && Board::RevButton::PinT::read()) {
		HWTests::run(controls, cal_storage);
	}

	Sdcard sd;
	sd.reload_disk();

	Flags flags;
	UserSettingsStorage settings_storage{sd, flags};

	SampleList samples;
	BankManager banks{samples};
	Params params{controls, flags, settings_storage.settings, banks, cal_storage};

	// Load sample index file (map files to sample slots and banks)
	SampleIndexLoader index_loader{sd, samples, banks, flags};
	{
		Timekeeper startup_animation{{.TIMx = TIM6, .period_ns = 1'000'000'000 / 6000, .priority1 = 2, .priority2 = 3},
									 [&params] { params.startup_animation(); }};
		startup_animation.start();
		index_loader.load_all_banks();
		startup_animation.stop();
	}

	Sampler sampler{params, flags, sd, banks};
	AudioStream audio_stream([&sampler, &params](const AudioInBlock &in, AudioOutBlock &out) {
		// Debug::Pin0::high();
		params.update();
		sampler.recorder.record_audio_to_buffer(in);
		sampler.audio.update(in, out);
		// Debug::Pin0::low();
	});

	sampler.start();
	audio_stream.start();

	while (true) {
		sampler.update();
		settings_storage.handle_events();
		index_loader.handle_events();

		__NOP();
	}
}
