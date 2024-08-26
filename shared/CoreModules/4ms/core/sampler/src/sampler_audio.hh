#pragma once
#include "audio_stream_conf.hh"
#include "circular_buffer.hh"
#include "params.hh"
#include "resample.hh"
#include "sampler_calcs.hh"
#include "sampler_state.hh"
#include "util/cortex_math.hh"
#include "util/zip.hh"

namespace SamplerKit
{

class SamplerAudio {
	SampleState &sample_state;
	Params &params;
	Flags &flags;
	SampleList &samples;
	std::array<CircularBuffer, NumSamplesPerBank> &play_buff;

	using ChanBuff = std::array<AudioStreamConf::SampleT, AudioStreamConf::BlockSize>;

public:
	float env_level;
	float env_rate = 0.f;

	SamplerAudio(SampleState &state,
				 Params &params,
				 Flags &flags,
				 SampleList &samples,
				 std::array<CircularBuffer, NumSamplesPerBank> &splay_buff)
		: sample_state{state}
		, params{params}
		, flags{flags}
		, samples{samples}
		, play_buff{splay_buff} {
	}

	void update(const AudioStreamConf::AudioInBlock &inblock, AudioStreamConf::AudioOutBlock &outblock) {
		ChanBuff outL;
		ChanBuff outR;

		if (params.op_mode == OperationMode::Record) {
			for (auto [in, out] : zip(inblock, outblock)) {
				auto c0 = in.sign_extend(in.chan[0]);
				auto c1 = in.sign_extend(in.chan[1]);
				c0 *= Brain::AudioGain * 0.913f;
				c1 *= Brain::AudioGain * 0.913f;
				out.chan[0] = MathTools::signed_saturate(c0, 24);
				out.chan[1] = MathTools::signed_saturate(c1, 24);
			}
			return;
		}

		play_audio_from_buffer(outL, outR);

		if (params.settings.stereo_mode) {
			// Stereo mode
			// Left Out = Left Sample channel
			// Right Out = Right Sample channel
			//
			for (auto [out, L, R] : zip(outblock, outL, outR)) {
				// Chan 1 L + Chan 2 L clipped at signed 16-bits
				int32_t invL = -L;
				int32_t invR = -R;
				out.chan[1] = MathTools::signed_saturate(invL, 24);
				out.chan[0] = MathTools::signed_saturate(invR, 24);
			}
			return;
		}

		{
			// Mono mode
			// Left Out = -Right Out = average of L+R
			for (auto [out, L, R] : zip(outblock, outL, outR)) {
				// Average is already done in play_audio_from_buffer(), and put into outL
				int32_t invL = -L;
				out.chan[1] = MathTools::signed_saturate(invL, 24);
				out.chan[0] = MathTools::signed_saturate(L, 24);
			}
		}
	}

	void play_audio_from_buffer(ChanBuff &outL, ChanBuff &outR) {

		// Fill buffer with silence and return if we're not playing
		if (params.play_state == PlayStates::PREBUFFERING || params.play_state == PlayStates::SILENT) {
			for (auto [L, R] : zip(outL, outR)) {
				L = 0;
				R = 0;
			}
			return;
		}

		// Calculate our actual resampling rate, based on the sample rate of the file being played
		uint8_t samplenum = params.sample_num_now_playing;
		uint8_t banknum = params.sample_bank_now_playing;
		Sample &s_sample = samples[banknum][samplenum];

		float rs = (s_sample.sampleRate == params.settings.record_sample_rate) ?
					   params.pitch :
					   params.pitch * ((float)s_sample.sampleRate / (float)params.settings.record_sample_rate);

		sample_state.check_sample_end(params, samples, play_buff, flags);

		bool flush = flags.read(Flag::PlayBuffDiscontinuity);
		if (params.settings.stereo_mode) {
			if ((rs * s_sample.numChannels) > MAX_RS)
				rs = MAX_RS / (float)s_sample.numChannels;

			if (s_sample.numChannels == 2) {
				uint32_t t_u32 = play_buff[samplenum].out;
				resample_read<WavChan::Left>(rs, &play_buff[samplenum], outL, params.reverse, flush);

				play_buff[samplenum].out = t_u32;
				resample_read<WavChan::Right>(rs, &play_buff[samplenum], outR, params.reverse, flush);

			} else {
				// MONO: read left channel and copy to right
				bool flush = flags.read(Flag::PlayBuffDiscontinuity);
				resample_read<WavChan::Mono>(rs, &play_buff[samplenum], outL, params.reverse, flush);
				for (unsigned i = 0; i < outL.size(); i++)
					outR[i] = outL[i];
			}
		} else { // not STEREO_MODE:
			if (rs > MAX_RS)
				rs = MAX_RS;

			if (s_sample.numChannels == 2)
				resample_read<WavChan::Average>(rs, &play_buff[samplenum], outL, params.reverse, flush);
			else
				resample_read<WavChan::Mono>(rs, &play_buff[samplenum], outL, params.reverse, flush);
		}

		// TODO: if writing a flag gets expensive, then we could refactor this
		// The only purpose of this flag is to set flush=true when
		//  - loading A new sample, or
		//  - When rs goes from ==1 to !=1
		// Note that flush is ignored in resample_read when rs==1
		if (rs == 1.f)
			flags.set(Flag::PlayBuffDiscontinuity);
		else
			flags.clear(Flag::PlayBuffDiscontinuity);

		apply_envelopes(outL, outR);
	}

