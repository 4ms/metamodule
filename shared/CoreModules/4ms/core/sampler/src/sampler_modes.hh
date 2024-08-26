#pragma once
#include "audio_memory.hh"
// #include "audio_stream_conf.hh"
#include "bank.hh"
#include "cache.hh"
#include "circular_buffer.hh"
#include "errors.hh"
#include "flags.hh"
#include "params.hh"
#include "sampler_calcs.hh"
#include "sampler_state.hh"
#include "sdcard.hh"
// #include "wav_recording.hh"

namespace SamplerKit
{

class SamplerModes {
	static constexpr uint32_t NUM_SAMPLES_PER_BANK = NumSamplesPerBank;

	Params &params;
	Flags &flags;
	Sdcard &sd;
	SampleList &samples;
#ifndef METAMODULE
	Recorder &recorder;
#endif

	SampleState &state;
	uint32_t time;

	std::array<CircularBuffer, NumSamplesPerBank> &play_buff;
	uint32_t &g_error;

	float env_level;
	float env_rate = 0.f;

	uint32_t last_play_start_tmr;

public:
	// current file position being read. Must match the actual open file's position. This is always inc/decrementing
	// from startpos towards endpos
	uint32_t sample_file_curpos[NumSamplesPerBank];

	bool cached_rev_state[NumSamplesPerBank];

	FIL fil[NumSamplesPerBank];

	SamplerModes(Params &params,
				 Flags &flags,
				 Sdcard &sd,
				 BankManager &banks,
#ifndef METAMODULE
	// Recorder &recorder,
#endif
				 SampleState &state,
				 std::array<CircularBuffer, NumSamplesPerBank> &splay_buff,
				 uint32_t &g_error)
		: params{params}
		, flags{flags}
		, sd{sd}
		, samples{banks.samples}
#ifndef METAMODULE
		, recorder{recorder}
#endif
		, state{state}
		, play_buff{splay_buff}
		, g_error{g_error} {

		for (unsigned i = 0; i < NumSamplesPerBank; i++) {
			state.cache[i].map_pt = play_buff[i].min;
			state.cache[i].low = 0;
			state.cache[i].high = 0;
			cached_rev_state[i] = 0;
			state.play_buff_bufferedamt[i] = 0;
			state.is_buffered_to_file_end[i] = 0;

			// fil[i].obj.fs = nullptr;
		}

		// Verify the channels are set to enabled banks, and correct if necessary
		params.bank = params.settings.startup_bank;
		if (!banks.is_bank_enabled(params.bank))
			params.bank = banks.next_enabled_bank(MaxNumBanks - 1);

		flags.set(Flag::PlaySampleChanged);
		flags.set(Flag::PlayBuffDiscontinuity);
		flags.set(Flag::ForceFileReload);
	}

	// FIXME: Split up the state machinery and the sd card IO
	// Then only call the SD card io from the main loop update()
	// And call the state machinery in the audio callback (before/after params.update())
	void process_mode_flags(uint32_t time) {
		this->time = time;

		if (flags.take(Flag::RevTrig))
			toggle_reverse();

		if (flags.take(Flag::PlayBut))
			toggle_playing();

		if (flags.read(Flag::PlayTrigDelaying)) {
			uint32_t time_since_play_trig = time - params.play_trig_timestamp;
			if (time_since_play_trig >= params.settings.play_trig_latch_pitch_time)
				flags.clear(Flag::LatchVoltOctCV);
			else
				flags.set(Flag::LatchVoltOctCV);

			if (time_since_play_trig >= params.settings.play_trig_delay) {
				flags.set(Flag::PlayTrig);
				flags.clear(Flag::PlayTrigDelaying);
			}
		}

		if (flags.take(Flag::PlayTrig)) {
			start_restart_playing();
			flags.clear(Flag::LatchVoltOctCV);
		}

#ifndef METAMODULE
		if (flags.take(Flag::RecBut))
			recorder.toggle_recording();

		if (flags.take(Flag::RecTrig))
			recorder.toggle_recording();
#endif

		if (flags.take(Flag::ToggleLooping)) {
			params.looping = !params.looping;
			if (params.looping && params.play_state == PlayStates::SILENT)
				toggle_playing();
		}

		if (flags.take(Flag::ToggleStereoMode)) {
			params.settings.stereo_mode = !params.settings.stereo_mode;
			flags.set(Flag::ToggleStereoModeAnimate);
		}

		if (flags.take(Flag::EnterPlayMode))
			params.op_mode = OperationMode::Playback;

		if (flags.take(Flag::EnterRecordMode)) {
			params.op_mode = OperationMode::Record;
			params.looping = false;
			// Stop playing
			switch (params.play_state) {
				case PlayStates::PLAYING:
				case PlayStates::PLAY_FADEUP:
				case PlayStates::PLAY_FADEDOWN:
				case PlayStates::PERC_FADEUP:
				case PlayStates::PLAYING_PERC:
				case PlayStates::REV_PERC_FADEDOWN:
				case PlayStates::RETRIG_FADEDOWN:
					params.play_state = PlayStates::PLAY_FADEDOWN;
					break;

				case PlayStates::SILENT:
				case PlayStates::PAD_SILENCE:
				case PlayStates::PREBUFFERING:
					params.play_state = PlayStates::SILENT;
					break;
			}
		}
	}

