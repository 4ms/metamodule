/*
 * wav_recording.hh - wav file recording routines
 *
 * Author: Dan Green (danngreen1@gmail.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * See http://creativecommons.org/licenses/MIT/ for more information.
 *
 * -----------------------------------------------------------------------------
 */

#pragma once

#include "circular_buffer.hh"
#include "drivers/stm32xx.h"
#include "ff.h"
#include "params.hh"
#include "wavefmt.hh"

namespace SamplerKit
{
#define WAV_COMMENT "Recorded on a 4ms Sampler" // goes into wav info chunk and id3 tag
#define WAV_SOFTWARE "4ms Sampler firmware v"	//	goes into wav info chunk and id3 tag

struct Recorder {
	Params &params;
	Flags &flags;
	Sdcard &sd;
	BankManager &banks;

	CircularBuffer rec_buff;

	uint32_t g_error = 0;

	static constexpr uint32_t WRITE_BLOCK_SIZE = 9216;
	int16_t rec_buff16[WRITE_BLOCK_SIZE >> 1];

	// WAV file specification limits sample data to 4GB = 0xFFFFFFFF Bytes
	static constexpr uint32_t MAX_REC_SAMPLES = (0xFFFFFFFF - Brain::MemorySizeBytes - (WRITE_BLOCK_SIZE * 2));

	RecStates &rec_state;
	bool recording_enabled;

	FIL recfil;
	uint32_t samplebytes_recorded;
	uint8_t sample_num_now_recording;
	uint8_t sample_num_to_record_in;
	uint8_t sample_bank_now_recording;
	uint8_t sample_bytesize_now_recording;
	char sample_fname_now_recording[FF_MAX_LFN];
	WaveHeaderAndChunk whac_now_recording; // whac = "Wave Header And Chunk"

	Recorder(Params &params, Flags &flags, Sdcard &sd, BankManager &banks)
		: params{params}
		, flags{flags}
		, sd{sd}
		, banks{banks}
		, rec_state{params.rec_state} {
		init_rec_buff();
	}

	void stop_recording();
	void toggle_recording();
	void record_audio_to_buffer(const AudioStreamConf::AudioInBlock &src);
	void write_buffer_to_storage();
	void init_rec_buff();
	void create_new_recording(uint8_t bitsPerSample, uint8_t numChannels, uint32_t sample_rate);
	FRESULT write_wav_info_chunk(FIL *wavfil, unsigned int *total_written);
	FRESULT write_wav_size(FIL *wavfil, uint32_t data_chunk_bytes, uint32_t file_size_bytes);
};
} // namespace SamplerKit