	// Linear fade of stereo data in outL and outR
	// Gain is a fixed gain to apply to all samples
	// Set rate to < 0 to fade down, > 0 to fade up
	// Returns amplitude applied to the last sample
	// Note: this increments amplitude before applying to the first sample
	static float fade(ChanBuff &outL, ChanBuff &outR, float gain, float starting_amp, float rate) {
		float amp = starting_amp;

		for (unsigned i = 0; i < outL.size(); i++) {
			amp += rate;
			if (amp >= 1.0f)
				amp = 1.0f;
			if (amp <= 0.f)
				amp = 0.f;
			outL[i] = (float)outL[i] * amp * gain;
			outR[i] = (float)outR[i] * amp * gain;
			outL[i] = MathTools::signed_saturate(outL[i], 24);
			outR[i] = MathTools::signed_saturate(outR[i], 24);
		}
		return amp;
	}

	static void apply_gain(ChanBuff &outL, ChanBuff &outR, float gain) {
		for (unsigned i = 0; i < outL.size(); i++) {
			outL[i] = (float)outL[i] * gain;
			outR[i] = (float)outR[i] * gain;
			outL[i] = MathTools::signed_saturate(outL[i], 24);
			outR[i] = MathTools::signed_saturate(outR[i], 24);
		}
	}