	// GCC_OPTIMIZE_OFF
	void start_playing() {
		FRESULT res;
		float rs;

		uint8_t samplenum = params.sample;
		uint8_t banknum = params.bank;
		Sample *s_sample = &(samples[banknum][samplenum]);

		if (s_sample->filename[0] == 0)
			return;

		params.sample_num_now_playing = samplenum;

		if (banknum != params.sample_bank_now_playing) {
			params.sample_bank_now_playing = banknum;
			init_changed_bank();
		}

		// Reload the sample file if necessary:
		// Force Reload flag is set (Edit mode, or loaded new index)
		// File is empty (never been read since entering this bank)
		// Sample File Changed flag is set (new file was recorded into this slot)
		if (flags.take(Flag::ForceFileReload) || /*(fil[samplenum].obj.fs == 0) ||*/
			(s_sample->file_status == FileStatus::NewFile))
		{
			res = reload_sample_file(&fil[samplenum], s_sample, sd);
			if (res != FR_OK) {
				g_error |= FILE_OPEN_FAIL;
				params.play_state = PlayStates::SILENT;
				return;
			}
			s_sample->file_status = FileStatus::Found;

			res = sd.create_linkmap(&fil[samplenum], samplenum);
			if (res == FR_NOT_ENOUGH_CORE) {
				g_error |= FILE_CANNOT_CREATE_CLTBL;
			} // ToDo: Log this error
			else if (res != FR_OK)
			{
				g_error |= FILE_CANNOT_CREATE_CLTBL;
				f_close(&fil[samplenum]);
				params.play_state = PlayStates::SILENT;
				return;
			}

			// Check the file is really as long as the sampleSize says it is
			if (f_size(&fil[samplenum]) < (s_sample->startOfData + s_sample->sampleSize)) {
				s_sample->sampleSize = f_size(&fil[samplenum]) - s_sample->startOfData;

				if (s_sample->inst_end > s_sample->sampleSize)
					s_sample->inst_end = s_sample->sampleSize;

				if ((s_sample->inst_start + s_sample->inst_size) > s_sample->sampleSize)
					s_sample->inst_size = s_sample->sampleSize - s_sample->inst_start;
			}

			state.cache[samplenum].low = 0;
			state.cache[samplenum].high = 0;
			state.cache[samplenum].map_pt = play_buff[samplenum].min;
		}

		// Calculate our actual resampling rate
		rs = params.pitch * ((float)s_sample->sampleRate / params.settings.record_sample_rate);

		// Determine starting and ending addresses
		if (params.settings.use_cues && s_sample->num_cues > 0) {
			state.anchor_cuenum = calc_start_cuenum(params.start, s_sample);
		} else
			state.anchor_cuenum = -1;

		uint32_t earlier_pos = calc_start_point(params.start, s_sample, state.anchor_cuenum, params.settings.use_cues);

		// TODO: this should be updated continuously in params.update()
		// whenenver length, pitch, start, or sample slot/bank changes
		// => params.file_startpos, params.file_endpos
		uint32_t later_pos = calc_stop_point(
			params.length, rs, s_sample, earlier_pos, state.anchor_cuenum, params.settings.record_sample_rate);

		if (params.reverse) {
			state.sample_file_endpos = earlier_pos;
			state.sample_file_startpos = later_pos;
		} else {
			state.sample_file_startpos = earlier_pos;
			state.sample_file_endpos = later_pos;
		}

		// See if the starting position is already cached
		if ((state.cache[samplenum].high > state.cache[samplenum].low) &&
			(state.cache[samplenum].low <= state.sample_file_startpos) &&
			(state.sample_file_startpos <= state.cache[samplenum].high))
		{
			play_buff[samplenum].out = state.cache[samplenum].map_cache_to_buffer(
				state.sample_file_startpos, s_sample->sampleByteSize, &play_buff[samplenum]);

			env_level = 0.f;
			if (params.length <= 0.5f)
				params.play_state = params.reverse ? PlayStates::PLAYING_PERC : PlayStates::PERC_FADEUP;
			else
				params.play_state = PlayStates::PLAY_FADEUP;

		} else {
			//...otherwise, start buffering from scratch
			// Set state to silent so we don't run play_audio_buffer(), which could result in a glitch since the
			// playbuff and cache values are being changed
			params.play_state = PlayStates::SILENT;
			play_buff[samplenum].init();

			// Seek to the file position where we will start reading
			sample_file_curpos[samplenum] = state.sample_file_startpos;
			res = set_file_pos(banknum, samplenum);

			// If seeking fails, perhaps we need to reload the file
			if (res != FR_OK) {

				res = reload_sample_file(&fil[samplenum], s_sample, sd);
				if (res != FR_OK) {
					g_error |= FILE_OPEN_FAIL;
					params.play_state = PlayStates::SILENT;
					return;
				}

				res = sd.create_linkmap(&fil[samplenum], samplenum);
				if (res != FR_OK) {
					g_error |= FILE_CANNOT_CREATE_CLTBL;
					f_close(&fil[samplenum]);
					params.play_state = PlayStates::SILENT;
					return;
				}

				res = set_file_pos(banknum, samplenum);
				if (res != FR_OK) {
					g_error |= FILE_SEEK_FAIL;
				}
			}
			if (g_error & LSEEK_FPTR_MISMATCH) {
				state.sample_file_startpos =
					align_addr(f_tell(&fil[samplenum]) - s_sample->startOfData, s_sample->blockAlign);
			}

			state.cache[samplenum].low = state.sample_file_startpos;
			state.cache[samplenum].high = state.sample_file_startpos;
			state.cache[samplenum].map_pt = play_buff[samplenum].min;
			state.cache[samplenum].size = (play_buff[samplenum].size >> 1) * s_sample->sampleByteSize;
			state.is_buffered_to_file_end[samplenum] = 0;

			params.play_state = PlayStates::PREBUFFERING;
		}

		// used by toggle_reverse() to see if we hit a reverse trigger right after a play trigger
		last_play_start_tmr = time;

		flags.set(Flag::PlayBuffDiscontinuity);
		flags.set(Flag::StartFadeUp);

#ifdef DEBUG_ENABLED
		// str_cpy(dbg_sample.filename, s_sample->filename);
		// dbg_sample.sampleSize = s_sample->sampleSize;
		// dbg_sample.sampleByteSize = s_sample->sampleByteSize;
		// dbg_sample.sampleRate = s_sample->sampleRate;
		// dbg_sample.numChannels = s_sample->numChannels;
		// dbg_sample.startOfData = s_sample->startOfData;
		// dbg_sample.blockAlign = s_sample->blockAlign;
		// dbg_sample.PCM = s_sample->PCM;
		// dbg_sample.inst_start = s_sample->inst_start;
		// dbg_sample.inst_end = s_sample->inst_end;
		// dbg_sample.inst_size = s_sample->inst_size;
		// dbg_sample.inst_gain = s_sample->inst_gain;
#endif
	}

