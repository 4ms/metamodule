#include "audio.hh"
#include "debug.hh"
#include "drivers/syscfg.hh"
#include "patch_player.hh"

constexpr bool DEBUG_PASSTHRU_AUDIO = false;

AudioStream::AudioStream(Params &p, ICodec &codec, AnalogOutT &dac, AudioStreamBlock (&buffers)[4])
	: codec_{codec}
	, sample_rate_{codec.get_samplerate()}
	, tx_buf_1{buffers[0]}
	, tx_buf_2{buffers[1]}
	, rx_buf_1{buffers[2]}
	, rx_buf_2{buffers[3]}
	, params{p}
	, dac{dac}
{
	load_patch();

	codec_.set_txrx_buffers(reinterpret_cast<uint8_t *>(tx_buf_1.data()),
							reinterpret_cast<uint8_t *>(rx_buf_1.data()),
							AudioConf::DMABlockSize * 2);
	codec_.set_callbacks([this]() { process(rx_buf_1, tx_buf_1); }, [this]() { process(rx_buf_2, tx_buf_2); });

	dac.init();
	dac_updater.init(DAC_update_conf, [&]() { dac.output_next(); });

	load_measure.init();
}

AudioConf::SampleT AudioStream::get_output(int output_id)
{
	auto raw_out = player.get_panel_output(output_id);
	auto scaled_out = AudioFrame::scaleOutput(raw_out);
	return scaled_out;
	// return compressor.compress(scaled_out);
}
void AudioStream::set_input(int input_id, AudioConf::SampleT in)
{
	auto scaled_in = AudioFrame::scaleInput(in);
	player.set_panel_input(input_id, scaled_in);
}

void AudioStream::process(AudioStreamBlock &in, AudioStreamBlock &out)
{
	check_patch_change();

	load_measure.start_measurement();
	Debug::Pin0::high();

	params.update();

	bool should_update_knob[NumKnobs];
	static auto is_small = [](float x) { return x < 9e-4f && x > -9e-4f; };
	int i = 0;
	for (auto &knob : knobs) {
		knob.set_new_value(params.knobs[i]);
		should_update_knob[i] = !is_small(knob.get_step_size());
		i++;
	}
	i = 0;
	for (auto &cv : cvjacks) {
		cv.set_new_value(params.cvjacks[i]);
		i++;
	}

	auto in_ = in.begin();
	for (auto &out_ : out) {
		int i;
		set_input(0, in_->l);
		set_input(1, in_->r);

		i = 0;
		for (auto &cv : cvjacks) {
			player.set_panel_input(i + NumAudioInputs, cv.next());
			i++;
		}
		i = 0;
		for (auto &knob : knobs) {
			if (should_update_knob[i])
				player.set_panel_param(i, knob.next());
			i++;
		}

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

		// Todo: use player.get_output(2) and (3)
		dac.queue_sample(0, out_.r + 0x00800000);
		dac.queue_sample(1, out_.l + 0x00800000);

		in_++;
	}

	Debug::Pin0::low();
	load_measure.end_measurement();
	params.audio_load = load_measure.get_last_measurement_load_percent();
}

void AudioStream::start()
{
	codec_.start();

	dac_updater.start();
}

bool AudioStream::check_patch_change()
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
		load_patch();
	}
	return new_patch;
}

void AudioStream::load_patch()
{
	bool ok = player.load_patch(params.cur_patch());

	for (int i = 0; i < NumCVInputs; i++)
		player.set_panel_input(i + NumAudioInputs, params.cvjacks[i]);

	for (int i = 0; i < NumAudioInputs + NumCVInputs; i++)
		player.set_panel_input(i, 0);

	for (int i = 0; i < NumKnobs; i++)
		player.set_panel_param(i, params.knobs[i]);

	if (!ok) {
		while (1) {
			; // Todo: Display error on screen: Cannot load patch
		}
	}
}
