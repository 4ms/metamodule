#pragma once
#include "bank.hh"
#include "circular_buffer.hh"
#include "flags.hh"
#include "log.hh"
#include "params.hh"
#include "sampler_modes.hh"
#include "sdcard.hh"

namespace SamplerKit
{

class SampleLoader {
	SamplerModes &modes;
	SampleState &s;
	Params &params;
	Flags &flags;
	Sdcard &sd;
	SampleList &samples;
	std::array<CircularBuffer, NumSamplesPerBank> &play_buff;
	uint32_t &g_error;

	uint32_t last_update = 0;
	static constexpr uint32_t UpdateRate = 1;

public:
	SampleLoader(SamplerModes &modes,
				 SampleState &state,
				 Params &params,
				 Flags &flags,
				 Sdcard &sd,
				 BankManager &banks,
				 std::array<CircularBuffer, NumSamplesPerBank> &splay_buff,
				 uint32_t &g_error)
		: modes{modes}
		, s{state}
		, params{params}
		, flags{flags}
		, sd{sd}
		, samples{banks.samples}
		, play_buff{splay_buff}
		, g_error{g_error} {
	}

	void update(uint32_t time) {
		if (last_update == 0 || last_update - time > UpdateRate) {
			last_update = time;
			read_storage_to_buffer();
		}
	}

	uint32_t file_read_buffer[(READ_BLOCK_SIZE >> 2) + 2];