	void check_sample_end() {
		if (params.play_state == PlayStates::PLAYING || params.play_state == PlayStates::PLAY_FADEUP ||
			params.play_state == PlayStates::PLAYING_PERC || params.play_state == PlayStates::PERC_FADEUP)
		{
			float length = params.length;
			uint8_t samplenum = params.sample_num_now_playing;
			uint8_t banknum = params.sample_bank_now_playing;
			Sample &s_sample = samples[banknum][samplenum];

			float rs = (s_sample.sampleRate == params.settings.record_sample_rate) ?
						   params.pitch :
						   params.pitch * ((float)s_sample.sampleRate / (float)params.settings.record_sample_rate);

			// Amount play_buff[]->out changes with each audio block sent to the codec
			uint32_t resampled_buffer_size = calc_resampled_buffer_size(s_sample, rs);

			// Amount an imaginary pointer in the sample file would move with each audio block sent to the codec
			int32_t resampled_cache_size = calc_resampled_cache_size(s_sample, resampled_buffer_size);

			// Amount in the sample file we have remaining before we hit sample_file_endpos
			// int32_t dist_to_end = calc_dist_to_end(s_sample, banknum);
			// Find out where the audio output data is relative to the start of the cache
			uint32_t sample_file_playpos = state.cache[samplenum].map_buffer_to_cache(
				play_buff[samplenum].out, s_sample.sampleByteSize, &play_buff[samplenum]);

			// Calculate the distance left to the end that we should be playing
			// TODO: check if playpos is in bounds of startpos as well
			uint32_t dist_to_end;
			if (!params.reverse)
				dist_to_end = (state.sample_file_endpos > sample_file_playpos) ?
								  (state.sample_file_endpos - sample_file_playpos) :
								  0;
			else
				dist_to_end = (sample_file_playpos > state.sample_file_endpos) ?
								  (sample_file_playpos - state.sample_file_endpos) :
								  0;

			// See if we are about to surpass the calculated position in the file where we should end our sample
			// We must start fading down at a point that depends on how long it takes to fade down

			uint32_t fadedown_blocks = calc_perc_fadedown_blocks(length, (float)params.settings.record_sample_rate) + 1;
			PlayStates fadedown_state = PlayStates::REV_PERC_FADEDOWN;

			if (dist_to_end < (resampled_cache_size * fadedown_blocks)) {
				params.play_state = fadedown_state;
				if (params.play_state != PlayStates::PLAYING_PERC)
					flags.clear(Flag::ChangePlaytoPerc);
			} else {
				// Check if we are about to hit buffer underrun
				state.play_buff_bufferedamt[samplenum] = play_buff[samplenum].distance(params.reverse);

				if (!state.is_buffered_to_file_end[samplenum] &&
					state.play_buff_bufferedamt[samplenum] <= resampled_buffer_size)
				{
					// buffer underrun: tried to read too much out. Try to recover!
					g_error |= READ_BUFF1_UNDERRUN;
					// check_errors();
					params.play_state = PlayStates::PREBUFFERING;
				}
			}
		}
	}

