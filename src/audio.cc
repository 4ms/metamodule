#include "audio.hh"
#include "math.hh"

Audio::Audio(Params &p, I2CPeriph &i2c, uint32_t sample_rate)
	: params{p}
	, codec{i2c, sample_rate}
	, sample_rate_{sample_rate}
	, callback_tx_halfcomplete{*this}
	, callback_tx_complete{*this}
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

	codec.set_txrx_buffers(
		&(tx_buf_raw_[0][0]),
		&(rx_buf_raw_[0][0]),
		kAudioStreamDMABlockSize * sizeof(AudioFrame) / 4); //Todo: why / 4?
}

void Audio::process(AudioStreamBlock &in, AudioStreamBlock &out)
{
	params.update();
	check_fx_change();
	current_fx[LEFT]->set_param(0, params.freq[0]);
	current_fx[LEFT]->set_param(1, params.res[0]);
	current_fx[RIGHT]->set_param(0, params.freq[1]);
	current_fx[RIGHT]->set_param(1, params.res[1]);

	auto in_ = in.begin();
	for (auto &out_ : out) {
		auto scaled_in = AudioFrame::scaleInput(in_->l);
		auto unscaled_out = current_fx[LEFT]->update(scaled_in);
		out_.l = AudioFrame::scaleOutput(unscaled_out);

		scaled_in = AudioFrame::scaleInput(in_->r);
		unscaled_out = current_fx[RIGHT]->update(scaled_in);
		out_.r = AudioFrame::scaleOutput(unscaled_out);

		in_++;
	}
}

void Audio::start()
{
	codec.start();
}

void Audio::check_fx_change()
{
	if (current_fx[LEFT] != FX_left[params.mode[0]]) {
		//Todo: start crossfading
		current_fx[LEFT] = FX_left[params.mode[0]];
		current_fx[LEFT]->set_samplerate(sample_rate_);
	}
	if (current_fx[RIGHT] != FX_right[params.mode[1]]) {
		//Todo: start crossfading
		current_fx[RIGHT] = FX_right[params.mode[1]];
		current_fx[RIGHT]->set_samplerate(sample_rate_);
	}
}

Audio::TXCompleteCallback::TXCompleteCallback(Audio &a)
	: audiostream(a)
{
	HALCallbackManager::registerHALCB(HALCallbackID::SAI_TxCplt, this);
}

void Audio::TXCompleteCallback::halcb()
{
	audiostream.process(audiostream.rx_buf_[1], audiostream.tx_buf_[1]);
}

Audio::TXHalfCompleteCallback::TXHalfCompleteCallback(Audio &a)
	: audiostream(a)
{
	HALCallbackManager::registerHALCB(HALCallbackID::SAI_TxHalfCplt, this);
}
void Audio::TXHalfCompleteCallback::halcb()
{
	audiostream.process(audiostream.rx_buf_[0], audiostream.tx_buf_[0]);
}

