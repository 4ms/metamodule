#include "audio.hh"
#include "debug.hh"
// #include "example-lfosimple.hh"
// #include "example-ps2.hh"
#include "example1.hh"
#include "patch_player.hh"

Audio::Audio(Params &p, ICodec &codec, AudioStreamBlock (&buffers)[4])
	: codec_{codec}
	, sample_rate_{codec.get_samplerate()}
	, tx_buf_1{buffers[0]}
	, tx_buf_2{buffers[1]}
	, rx_buf_1{buffers[2]}
	, rx_buf_2{buffers[3]}
	, params{p}
{
	bool ok = player.load_patch(Example1);
	if (!ok) {
		while (1) {
			;
		}
	}

	codec_.set_txrx_buffers(reinterpret_cast<uint8_t *>(tx_buf_1.data()),
							reinterpret_cast<uint8_t *>(rx_buf_1.data()),
							kAudioStreamDMABlockSize * 2);
	codec_.set_callbacks([this]() { process(rx_buf_1, tx_buf_1); }, [this]() { process(rx_buf_2, tx_buf_2); });
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

// namespace
// {
static volatile uint32_t last_start_tm = 0;
// }
void Audio::process(AudioStreamBlock &in, AudioStreamBlock &out)
{
	if (check_patch_change())
		return;

	// Todo: use target::DWT
	uint32_t start_tm = DWT->CYCCNT;
	uint32_t period = start_tm - last_start_tm;
	last_start_tm = start_tm;

	Debug::Pin0::high();

	params.update();

	bool should_update_knob[4];
	static auto is_small = [](float x) { return x < 1e-8f && x > -1e-8f; };
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
		auto scaled_in = AudioFrame::scaleInput(in_->l);
		player.set_panel_input(0, scaled_in);

		scaled_in = AudioFrame::scaleInput(in_->r);
		player.set_panel_input(1, scaled_in);

		int i = 0;
		for (auto &knob : knobs) {
			if (should_update_knob[i])
				player.set_panel_param(i, knob.next());
			i++;
		}

		i = 0;
		for (auto &cv : cvjacks) {
			player.set_panel_input(i + 2, cv.next()); // i+2 : skip audio jacks
			i++;
		}
		// Debug::set_1(true);
		player.update_patch(params.cur_patch());
		// Debug::set_1(false);

		out_.l = get_output(0);
		out_.r = get_output(1);
		in_++;
	}

	Debug::Pin0::low();
	uint32_t elapsed_tm = DWT->CYCCNT - start_tm;
	params.audio_load = (elapsed_tm * 100) / period;
}

void Audio::start()
{
	codec_.start();
}

void Audio::check_patch_change()
{
	// Check if it changed
	// call patch.load_patch(new_patch);
	// set cur_patch = new_patch; (copy? pointer?)
}