	void read_storage_to_buffer() {
		uint32_t err;

		FRESULT res;
		UINT br;
		uint32_t rd;

		// convenience variables
		uint8_t samplenum, banknum;
		Sample *s_sample;
		FSIZE_t t_fptr;
		float resample_amt;

		check_change_sample();
		check_change_bank();

		if ((params.play_state == PlayStates::SILENT) || (params.play_state == PlayStates::PLAY_FADEDOWN) ||
			(params.play_state == PlayStates::RETRIG_FADEDOWN))
			return;

		samplenum = params.sample_num_now_playing;
		banknum = params.sample_bank_now_playing;
		s_sample = &(samples[banknum][samplenum]);

		// FixMe: Calculate play_buff_bufferedamt after play_buff changes, not here, then make bufferedmat private
		// again
		s.play_buff_bufferedamt[samplenum] = play_buff[samplenum].distance(params.reverse);

		//
		// Try to recover from a file read error
		//
		if (g_error & FILE_READ_FAIL_1) {
			res = reload_sample_file(&s.fil[samplenum], s_sample, sd);
			if (res != FR_OK) {
				g_error |= FILE_OPEN_FAIL;
				params.play_state = PlayStates::SILENT;
				return;
			}

			res = sd.create_linkmap(&s.fil[samplenum], samplenum);
			if (res != FR_OK) {
				g_error |= FILE_CANNOT_CREATE_CLTBL;
				sd.f_close(&s.fil[samplenum]);
				params.play_state = PlayStates::SILENT;
				return;
			}

			// clear the error flag
			g_error &= ~FILE_READ_FAIL_1;

		} else {
			// FixMe: does this logic make sense for clearing is_buffered_to_file_end?
			if ((!params.reverse && (s.sample_file_curpos[samplenum] < s_sample->inst_end)) ||
				(params.reverse && (s.sample_file_curpos[samplenum] > s_sample->inst_start)))
				s.is_buffered_to_file_end[samplenum] = 0;
		}

		//
		// Calculate the amount to pre-buffer before we play:
		//
		resample_amt = params.pitch * (float)s_sample->sampleRate / (float)params.settings.record_sample_rate;
		float max_rs = params.settings.stereo_mode ? MAX_RS / s_sample->numChannels : MAX_RS;
		if (resample_amt > max_rs)
			resample_amt = max_rs;

		// Calculate how many bytes we need to pre-load in our buffer
		uint32_t pre_buff_amt =
			(float)(BASE_BUFFER_THRESHOLD * s_sample->blockAlign * s_sample->numChannels) * resample_amt;
		auto playback_buff_amt = std::clamp<uint32_t>(pre_buff_amt * 4, 0, (play_buff[samplenum].size * 7) / 10);
		uint32_t target_buff_amt = params.play_state == PlayStates::PREBUFFERING ? pre_buff_amt : playback_buff_amt;

		// Check if the we need to load more from SD Card to the buffer
		if (!s.is_buffered_to_file_end[samplenum] && (s.play_buff_bufferedamt[samplenum] < target_buff_amt)) {

			if (s.sample_file_curpos[samplenum] > s_sample->sampleSize) {
				// We read too much data somehow
				// TODO: When does this happen? sample_file_curpos has not changed recently...
				g_error |= FILE_WAVEFORMATERR;
				params.play_state = PlayStates::SILENT;
				modes.start_playing();

			} else if (s.sample_file_curpos[samplenum] > s_sample->inst_end) {
				// Buffered the end of the file, do not load any more
				s.is_buffered_to_file_end[samplenum] = 1;

			} else {
				// Forward reading:
				if (params.reverse == 0) {
					rd = s_sample->inst_end - s.sample_file_curpos[samplenum];

					if (rd > READ_BLOCK_SIZE)
						rd = READ_BLOCK_SIZE;

					res = sd.f_read(&s.fil[samplenum], file_read_buffer, rd, &br);

					if (res != FR_OK) {
						// FixMe: Do we really want to set this in case of disk error? We don't when reversing.
						g_error |= FILE_READ_FAIL_1;
						s.is_buffered_to_file_end[samplenum] = 1;
						pr_err("Err Read\n");
					}

					if (br < rd) {
						// unexpected EOF, but we can continue writing out the data we read
						g_error |= FILE_UNEXPECTEDEOF;
						s.is_buffered_to_file_end[samplenum] = 1;
						pr_err("Err EOF\n");
					}

					s.sample_file_curpos[samplenum] = f_tell(&s.fil[samplenum]) - s_sample->startOfData;

					if (s.sample_file_curpos[samplenum] >= s_sample->inst_end) {
						s.is_buffered_to_file_end[samplenum] = 1;
					}

				} else {
					// Reverse reading:
					rd = s.sample_file_curpos[samplenum] > s_sample->inst_start ?
							 s.sample_file_curpos[samplenum] - s_sample->inst_start :
							 0;

					if (rd >= READ_BLOCK_SIZE) {
						// Jump back a block
						rd = READ_BLOCK_SIZE;

						t_fptr = f_tell(&s.fil[samplenum]);
						res = sd.f_lseek(&s.fil[samplenum], t_fptr - READ_BLOCK_SIZE);
						if (res || (f_tell(&s.fil[samplenum]) != (t_fptr - READ_BLOCK_SIZE)))
							g_error |= LSEEK_FPTR_MISMATCH;

						s.sample_file_curpos[samplenum] = f_tell(&s.fil[samplenum]) - s_sample->startOfData;

					} else {
						// rd < READ_BLOCK_SIZE: read the first block
						// (which is the last to be read, since we're reversing)
						// TODO: align rd to 24?

						// Jump to the beginning
						s.sample_file_curpos[samplenum] = s_sample->inst_start;
						res = modes.set_file_pos(banknum, samplenum);
						if (res != FR_OK)
							g_error |= FILE_SEEK_FAIL;

						s.is_buffered_to_file_end[samplenum] = 1;
					}

					// Read one block forward
					t_fptr = f_tell(&s.fil[samplenum]);
					res = sd.f_read(&s.fil[samplenum], file_read_buffer, rd, &br);
					if (res != FR_OK)
						g_error |= FILE_READ_FAIL_1;

					if (br < rd)
						g_error |= FILE_UNEXPECTEDEOF;

					// Jump backwards to where we started reading
					res = sd.f_lseek(&s.fil[samplenum], t_fptr);
					if (res != FR_OK)
						g_error |= FILE_SEEK_FAIL;
					if (f_tell(&s.fil[samplenum]) != t_fptr)
						g_error |= LSEEK_FPTR_MISMATCH;
				}

				// Write temporary buffer to play_buff[]->in
				if (res != FR_OK)
					g_error |= FILE_READ_FAIL_1;
				else {
					// Jump back in play_buff by the amount just read (re-sized from file addresses to buffer
					// address)
					if (params.reverse)
						play_buff[samplenum].offset_in_address((rd * 2) / s_sample->sampleByteSize, 1);

					err = 0;

					//
					// Write raw file data (tmp_buff_u32) into buffer (play_buff)
					//

					// 16 bit
					if (s_sample->sampleByteSize == 2)
						err = play_buff[samplenum].memory_write_16as16((uint32_t *)file_read_buffer, rd >> 2, 0);

					// 24bit (rd must be a multiple of 3)
					else if (s_sample->sampleByteSize == 3)
						err = play_buff[samplenum].memory_write_24as16((uint8_t *)file_read_buffer, rd, 0);

					// 8bit
					else if (s_sample->sampleByteSize == 1)
						err = play_buff[samplenum].memory_write_8as16((uint8_t *)file_read_buffer, rd, 0);

					// 32-bit float (rd must be a multiple of 4)
					else if (s_sample->sampleByteSize == 4 && s_sample->PCM == 3)
						err = play_buff[samplenum].memory_write_32fas16((float *)file_read_buffer, rd >> 2, 0);

					// 32-bit int rd must be a multiple of 4
					else if (s_sample->sampleByteSize == 4 && s_sample->PCM == 1)
						err = play_buff[samplenum].memory_write_32ias16((uint8_t *)file_read_buffer, rd, 0);

					// Update the cache addresses
					if (params.reverse) {
						// Ignore head crossing error if we are reversing and ended up with in==out (that's
						// normal for the first reading)
						if (err && (play_buff[samplenum].in == play_buff[samplenum].out))
							err = 0;

						//
						// Jump back again in play_buff by the amount just read (re-sized from file addresses to
						// buffer address) This ensures play_buff[]->in points to the buffer seam
						//
						play_buff[samplenum].offset_in_address((rd * 2) / s_sample->sampleByteSize, 1);

						s.cache[samplenum].low = s.sample_file_curpos[samplenum];
						s.cache[samplenum].map_pt = play_buff[samplenum].in;

						if ((s.cache[samplenum].high - s.cache[samplenum].low) > s.cache[samplenum].size)
							s.cache[samplenum].high = s.cache[samplenum].low + s.cache[samplenum].size;
					} else {

						s.cache[samplenum].high = s.sample_file_curpos[samplenum];

						if ((s.cache[samplenum].high - s.cache[samplenum].low) > s.cache[samplenum].size) {
							s.cache[samplenum].map_pt = play_buff[samplenum].in;
							s.cache[samplenum].low = s.cache[samplenum].high - s.cache[samplenum].size;
						}
					}

					if (err)
						g_error |= READ_BUFF1_OVERRUN;
				}
			}
		}

		// Check if we've prebuffered enough to start playing
		if ((s.is_buffered_to_file_end[samplenum] || s.play_buff_bufferedamt[samplenum] >= pre_buff_amt) &&
			params.play_state == PlayStates::PREBUFFERING)
		{
			flags.set(Flag::StartFadeUp);
			//  env_level = 0.f;
			if (params.length <= 0.5f)
				params.play_state = params.reverse ? PlayStates::PLAYING_PERC : PlayStates::PERC_FADEUP;
			else
				params.play_state = PlayStates::PLAY_FADEUP;
		}
	}