	FRESULT set_file_pos(uint8_t b, uint8_t s) {
		FRESULT r = f_lseek(&fil[s], samples[b][s].startOfData + sample_file_curpos[s]);
		if (fil[s].fptr != (samples[b][s].startOfData + sample_file_curpos[s]))
			g_error |= LSEEK_FPTR_MISMATCH;
		return r;
	}

	void reverse_file_positions(uint8_t samplenum, uint8_t banknum, bool new_dir) {
		// Swap sample_file_curpos with cache_high or _low
		// and move ->in to the equivalant address in play_buff
		// This gets us ready to read new data to the opposite end of the cache.
		if (new_dir) {
			sample_file_curpos[samplenum] = state.cache[samplenum].low;
			play_buff[samplenum].in = state.cache[samplenum].map_pt; // cache_map_pt is the map of cache_low
		} else {
			sample_file_curpos[samplenum] = state.cache[samplenum].high;
			play_buff[samplenum].in = state.cache[samplenum].map_cache_to_buffer(
				state.cache[samplenum].high, samples[banknum][samplenum].sampleByteSize, &play_buff[samplenum]);
		}

		// Swap the endpos with the startpos
		// This way, curpos is always moving towards endpos and away from startpos
		std::swap(state.sample_file_endpos, state.sample_file_startpos);

		// Seek the starting position in the file
		// This gets us ready to start reading from the new position
		if (fil[samplenum].obj.id > 0) {
			FRESULT res;
			res = set_file_pos(banknum, samplenum);
			if (res != FR_OK)
				g_error |= FILE_SEEK_FAIL;
		}
	}

private:
	void toggle_reverse() {
		uint8_t samplenum, banknum;

		if (params.play_state == PlayStates::PLAYING || params.play_state == PlayStates::PLAYING_PERC ||
			params.play_state == PlayStates::PREBUFFERING || params.play_state == PlayStates::PLAY_FADEUP ||
			params.play_state == PlayStates::PERC_FADEUP)
		{
			samplenum = params.sample_num_now_playing;
			banknum = params.sample_bank_now_playing;
		} else {
			samplenum = params.sample;
			banknum = params.bank;
		}

		// Prevent issues if playback interrupts this routine
		PlayStates tplay_state = params.play_state;
		params.play_state = PlayStates::SILENT;

		// If we are PREBUFFERING or PLAY_FADEUP, then that means we just started playing.
		// It could be the case a common trigger fired into PLAY and REV, but the PLAY trig was detected first
		// So we actually want to make it play from the end of the sample rather than reverse direction from the current
		// spot
		if (tplay_state == PlayStates::PREBUFFERING || tplay_state == PlayStates::PLAY_FADEUP ||
			tplay_state == PlayStates::PLAYING || tplay_state == PlayStates::PERC_FADEUP)
		{
			// Handle a rev trig shortly after a play trig by playing as if the rev trig was first
			if ((time - last_play_start_tmr) < (params.settings.record_sample_rate * 0.1f)) // 100ms
			{
				// See if the endpos is within the cache, then we can just play from that point
				if ((state.sample_file_endpos >= state.cache[samplenum].low) &&
					(state.sample_file_endpos <= state.cache[samplenum].high))
				{
					play_buff[samplenum].out = state.cache[samplenum].map_cache_to_buffer(
						state.sample_file_endpos, samples[banknum][samplenum].sampleByteSize, &play_buff[samplenum]);
				} else {
					// Otherwise we have to make a new cache, so run start_playing()
					params.reverse = !params.reverse;
					start_playing();
					return;
				}
			}
		}
		params.reverse = !params.reverse;
		reverse_file_positions(samplenum, banknum, params.reverse);
		cached_rev_state[params.sample] = params.reverse;

		// Restore params.play_state
		params.play_state = tplay_state;
	}

