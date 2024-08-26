#pragma once
#include "sampler_audio.hh"
#include "sampler_loader.hh"
#include "sampler_modes.hh"
#ifndef METAMODULE
#include "wav_recording.hh"
#endif

namespace SamplerKit
{

struct Sampler {
	uint32_t g_error = 0;

	Sampler(Params &params,
			Flags &flags,
			Sdcard &sd,
			BankManager &banks,
			std::array<CircularBuffer, NumSamplesPerBank> &play_buff)
		: audio{state, params, flags, banks.samples, play_buff}
		, loader{modes, state, params, flags, sd, banks, play_buff, g_error}
		, modes{params, flags, sd, banks, state, play_buff, g_error}
#ifndef METAMODULE
		, recorder{params, flags, sd, banks}
#endif
	{
	}

	SamplerAudio audio;
	SampleLoader loader;
	SamplerModes modes;
	SampleState state;
#ifndef METAMODULE
	Recorder recorder;
#endif

	void start() {
		// loader.start();
	}

	void update_fs_thread(uint32_t time) {
		modes.process_mode_flags(time);
		loader.update(time);
#ifndef METAMODULE
		recorder.write_buffer_to_storage();
#endif
	}
};

} // namespace SamplerKit
