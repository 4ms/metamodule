#include "audio.hh"
#include "arch.hh"
#include "conf/hsem_conf.hh"
#include "debug.hh"
#include "drivers/cache.hh"
#include "drivers/hsem.hh"
#include "patch_player.hh"

namespace MetaModule
{
constexpr bool DEBUG_PASSTHRU_AUDIO = false;

// Clock in -> clock out latency: 1.33ms (one audio DMA half-transfer)
// Gate In -> audio OUt latency: 1.90ms
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

	codec_.init();
	codec_.set_txrx_buffers(reinterpret_cast<uint8_t *>(tx_buf_1.data()),
							reinterpret_cast<uint8_t *>(rx_buf_1.data()),
							AudioConf::DMABlockSize * 2);
	codec_.set_callbacks(
		[this]() {
			Debug::Pin0::high();
			HWSemaphore<ParamsBuf1Lock>::lock();
			HWSemaphore<ParamsBuf2Lock>::unlock();

			if constexpr (target::TYPE == SupportedTargets::stm32h7x5)
				process(rx_buf_1, tx_buf_1, param_blocks[0]);
			else {
				target::SystemCache::invalidate_dcache_by_range(&rx_buf_2, sizeof(AudioStreamBlock));
				target::SystemCache::invalidate_dcache_by_range(&(param_blocks[0]), sizeof(ParamBlock));
				process(rx_buf_2, tx_buf_2, param_blocks[0]);
				target::SystemCache::clean_dcache_by_range(&tx_buf_2, sizeof(AudioStreamBlock));
			}
			Debug::Pin0::low();
		},
		[this]() {
			Debug::Pin0::high();
			HWSemaphore<ParamsBuf2Lock>::lock();
			HWSemaphore<ParamsBuf1Lock>::unlock();
			if constexpr (target::TYPE == SupportedTargets::stm32h7x5)
				process(rx_buf_2, tx_buf_2, param_blocks[1]);
			else {
				target::SystemCache::invalidate_dcache_by_range(&rx_buf_1, sizeof(AudioStreamBlock));
				target::SystemCache::invalidate_dcache_by_range(&(param_blocks[1]), sizeof(ParamBlock));
				process(rx_buf_1, tx_buf_1, param_blocks[1]);
				target::SystemCache::clean_dcache_by_range(&tx_buf_1, sizeof(AudioStreamBlock));
			}
			Debug::Pin0::low();
		});

	dac.init();

	dac_updater.init(DAC_update_conf, [&]() {
		// static bool rising_edge = false;
		dac.output_next();
		// rising_edge = !rising_edge;
		// if (rising_edge)
		// 	clock_out.output_next();
	});
	load_measure.init();
}

AudioConf::SampleT AudioStream::get_audio_output(int output_id)
{
	auto raw_out = player.get_panel_output(output_id);
	auto scaled_out = AudioFrame::scaleOutput(raw_out);
	return scaled_out;
	// return compressor.compress(scaled_out);
}

uint32_t AudioStream::get_dac_output(int output_id)
{
	auto raw_out = player.get_panel_output(output_id);
	raw_out *= -1.f;
	auto scaled_out = AudioFrame::scaleOutput(raw_out);
	scaled_out += 0x00800000;
	return scaled_out;
}
// Todo: integrate these:
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

	if constexpr (DEBUG_PASSTHRU_AUDIO) {
		passthrough_audio(in, out);
		return;
	}

	auto in_ = in.begin();
	auto params_ = param_block.params.begin();
	for (auto &out_ : out) {
		int i;

		player.set_panel_input(0, AudioFrame::scaleInput(-1.f * in_->l)); // inputs are inverted in hardware PCB p3
		player.set_panel_input(1, AudioFrame::scaleInput(-1.f * in_->r));

		i = 0;
		for (auto &cv : params_->cvjacks) {
			// Todo: player.set_cv_input(i, cv);
			player.set_panel_input(i + NumAudioInputs, cv);
			i++;
		}
		i = 0;
		for (auto &gatein : params_->gate_ins) {
			// Todo: player.set_gate_input(i, cv);
			player.set_panel_input(i + NumAudioInputs + NumCVInputs, gatein.is_high() ? 1.f : 0.f);
			i++;
		}
		i = 0;
		for (auto &knob : params_->knobs) {
			player.set_panel_param(i, 0.5f); // knob);
			i++;
		}

		// dual LFO: 2us on H7, 31us on MP1, with cache it's 9us on MP1, now it's 1.43us on MP1
		player.update_patch(patch_list.cur_patch());

		out_.l = get_audio_output(LEFT_OUT);
		out_.r = get_audio_output(RIGHT_OUT);

		dac.queue_sample(0, get_dac_output(2));
		dac.queue_sample(1, get_dac_output(3));
		clock_out.queue_sample(player.get_panel_output(4) > 0.5f ? true : false);

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

void AudioStream::output_silence(AudioStreamBlock &out)
{
	for (auto &out_ : out) {
		out_.l = 0;
		out_.r = 0;
		dac.queue_sample(0, 0x00800000);
		dac.queue_sample(1, 0x00800000);
	}
}

void AudioStream::passthrough_audio(AudioStreamBlock &in, AudioStreamBlock &out)
{
	auto in_ = in.begin();
	for (auto &out_ : out) {
		if constexpr (target::TYPE == SupportedTargets::stm32h7x5) {
			out_.l = -(in_->r); // inverted and channels swapped (H7 only)
			out_.r = -(in_->l);
		} else {
			out_.l = -(in_->l); // inverted (MP1 only)
			out_.r = -(in_->r);
		}
		dac.queue_sample(0, in_->l + 0x00800000);
		dac.queue_sample(1, in_->r + 0x00800000);
		in_++;
	}
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