	// Button->toggle
	void toggle_playing() {
		// Start playing
		if (params.play_state == PlayStates::SILENT || params.play_state == PlayStates::PLAY_FADEDOWN ||
			params.play_state == PlayStates::RETRIG_FADEDOWN || params.play_state == PlayStates::PREBUFFERING ||
			params.play_state == PlayStates::PLAY_FADEUP || params.play_state == PlayStates::PERC_FADEUP)
		{
			start_playing();
		}

		// Stop it if we're playing a full sample
		else if (params.play_state == PlayStates::PLAYING && params.length > 0.98f)
		{
			if (params.settings.length_full_start_stop) {
				params.play_state = PlayStates::PLAY_FADEDOWN;
				env_level = 1.f;
			} else
				params.play_state = PlayStates::RETRIG_FADEDOWN;

			// play_led_state = 0;
		}

		// Re-start if we're not near full length
		else if (params.play_state == PlayStates::PLAYING_PERC || params.play_state == PlayStates::PLAYING ||
				 params.play_state == PlayStates::PAD_SILENCE || params.play_state == PlayStates::REV_PERC_FADEDOWN)
		{
			params.play_state = PlayStates::RETRIG_FADEDOWN;
			// play_led_state = 0;
		}
	}

	// Trigger->start/restart
	void start_restart_playing() {
		// Start playing immediately if we have envelopes disabled for the mode that's playing, or we're not playing
		if ((!params.settings.fadeupdown_env &&
			 (params.play_state == PlayStates::PLAYING || params.play_state == PlayStates::PLAY_FADEDOWN)) ||
			(!params.settings.perc_env && params.play_state == PlayStates::PLAYING_PERC) ||
			params.play_state == PlayStates::SILENT || params.play_state == PlayStates::PREBUFFERING)
		{
			start_playing();
		}

		// Re-start if we're playing (and have envelopes enabled)
		else
		{
			params.play_state = PlayStates::RETRIG_FADEDOWN;
		}
	}

	void init_changed_bank() {
		uint8_t samplenum;
		FRESULT res;

		for (samplenum = 0; samplenum < NUM_SAMPLES_PER_BANK; samplenum++) {
			res = f_close(&fil[samplenum]);
			if (res != FR_OK)
				fil[samplenum].obj.fs = 0;

			state.is_buffered_to_file_end[samplenum] = 0;

			play_buff[samplenum].init();
		}
	}
};
} // namespace SamplerKit
