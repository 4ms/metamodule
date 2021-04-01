#include "audio.hh"
#include "conf/hsem_conf.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "drivers/syscfg.hh"
#include "patch_player.hh"

namespace MetaModule
{
constexpr bool DEBUG_PASSTHRU_AUDIO = false;

AudioStream::AudioStream(PatchList &patches,
						 PatchPlayer &patchplayer,
						 ICodec &codec,
						 AnalogOutT &dac,
						 ParamCache &param_cache,
						 UiAudioMailbox &uiaudiomailbox,
						 DoubleBufParamBlock &p,
						 AudioStreamBlock (&buffers)[4])
	: cache{param_cache}
	, mbox{uiaudiomailbox}
	, param_blocks{p}
	, tx_buf_1{buffers[0]}
	, tx_buf_2{buffers[1]}
	, rx_buf_1{buffers[2]}
	, rx_buf_2{buffers[3]}
	, codec_{codec}
	, sample_rate_{codec.get_samplerate()}
	, dac{dac}
	, patch_list{patches}
	, player{patchplayer}
{

	codec_.set_txrx_buffers(reinterpret_cast<uint8_t *>(tx_buf_1.data()),
							reinterpret_cast<uint8_t *>(rx_buf_1.data()),
							AudioConf::DMABlockSize * 2);
	codec_.set_callbacks(
		[this]() {
			Debug::Pin0::high();
			HWSemaphore<ParamsBuf1Lock>::lock();
			HWSemaphore<ParamsBuf2Lock>::unlock();
			process(rx_buf_1, tx_buf_1, param_blocks[0]);
			Debug::Pin0::low();
		},
		[this]() {
			Debug::Pin0::high();
			HWSemaphore<ParamsBuf2Lock>::lock();
			HWSemaphore<ParamsBuf1Lock>::unlock();
			process(rx_buf_2, tx_buf_2, param_blocks[1]);
			Debug::Pin0::low();
		});

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

void AudioStream::output_silence(AudioStreamBlock &out)
{
	for (auto &out_ : out) {
		out_.l = 0;
		out_.r = 0;
		dac.queue_sample(0, 0x00800000);
		dac.queue_sample(1, 0x00800000);
	}
}

// Todo: integrate these:
// params.gate_ins[]
// params.clock_in
// params.patch_cv
// params.buttons[]
// params.jack_senses[]

void AudioStream::process(AudioStreamBlock &in, AudioStreamBlock &out, ParamBlock &param_block)
{
	param_block.metaparams.audio_load = load_measure.get_last_measurement_load_percent();
	cache.write_sync(param_block.params[0], param_block.metaparams);
	load_measure.start_measurement();

	// Setting audio_is_muted to true notifies UI that it's safe to load a new patch
	// Todo: fade down before setting audio_is_muted to true
	mbox.audio_is_muted = mbox.loading_new_patch ? true : false;

	if (mbox.audio_is_muted) {
		output_silence(out);
		return;
	}

	auto in_ = in.begin();
	auto params_ = param_block.params.begin();
	for (auto &out_ : out) {
		if constexpr (DEBUG_PASSTHRU_AUDIO) {
			out_.l = in_->l;
			out_.r = in_->r;
			dac.queue_sample(0, out_.r + 0x00800000);
			dac.queue_sample(1, out_.l + 0x00800000);
			in_++;
			continue;
		}
		int i;

		player.set_panel_input(0, AudioFrame::scaleInput(in_->l));
		player.set_panel_input(1, AudioFrame::scaleInput(in_->r));

		i = 0;
		for (auto &cv : params_->cvjacks) {
			player.set_panel_input(i + NumAudioInputs, cv);
			i++;
		}
		i = 0;
		for (auto &knob : params_->knobs) {
			player.set_panel_param(i, knob);
			i++;
		}

		player.update_patch(patch_list.cur_patch());

		// FixMe: Why are the L/R samples swapped in the DMA buffer? The L/R jacks are not swapped on hardware
		// Todo: scope the data stream vs. LR clk
		out_.l = get_output(1);
		out_.r = get_output(0);

		dac.queue_sample(0, get_output(2) + 0x00800000);
		dac.queue_sample(1, get_output(3) + 0x00800000);

		in_++;
		params_++;
	}

	load_measure.end_measurement();
}

void AudioStream::start()
{
	codec_.start();
	dac_updater.start();
}

// TODO: not used, remove?
void AudioStream::send_zeros_to_patch()
{
	for (int i = 0; i < NumAudioInputs; i++)
		player.set_panel_input(i, 0);

	for (int i = 0; i < NumCVInputs; i++)
		player.set_panel_input(i + NumAudioInputs, 0);

	for (int i = 0; i < NumKnobs; i++)
		player.set_panel_param(i, 0);
}

} // namespace MetaModule