	void check_change_bank() {
		if (flags.take(Flag::PlayBankChanged)) {

			// Set flag that the sample has changed
			flags.set(Flag::PlaySampleChanged);

			// Changing bank updates the play button "not-playing" color (dim white or dim red)
			// But avoids the bright flash of white or red by setting PlaySampleXChanged_* = 1
			//

			if (samples[params.bank][params.sample].filename[0] == 0) {
				flags.clear(Flag::PlaySampleChangedValid);
				flags.set(Flag::PlaySampleChangedEmpty);
			} else {
				flags.set(Flag::PlaySampleChangedValid);
				flags.clear(Flag::PlaySampleChangedEmpty);
			}
		}
	}

	void check_change_sample(void) {
		if (!flags.take(Flag::PlaySampleChanged))
			return;

		if (s.cached_rev_state[params.sample] != params.reverse) {
			modes.reverse_file_positions(params.sample, params.bank, params.reverse);
			s.cached_rev_state[params.sample] = params.reverse;
		}

		// FixMe: Clean up this logic:
		// no file: fadedown or remain silent
		if (samples[params.bank][params.sample].filename[0] == 0) {
			// Avoid dimming it if we had already set the bright flag
			if (flags.read(Flag::PlaySampleChangedEmptyBright) == 0)
				flags.set(Flag::PlaySampleChangedEmpty);
			flags.clear(Flag::PlaySampleChangedValid);

			if (params.settings.auto_stop_on_sample_change == AutoStopMode::Always ||
				(params.settings.auto_stop_on_sample_change == AutoStopMode::Looping && params.looping))
			{
				if (params.play_state != PlayStates::SILENT && params.play_state != PlayStates::PREBUFFERING) {
					if (params.play_state == PlayStates::PLAYING_PERC)

						params.play_state = PlayStates::REV_PERC_FADEDOWN;
					else {
						params.play_state = PlayStates::PLAY_FADEDOWN;
						flags.set(Flag::StartFadeDown);
						// env_level = 1.f;
					}

				} else
					params.play_state = PlayStates::SILENT;
			}
			return;
		}

		// Sample found in this slot:

		// Avoid dimming it if we had already set the bright flag
		if (flags.read(Flag::PlaySampleChangedValidBright) == 0)
			flags.set(Flag::PlaySampleChangedValid);
		flags.clear(Flag::PlaySampleChangedEmpty);
		// pr_dbg("%.80s\n", samples[params.bank][params.sample].filename);

		if (params.settings.auto_stop_on_sample_change == AutoStopMode::Always) {
			if (params.play_state == PlayStates::SILENT && params.looping)
				flags.set(Flag::PlayBut);

			if (params.play_state != PlayStates::SILENT && params.play_state != PlayStates::PREBUFFERING) {
				if (params.play_state == PlayStates::PLAYING_PERC)
					params.play_state = PlayStates::REV_PERC_FADEDOWN;
				else {
					params.play_state = PlayStates::PLAY_FADEDOWN;
					flags.set(Flag::StartFadeDown);
					// env_level = 1.f;
				}
			}
		} else {
			if (params.looping) {
				if (params.play_state == PlayStates::SILENT)
					flags.set(Flag::PlayBut);

				else if (params.settings.auto_stop_on_sample_change == AutoStopMode::Looping) {
					if (params.play_state == PlayStates::PLAYING_PERC)
						params.play_state = PlayStates::REV_PERC_FADEDOWN;
					else {
						params.play_state = PlayStates::PLAY_FADEDOWN;
						flags.set(Flag::StartFadeDown);
						// env_level = 1.f;
					}
				}
			}
		}
	}
};
} // namespace SamplerKit