	void apply_envelopes(ChanBuff &outL, ChanBuff &outR) {
		if (flags.take(Flag::StartFadeUp))
			env_level = 0.f;
		if (flags.take(Flag::StartFadeDown))
			env_level = 1.f;

		uint8_t samplenum = params.sample_num_now_playing;
		uint8_t banknum = params.sample_bank_now_playing;
		Sample *s_sample = &(samples[banknum][samplenum]);

		float length = params.length;
		float gain = s_sample->inst_gain * params.volume;
		float rs = (s_sample->sampleRate == params.settings.record_sample_rate) ?
					   params.pitch :
					   params.pitch * ((float)s_sample->sampleRate / (float)params.settings.record_sample_rate);

		// Update the start/endpos based on the length parameter
		// Update the play_time (used to calculate led flicker and END OUT pulse width
		// ToDo: we should do this in update_params, so we can check if length or pitch changed
		float sr = params.settings.record_sample_rate;
		uint32_t anchor_pos = params.reverse ? sample_state.sample_file_endpos : sample_state.sample_file_startpos;
		uint32_t ending_pos = calc_stop_point(length, rs, s_sample, anchor_pos, sample_state.anchor_cuenum, sr);
		if (params.reverse)
			sample_state.sample_file_startpos = ending_pos;
		else
			sample_state.sample_file_endpos = ending_pos;

		const float fast_perc_fade_rate = calc_fast_perc_fade_rate(length, sr);

		// retrig fadedown rate is the faster of perc fade and global non-perc fadedown rate (larger rate == faster
		// fade)
		const float fast_retrig_fade_rate = (fast_perc_fade_rate < params.settings.fade_down_rate) ?
												params.settings.fade_down_rate :
												fast_perc_fade_rate;

		float play_time = (ending_pos - anchor_pos) / (s_sample->blockAlign * s_sample->sampleRate * params.pitch);

		switch (params.play_state) {
			case (PlayStates::RETRIG_FADEDOWN):
				env_rate =
					params.settings.fadeupdown_env ? fast_retrig_fade_rate : (1.0f / (float)AudioStreamConf::BlockSize);
				env_level = fade(outL, outR, gain, env_level, -1.f * env_rate);
				flicker_endout(play_time);

				if (env_level <= 0.f) {
					env_level = 0.f;
					// Start playing again unless we faded down because of a play trigger
					// TODO: Does this ever happen?
					if (!flags.read(Flag::PlayTrigDelaying))
						flags.set(Flag::PlayTrig);

					params.play_state = PlayStates::SILENT;
				}
				break;

			case (PlayStates::PLAY_FADEUP):
				if (params.settings.fadeupdown_env) {
					env_rate = params.settings.fade_up_rate;
					env_level = fade(outL, outR, gain, env_level, env_rate);
					if (env_level >= 1.f)
						params.play_state = PlayStates::PLAYING;

				} else {
					apply_gain(outL, outR, gain);
					params.play_state = PlayStates::PLAYING;
				}
				break;

			case (PlayStates::PERC_FADEUP):
				env_rate = fast_perc_fade_rate;
				if (params.settings.perc_env) {
					env_level = fade(outL, outR, gain, env_level, env_rate);
				} else {
					// same rate as fadeing, but don't apply the envelope
					apply_gain(outL, outR, gain);
					env_level += env_rate * AudioStreamConf::BlockSize;
				}
				if (env_level >= 1.f) {
					params.play_state = PlayStates::PLAYING_PERC;
					env_level = 1.f;
				}
				break;

			case (PlayStates::PLAYING):
				apply_gain(outL, outR, gain);
				if (length <= 0.5f)
					flags.set(Flag::ChangePlaytoPerc);
				break;

			case (PlayStates::PLAY_FADEDOWN):
				if (params.settings.fadeupdown_env) {
					env_rate = params.settings.fade_down_rate;
					env_level = fade(outL, outR, gain, env_level, -1.f * env_rate);
				} else {
					apply_gain(outL, outR, gain);
					env_level = 0.f; // set this so we detect "end of fade" in the next block
				}

				if (env_level <= 0.f) {
					flicker_endout(play_time);

					// Start playing again if we're looping, unless we faded down because of a play trigger
					if (params.looping && !flags.read(Flag::PlayTrigDelaying))
						flags.set(Flag::PlayTrig);

					params.play_state = PlayStates::SILENT;
				}
				break;

			case (PlayStates::PLAYING_PERC):
				env_rate = (params.reverse ? 1.f : -1.f) / (length * PERC_ENV_FACTOR);
				if (params.settings.perc_env) {
					env_level = fade(outL, outR, gain, env_level, env_rate);
				} else {
					// Calculate the envelope in order to keep the timing the same vs. PERC_ENVELOPE enabled,
					// but just don't apply the envelope
					apply_gain(outL, outR, gain);
					env_level += env_rate * AudioStreamConf::BlockSize;
				}

				// After fading up to full amplitude in a reverse percussive playback, fade back down to silence:
				if ((env_level >= 1.0f) && (params.reverse)) {
					params.play_state = PlayStates::REV_PERC_FADEDOWN;
					env_level = 1.f;
				} else
					check_perc_ending();
				break;

			case (PlayStates::REV_PERC_FADEDOWN):
				// Fade down to silence before going to PAD_SILENCE mode or ending the playback
				// (this prevents a click if the sample data itself doesn't cleanly fade out)
				env_rate = -1.f * fast_perc_fade_rate;
				if (params.settings.perc_env) {
					env_level = fade(outL, outR, gain, env_level, env_rate);
				} else {
					apply_gain(outL, outR, gain);
					env_level += env_rate * AudioStreamConf::BlockSize;
				}

				// If the end point is the end of the sample data (which happens if the file is very short, or if we're
				// at the end of it) Then pad it with silence so we keep a constant End Out period when looping
				if (env_level <= 0.f && sample_state.sample_file_endpos == s_sample->inst_end)
					params.play_state = PlayStates::PAD_SILENCE;
				else
					check_perc_ending();
				break;

			case (PlayStates::PAD_SILENCE):
				for (int i = 0; i < AudioStreamConf::BlockSize; i++) {
					outL[i] = 0;
					outR[i] = 0;
				}
				check_perc_ending();
				break;

			default: // PREBUFFERING or SILENT
				break;

		} // switch sampler_modes.play_state
	}

	void check_perc_ending() {
		// End the playback, go to silence, and trigger another play if looping
		if (env_level <= 0.0f || env_level >= 1.0f) {
			env_level = 0.0f;

			flicker_endout(params.length * 3.0f);

			// Restart loop
			if (params.looping && !flags.read(Flag::PlayTrigDelaying))
				flags.set(Flag::PlayTrig);

			params.play_state = PlayStates::SILENT;
		}
	}

	void flicker_endout(float tm) {
		if (tm > 0.3f)
			flags.set(Flag::EndOutLong);
		else
			flags.set(Flag::EndOutShort);
		// TODO: End Out on immediately to reduce jitter? Does it make a difference?
	}
};

} // namespace SamplerKit
