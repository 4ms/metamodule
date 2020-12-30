#include "audio.hh"
#include "debug.hh"
#include "example_patch.hh"
#include "patch_player.hh"
#include <cmath>

Audio::Audio(Params &p, ICodec &codec, AudioStreamBlock (&buffers)[4])
	: params{p}
	, codec_{codec}
	, sample_rate_{codec.get_samplerate()}
	, tx_buf_1{buffers[0]}
	, tx_buf_2{buffers[1]}
	, rx_buf_1{buffers[2]}
	, rx_buf_2{buffers[3]}
{
	player.load_patch(example_patch);

	codec_.set_txrx_buffers(reinterpret_cast<uint8_t *>(tx_buf_1.data()),
							reinterpret_cast<uint8_t *>(rx_buf_1.data()),
							kAudioStreamDMABlockSize * 2);

	codec_.set_callbacks([this]() { process(rx_buf_1, tx_buf_2); }, [this]() { process(rx_buf_2, tx_buf_1); });
}

Audio::AudioSampleType Audio::get_output(int output_id)
{
	auto raw_out = player.get_panel_output(output_id);
	auto scaled_out = AudioFrame::scaleOutput(raw_out);
	return compressor.compress(scaled_out);
}

void Audio::process(AudioStreamBlock &in, AudioStreamBlock &out)
{
	Debug::set_2(true);

	params.update();

	freq0.set_new_value(params.freq[0]);
	freq1.set_new_value(params.freq[1]);
	res0.set_new_value(params.res[0]);
	res1.set_new_value(params.res[1]);

	static auto is_small = [](float x) { return x < 1e-8f && x > -1e-8f; };
	bool update_freq0 = !is_small(freq0.get_step_size());
	bool update_freq1 = !is_small(freq1.get_step_size());
	bool update_res0 = !is_small(res0.get_step_size());
	bool update_res1 = !is_small(res1.get_step_size());

	auto in_ = in.begin();
	for (auto &out_ : out) {
		auto scaled_in = AudioFrame::scaleInput(in_->l);
		player.set_panel_input(0, scaled_in);

		scaled_in = AudioFrame::scaleInput(in_->r);
		player.set_panel_input(1, scaled_in);

		if (update_freq0)
			player.set_panel_param(0, freq0.next());
		if (update_res0)
			player.set_panel_param(1, res0.next());
		if (update_freq1)
			player.set_panel_param(2, freq1.next());
		if (update_res1)
			player.set_panel_param(3, res1.next());

		player.update_patch(example_patch);
		out_.l = get_output(0);
		out_.r = get_output(1);

		in_++;
	}

	Debug::set_2(false);
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
