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
}

// param smoothing: +3.9% of processing (23.4% -> 19.5%)
// SDRAM: +5.7% (SRAM1: 15.5% vs. SDRAM: 21.2% (SDRAM adds 5.7%)
// block size: 0.2% (@32: 21.2%, @128: 21.0%)
// Compression<float>: 18.4%, +comp float stereo = 20.4% (+2%)
// Compression<int32_t>: -> 19.6% (+1%)
// Hard Clip (constrain): 21.2% -> 21.2% (+2.3%)
void Audio::process(AudioStreamBlock &in, AudioStreamBlock &out)
{
	Debug::set_0(true);

	params.update();
	check_fx_change();

	freq0.set_new_value(params.freq[0]);
	freq1.set_new_value(params.freq[1]);
	res0.set_new_value(params.res[0]);
	res1.set_new_value(params.res[1]);

	auto in_ = in.begin();
	for (auto &out_ : out) {
		{
			auto scaled_in = AudioFrame::scaleInput(in_->l);
			auto raw_out = current_fx[LEFT]->update(scaled_in);
			auto scaled_out = AudioFrame::scaleOutput(raw_out);
			out_.l = compressor.compress(scaled_out);
		}
		{
			auto scaled_in = AudioFrame::scaleInput(in_->r);
			auto raw_out = current_fx[RIGHT]->update(scaled_in);
			auto scaled_out = AudioFrame::scaleOutput(raw_out);
			out_.r = compressor.compress(scaled_out);
		}

		current_fx[LEFT]->set_param(0, freq0.next());
		current_fx[LEFT]->set_param(1, res0.next());
		current_fx[RIGHT]->set_param(0, freq1.next());
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
	if (current_fx[LEFT] != FX_left[params.mode[0]]) {
		// Todo: start crossfading
		current_fx[LEFT] = FX_left[params.mode[0]];
	}
	if (current_fx[RIGHT] != FX_right[params.mode[1]]) {
		// Todo: start crossfading
		current_fx[RIGHT] = FX_right[params.mode[1]];
	}
}
