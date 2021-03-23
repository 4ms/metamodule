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
						 ParamBlock (&p)[2],
						 Params &last_params,
						 AudioStreamBlock (&buffers)[4])
	: codec_{codec}
	, sample_rate_{codec.get_samplerate()}
	, tx_buf_1{buffers[0]}
	, tx_buf_2{buffers[1]}
	, rx_buf_1{buffers[2]}
	, rx_buf_2{buffers[3]}
	, param_block_1{p[0]}
	, param_block_2{p[1]}
	, last_params{last_params}
	, dac{dac}
	, patch_list{patches}
	, player{patchplayer}
{
	load_patch();

	codec_.set_txrx_buffers(reinterpret_cast<uint8_t *>(tx_buf_1.data()),
							reinterpret_cast<uint8_t *>(rx_buf_1.data()),
							AudioConf::DMABlockSize * 2);
	codec_.set_callbacks(
		[this]() {
			HWSemaphore<ParamsBuf1Lock>::lock();
			HWSemaphore<ParamsBuf2Lock>::unlock();
			process(rx_buf_1, tx_buf_1, param_block_1);
		},
		[this]() {
			HWSemaphore<ParamsBuf2Lock>::lock();
			HWSemaphore<ParamsBuf1Lock>::unlock();
			process(rx_buf_2, tx_buf_2, param_block_2);
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

// Todo: integrate these:
// params.gate_ins[]
// params.clock_in
// params.patch_cv
// params.buttons[]
// params.jack_senses[]

void AudioStream::process(AudioStreamBlock &in, AudioStreamBlock &out, ParamBlock &param_block)
{
	Debug::Pin0::high();
	load_measure.start_measurement();

	SCB_InvalidateDCache_by_Addr((uint32_t *)&param_block, sizeof(ParamBlock));

	last_params = param_block[0];
	check_patch_change(last_params.rotary_motion);

	auto in_ = in.begin();
	auto params_ = param_block.begin();
	for (auto &out_ : out) {
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
		params_++;
	}

	Debug::Pin0::low();
	load_measure.end_measurement();
	patch_list.audio_load = load_measure.get_last_measurement_load_percent();
}

void AudioStream::start()
{
	codec_.start();

	dac_updater.start();
}

bool AudioStream::check_patch_change(int motion)
{
	if (motion > 0) {
		player.unload_patch(patch_list.cur_patch());
		patch_list.next_patch();
		load_patch();
		return true;
	} else if (motion < 0) {
		player.unload_patch(patch_list.cur_patch());
		patch_list.prev_patch();
		load_patch();
		return true;
	}
	return false;
}

void AudioStream::load_patch()
{
	bool ok = player.load_patch(patch_list.cur_patch());

	for (int i = 0; i < NumAudioInputs; i++)
		player.set_panel_input(i, 0);

	for (int i = 0; i < NumCVInputs; i++)
		player.set_panel_input(i + NumAudioInputs, last_params.cvjacks[i]);

	for (int i = 0; i < NumKnobs; i++)
		player.set_panel_param(i, last_params.knobs[i]);

	if (!ok) {
		while (1) {
			; // Todo: Display error on screen: Cannot load patch
		}
	}
}

} // namespace MetaModule
