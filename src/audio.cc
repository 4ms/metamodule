#include "audio.hh"

Audio::Audio(Params &p, ICodec &codec, uint32_t sample_rate)
	: params{p}
	, codec_{codec}
	, sample_rate_{sample_rate}
{
	// Todo: get this working:
	// for (auto &fx : FX_left)
	// 	fx.set_samplerate(sample_rate_);
	// for (auto &fx : FX_right)
	// 	fx.set_samplerate(sample_rate_);
	current_fx[LEFT] = FX_left[0];
	current_fx[LEFT]->set_samplerate(sample_rate_);
	current_fx[RIGHT] = FX_right[0];
	current_fx[RIGHT]->set_samplerate(sample_rate_);

	codec_.set_txrx_buffers(reinterpret_cast<uint8_t *>(tx_buf_[0].data()),
							reinterpret_cast<uint8_t *>(rx_buf_[0].data()),
							kAudioStreamDMABlockSize * 2);
}

void Audio::process(AudioStreamBlock &in, AudioStreamBlock &out)
{
	params.update();
	check_fx_change();

	current_fx[LEFT]->set_param(0, params.freq[0]);
	current_fx[LEFT]->set_param(1, params.res[0]);
	current_fx[RIGHT]->set_param(0, params.freq[1]);
	current_fx[RIGHT]->set_param(1, params.res[1]);
	//freq0.set_new_value(params.freq[0]);

	auto in_ = in.begin();
	for (auto &out_ : out) {
		auto scaled_in = AudioFrame::scaleInput(in_->l);
		auto unscaled_out = current_fx[LEFT]->update(scaled_in);
		out_.l = AudioFrame::scaleOutput(unscaled_out);

		scaled_in = AudioFrame::scaleInput(in_->r);
		unscaled_out = current_fx[RIGHT]->update(scaled_in);
		out_.r = AudioFrame::scaleOutput(unscaled_out);

		//current_fx[LEFT]->set_param(0, freq0.next());
		in_++;
	}
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
		current_fx[LEFT]->set_samplerate(sample_rate_);
	}
	if (current_fx[RIGHT] != FX_right[params.mode[1]]) {
		// Todo: start crossfading
		current_fx[RIGHT] = FX_right[params.mode[1]];
		current_fx[RIGHT]->set_samplerate(sample_rate_);
	}
}

