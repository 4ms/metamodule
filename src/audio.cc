#include "audio.hh"
#include "debug.hh"
#include <cmath>

Audio::Audio(Params &p, ICodec &codec)
	: params{p}
	, codec_{codec}
	, sample_rate_{codec.get_samplerate()}
{
	for (uint32_t i = 0; i < FXList::NumFX; i++) {
		FX_left[i]->set_samplerate(sample_rate_);
		FX_right[i]->set_samplerate(sample_rate_);
	}

	current_fx[LEFT] = FX_left[0];
	current_fx[RIGHT] = FX_right[0];

	codec_.set_txrx_buffers(reinterpret_cast<uint8_t *>(tx_buf_[0].data()),
							reinterpret_cast<uint8_t *>(rx_buf_[0].data()),
							kAudioStreamDMABlockSize * 2);

	codec_.set_callbacks([this]() { process(rx_buf_[0], tx_buf_[1]); }, [this]() { process(rx_buf_[1], tx_buf_[0]); });
}

// param smoothing: +3.9% of processing (23.4% -> 19.5%)
// SDRAM: +5.7% (SRAM1: 15.5% vs. SDRAM: 21.2% (SDRAM adds 5.7%)
// block size: 0.2% (@32: 21.2%, @128: 21.0%)
// Compression<float>: 18.4%, +comp float stereo = 20.4% (+2%)
// Compression<int32_t>: -> 19.6% (+1%)
// Hard Clip (constrain): 21.2% -> 21.2% (+2.3%)

Audio::AudioSampleType Audio::process_chan(AudioSampleType in, enum AudioChannels c)
{
	auto scaled_in = AudioFrame::scaleInput(in);
	auto raw_out = current_fx[c]->update(scaled_in);
	auto scaled_out = AudioFrame::scaleOutput(raw_out);
	return compressor.compress(scaled_out);
}

void Audio::process(AudioStreamBlock &in, AudioStreamBlock &out)
{
	Debug::set_0(true);

	params.update();
	check_fx_change();

	static auto is_small = [](float x) { return x < 1e-8f && x > -1e-8f; };
	freq0.set_new_value(params.freq[0]);
	freq1.set_new_value(params.freq[1]);
	res0.set_new_value(params.res[0]);
	res1.set_new_value(params.res[1]);

	bool update_freq0 = !is_small(freq0.get_step_size());
	bool update_freq1 = !is_small(freq1.get_step_size());
	bool update_res0 = !is_small(res0.get_step_size());
	bool update_res1 = !is_small(res1.get_step_size());

	auto in_ = in.begin();
	for (auto &out_ : out) {
		out_.l = process_chan(in_->l, LEFT);
		out_.r = process_chan(in_->r, RIGHT);

		if (update_freq0)
			current_fx[LEFT]->set_param(0, freq0.next());
		if (update_res0)
			current_fx[LEFT]->set_param(1, res0.next());
		if (update_freq1)
			current_fx[RIGHT]->set_param(0, freq1.next());
		if (update_res1)
			current_fx[RIGHT]->set_param(1, res1.next());

		in_++;
	}
	Debug::set_0(false);
}

void Audio::start()
{
	codec_.start();
}

void Audio::check_fx_change()
{
	if (current_fx[LEFT] != FX_left[params.fx_mode[0]]) {
		current_fx[LEFT] = FX_left[params.fx_mode[0]];
	}
	if (current_fx[RIGHT] != FX_right[params.fx_mode[1]]) {
		current_fx[RIGHT] = FX_right[params.fx_mode[1]];
	}
}
