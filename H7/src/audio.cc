#include "audio.hh"
#include "debug.hh"
#include "patch_player.hh"

constexpr bool DEBUG_PASSTHRU_AUDIO = false;

Audio::Audio(Params &p, ICodec &codec, AudioStreamBlock (&buffers)[4])
	: codec_{codec}
	, sample_rate_{codec.get_samplerate()}
	, tx_buf_1{buffers[0]}
	, tx_buf_2{buffers[1]}
	, rx_buf_1{buffers[2]}
	, rx_buf_2{buffers[3]}
	, params{p}
{
	bool ok = player.load_patch(params.cur_patch());
	if (!ok) {
		while (1) {
			;
		}
	}

	codec_.set_txrx_buffers(reinterpret_cast<uint8_t *>(tx_buf_1.data()),
							reinterpret_cast<uint8_t *>(rx_buf_1.data()),
							kAudioStreamDMABlockSize * 2);
	codec_.set_callbacks([this]() { process(rx_buf_1, tx_buf_1); }, [this]() { process(rx_buf_2, tx_buf_2); });

	// Todo: LoadMeasurer class
	// DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

Audio::AudioSampleType Audio::get_output(int output_id)
{
	auto raw_out = player.get_panel_output(output_id);
	auto scaled_out = AudioFrame::scaleOutput(raw_out);
	return scaled_out;
	// return compressor.compress(scaled_out);
}
void Audio::set_input(int input_id, Audio::AudioSampleType in)
{
	auto scaled_in = AudioFrame::scaleInput(in);
	player.set_panel_input(input_id, scaled_in);
}

void Audio::process(AudioStreamBlock &in, AudioStreamBlock &out)
{
	if (check_patch_change()) {
		params.controls.clock_out.high();
	}

	// Todo: Make LoadMeasurer class, and use target::DWT
	uint32_t start_tm = DWT->CYCCNT /*SysTick->VAL*/;
	uint32_t period = start_tm - last_start_tm;
	last_start_tm = start_tm;
	/////

	Debug::Pin0::high();

	params.update();

	bool should_update_knob[4];
	static auto is_small = [](float x) { return x < 3e-4f && x > -3e-4f; };
	int i = 0;
	for (auto &knob : knobs) {
		knob.set_new_value(params.knobs[i]);
		should_update_knob[i] = !is_small(knob.get_step_size());
		// player.set_panel_param(i, params.knobs[i]);
		i++;
	}
	i = 0;
	for (auto &cv : cvjacks) {
		cv.set_new_value(params.cvjacks[i]);
		// player.set_panel_input(i + 2, params.cvjacks[i]);
		i++;
	}

	auto in_ = in.begin();
	for (auto &out_ : out) {
		int i;
		set_input(0, in_->l);
		set_input(1, in_->r);

		i = 0;
		for (auto &cv : cvjacks) {
			player.set_panel_input(i + 2, cv.next()); // i+2 : skip audio jacks
			i++;
		}

		i = 0;
		for (auto &knob : knobs) {
			if (should_update_knob[i])
				player.set_panel_param(i, knob.next());
			i++;
		}

		// SCB_InvalidateDCache();
		player.update_patch(params.cur_patch());

		// FixMe: Why are the L/R samples swapped in the DMA buffer? The L/R jacks are not swapped on hardware
		// Todo: scope the data stream vs. LR clk
		if constexpr (DEBUG_PASSTHRU_AUDIO) {
			out_.l = in_->r;
			out_.r = in_->l;
		} else {
			out_.l = get_output(1);
			out_.r = get_output(0);
		}

		in_++;
	}

	Debug::Pin0::low();
	params.controls.clock_out.low();

	// Todo: move to LoadMeasurer class
	uint32_t elapsed_tm = /*SysTick->VAL */ DWT->CYCCNT - start_tm;
	params.audio_load = ((elapsed_tm * 100) + 1) / (period + 1);
	////
}

void Audio::start()
{
	codec_.start();
}

bool Audio::check_patch_change()
{
	bool new_patch = false;
	if (params.rotary_motion > 0) {
		player.unload_patch(params.cur_patch());
		params.next_patch();
		new_patch = true;
	} else if (params.rotary_motion < 0) {
		player.unload_patch(params.cur_patch());
		params.prev_patch();
		new_patch = true;
	}

	if (new_patch) {
		params.rotary_motion = 0;
		params.should_redraw_patch = true;
		// __BKPT();
		bool ok = player.load_patch(params.cur_patch());
		if (!ok) {
			while (1)
				; // Todo: handle error?
		}
	}
	return new_patch;
}
