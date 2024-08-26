#pragma once
#include "cache.hh"
#include "params.hh"
#include "sampler_calcs.hh"
#include <cstdint>

namespace SamplerKit
{

struct SampleState {
	// file position where we began playback.
	uint32_t sample_file_startpos;
	int anchor_cuenum = -1;

	// file position where we will end playback. endpos > startpos when REV==0, endpos < startpos when REV==1
	uint32_t sample_file_endpos;

	// current file position being read. Must match the actual open file's position. This is always inc/decrementing
	// from startpos towards endpos
	uint32_t sample_file_curpos[NumSamplesPerBank];

	// Whether file is totally cached (from inst_start to inst_end)
	bool is_buffered_to_file_end[NumSamplesPerBank];

	uint32_t play_buff_bufferedamt[NumSamplesPerBank];

	bool cached_rev_state[NumSamplesPerBank];

	FIL fil[NumSamplesPerBank];
	Cache cache[NumSamplesPerBank];

	void check_sample_end(Params &params,
						  SampleList &samples,
						  std::array<CircularBuffer, NumSamplesPerBank> &play_buff,
						  Flags &flags) {
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
			uint32_t sample_file_playpos = cache[samplenum].map_buffer_to_cache(
				play_buff[samplenum].out, s_sample.sampleByteSize, &play_buff[samplenum]);

			// Calculate the distance left to the end that we should be playing
			// TODO: check if playpos is in bounds of startpos as well
			uint32_t dist_to_end;
			if (!params.reverse)
				dist_to_end =
					(sample_file_endpos > sample_file_playpos) ? (sample_file_endpos - sample_file_playpos) : 0;
			else
				dist_to_end =
					(sample_file_playpos > sample_file_endpos) ? (sample_file_playpos - sample_file_endpos) : 0;

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
				play_buff_bufferedamt[samplenum] = play_buff[samplenum].distance(params.reverse);

				if (!is_buffered_to_file_end[samplenum] && play_buff_bufferedamt[samplenum] <= resampled_buffer_size) {
					// buffer underrun: tried to read too much out. Try to recover!
					// g_error |= READ_BUFF1_UNDERRUN;
					// check_errors();
					params.play_state = PlayStates::PREBUFFERING;
				}
			}
		}
	}
};
} // namespace SamplerKit
