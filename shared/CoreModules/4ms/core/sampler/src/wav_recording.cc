/*
 * wav_recording.c - wav file recording routines
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

#include "wav_recording.hh"
#include "bank.hh"
#include "brain_conf.hh"
#include "circular_buffer.hh"
#include "elements.hh"
#include "errors.hh"
#include "params.hh"
#include "sample_file.hh"
#include "sts_filesystem.hh"
#include "wavefmt.hh"
#include <array>

namespace SamplerKit
{

void Recorder::init_rec_buff(void) {
	rec_buff.in = Brain::MemoryStartAddr;
	rec_buff.out = Brain::MemoryStartAddr;
	rec_buff.min = Brain::MemoryStartAddr;
	rec_buff.max = Brain::MemoryEndAddr;
	rec_buff.size = Brain::MemorySizeBytes; // TODO: bytes or samples?
	rec_buff.wrapping = 0;

	sample_num_to_record_in = params.sample;
}

void Recorder::stop_recording() {
	using enum RecStates;
	if (rec_state == RECORDING || rec_state == CREATING_FILE) {
		rec_state = CLOSING_FILE;
	}
}

void Recorder::toggle_recording(void) {
	using enum RecStates;
	if (rec_state == RECORDING || rec_state == CREATING_FILE) {
		rec_state = CLOSING_FILE;
		printf_("Stopping...\n");
	} else {
		init_rec_buff();
		rec_state = CREATING_FILE;
		printf_("Recording...\n");
	}
}

// Main routine that handles recording codec input stream (src)
// to the SDRAM buffer (rec_buff)
//
void Recorder::record_audio_to_buffer(const AudioStreamConf::AudioInBlock &src) {
	using enum RecStates;
	if (rec_state == RECORDING || rec_state == CREATING_FILE) {
		// WATCH_REC_BUFF = CB_distance(rec_buff, 0);
		// if (WATCH_REC_BUFF == 0)
		// 	{DEBUG0_ON;DEBUG0_OFF;}

		uint32_t overrun = 0;

		// Copy a buffer's worth of samples from codec (src) into rec_buff
		for (auto [i, in] : enumerate(src)) {
			for (unsigned chan = 0; chan < 2; chan++) {

				// 1 - chan: Fix for hardware having L/R channels reversed on the inputs
				auto sample = in.chan[1 - chan];

				int32_t scaled = in.sign_extend(sample);
				scaled *= Brain::AudioGain * 0.90f;
				scaled = __SSAT(scaled, 24);

				if (params.settings.rec_24bits) {
					uint8_t bottombyte = scaled & 0x0000FF;
					uint8_t midbyte = (scaled & 0x00FF00) >> 8;
					uint8_t topbyte = (scaled & 0xFF0000) >> 16;

					*(uint8_t *)rec_buff.in = bottombyte;
					rec_buff.offset_in_address(1, 0);
					rec_buff.wait_memory_ready();

					*(uint8_t *)rec_buff.in = midbyte;
					rec_buff.offset_in_address(1, 0);
					rec_buff.wait_memory_ready();

					*(uint8_t *)rec_buff.in = topbyte;
					rec_buff.offset_in_address(1, 0);
					rec_buff.wait_memory_ready();

				} else {
					*(int16_t *)rec_buff.in = scaled >> 8;
					rec_buff.offset_in_address(2, 0);
					rec_buff.wait_memory_ready();
				}
			}

			// Flag a buffer overrun condition if the in and out pointers cross
			// But, don't consider the heads being crossed if they end at the same place
			if ((rec_buff.in == rec_buff.out) && i != (AudioStreamConf::BlockSize - 1))
				overrun = rec_buff.out;
		}

		if (overrun) {
			g_error |= WRITE_BUFF_OVERRUN;
			check_errors(g_error);
		}
	}
}

// Creates a new file and writes a wave header and header chunk to it
// If it succeeds, it sets the recording state to RECORDING
// Otherwise, it sets a g_error and returns
//
void Recorder::create_new_recording(uint8_t bitsPerSample, uint8_t numChannels, uint32_t sample_rate) {
	using enum RecStates;

	uint32_t sz;
	unsigned int written;

	DIR dir;
	// Make a file with a temp name (tmp-XXXXX.wav), inside the temp dir
	FRESULT res = create_dir(sd, &dir, "_tmp");

	// If we just can't open or create the tmp dir, just put it in the root dir
	if (res != FR_OK)
		str_cpy(sample_fname_now_recording, "tmp-");
	else
		str_cat(sample_fname_now_recording, "_tmp/", "tmp-");

	sz = str_len(sample_fname_now_recording);
	sz += intToStr(HAL_GetTick(), &(sample_fname_now_recording[sz]), 0);

	sample_fname_now_recording[sz++] = '.';
	sample_fname_now_recording[sz++] = 'w';
	sample_fname_now_recording[sz++] = 'a';
	sample_fname_now_recording[sz++] = 'v';
	sample_fname_now_recording[sz++] = 0;

	create_waveheader(&whac_now_recording.wh, &whac_now_recording.fc, bitsPerSample, numChannels, sample_rate);
	create_chunk(ccDATA, 0, &whac_now_recording.wc);

	sz = sizeof(WaveHeaderAndChunk);

	// Try to create the tmp file and write to it, reloading the sd card if needed
	g_error = 0;

	res = f_open(&recfil, sample_fname_now_recording, FA_WRITE | FA_CREATE_NEW | FA_READ);
	if (res == FR_OK)
		res = f_write(&recfil, &whac_now_recording.wh, sz, &written);

	if (res != FR_OK) {
		f_close(&recfil);
		res = sd.reload_disk() ? FR_OK : FR_DISK_ERR;
		if (res == FR_OK) {
			res = f_open(&recfil, sample_fname_now_recording, FA_WRITE | FA_CREATE_NEW);
			f_sync(&recfil);
			res = f_write(&recfil, &whac_now_recording.wh, sz, &written);
			f_sync(&recfil);
		} else {
			f_close(&recfil);
			rec_state = REC_OFF;
			g_error |= FILE_REC_OPEN_FAIL;
			check_errors(g_error);
			return;
		}
	}

	if (sz != written) {
		f_close(&recfil);
		rec_state = REC_OFF;
		g_error |= FILE_UNEXPECTEDEOF_WRITE;
		check_errors(g_error);
		return;
	}

	samplebytes_recorded = 0;

	rec_state = RECORDING;
}

// Writes the data chunk size and the file fize into the given wave file
// The former is written into the RIFF chunk, and the latter is written
// to the 'data' chunk.
//
FRESULT Recorder::write_wav_size(FIL *wavfil, uint32_t data_chunk_bytes, uint32_t file_size_bytes) {
	uint32_t orig_pos;
	unsigned int written;
	FRESULT res;

	// cache the original file position
	orig_pos = f_tell(wavfil);

	// RIFF file size
	whac_now_recording.wh.fileSize = file_size_bytes;

	// data chunk size
	whac_now_recording.wc.chunkSize = data_chunk_bytes;

	res = f_lseek(wavfil, 0);
	if (res == FR_OK) {
		res = f_write(wavfil, &whac_now_recording, sizeof(WaveHeaderAndChunk), &written);
	}

	if (res != FR_OK) {
		g_error |= FILE_WRITE_FAIL;
		check_errors(g_error);
		return res;
	}
	if (written != sizeof(WaveHeaderAndChunk)) {
		g_error |= FILE_UNEXPECTEDEOF_WRITE;
		check_errors(g_error);
		return (FR_INT_ERR);
	}

	// restore the original file position
	res = f_lseek(wavfil, orig_pos);
	return (res);
}

// Writes comments into the INFO chunk of the given wav file
// ToDo: This only works for firmware versions 0.0 to 9.9
// ToDo: firmware tag limited to FF_MAX_LFN char
// The firmware version and comment string are set in wav_recording.h
// and globals.h
//
FRESULT Recorder::write_wav_info_chunk(FIL *wavfil, unsigned int *total_written) {
	unsigned int written;
	FRESULT res;
	uint8_t chunkttl_len = 4;
	uint32_t num32;
	char firmware[FF_MAX_LFN + 1];
	char temp_a[FF_MAX_LFN + 1];
	uint8_t pad_zeros[4] = {0, 0, 0, 0};

	// format firmware version string with version info
	intToStr(FirmwareMajorVersion, temp_a, 1);
	str_cat(firmware, WAV_SOFTWARE, temp_a);
	str_cat(firmware, firmware, ".");
	intToStr(FirmwareMinorVersion, temp_a, 1);
	str_cat(firmware, firmware, temp_a);

	struct Chunk {
		uint32_t len = 0;
		uint32_t padlen = 0;
	};

	struct Chunk list_ck, comment_ck, firmware_ck;

	// COMPUTE CHUNK LENGTHS
	// wav comment
	comment_ck.len = str_len(WAV_COMMENT);
	if (comment_ck.len % 4)
		comment_ck.padlen = 4 - (comment_ck.len % 4);

	// firmware version
	firmware_ck.len = str_len(firmware);
	if ((firmware_ck.len) % 4)
		firmware_ck.padlen = 4 - (firmware_ck.len % 4);

	// list chunk header
	list_ck.len =
		comment_ck.len + comment_ck.padlen + firmware_ck.len + firmware_ck.padlen + 3 * chunkttl_len + 2 * chunkttl_len;
	// 3x: INFO ICMT ISFT  2x: lenght entry, after title

	*total_written = 0;

	// WRITE DATA TO WAV FILE
	res = f_write(wavfil, "LIST", chunkttl_len, &written);
	if (res != FR_OK)
		return (res);
	if (written != chunkttl_len)
		return (FR_INT_ERR);
	*total_written += written;

	res = f_write(wavfil, &list_ck.len, chunkttl_len, &written);
	if (res != FR_OK)
		return (res);
	if (written != chunkttl_len)
		return (FR_INT_ERR);
	*total_written += written;

	res = f_write(wavfil, "INFOICMT", chunkttl_len * 2, &written);
	if (res != FR_OK)
		return (res);
	if (written != chunkttl_len * 2)
		return (FR_INT_ERR);
	*total_written += written;

	num32 = comment_ck.len + comment_ck.padlen;
	res = f_write(wavfil, &num32, sizeof(num32), &written);
	if (res != FR_OK)
		return (res);
	if (written != sizeof(num32))
		return (FR_INT_ERR);
	*total_written += written;

	res = f_write(wavfil, WAV_COMMENT, comment_ck.len, &written);
	if (res != FR_OK)
		return (res);
	if (written != comment_ck.len)
		return (FR_INT_ERR);
	*total_written += written;

	res = f_write(wavfil, &pad_zeros, comment_ck.padlen, &written);
	if (res != FR_OK)
		return (res);
	if (written != comment_ck.padlen)
		return (FR_INT_ERR);
	*total_written += written;

	res = f_write(wavfil, "ISFT", chunkttl_len, &written);
	if (res != FR_OK)
		return (res);
	if (written != chunkttl_len)
		return (FR_INT_ERR);
	*total_written += written;

	num32 = firmware_ck.len + firmware_ck.padlen;
	res = f_write(wavfil, &num32, sizeof(num32), &written);
	if (res != FR_OK)
		return (res);
	if (written != sizeof(num32))
		return (FR_INT_ERR);
	*total_written += written;

	res = f_write(wavfil, &firmware, firmware_ck.len, &written);
	if (res != FR_OK)
		return (res);
	if (written != firmware_ck.len)
		return (FR_INT_ERR);
	*total_written += written;

	res = f_write(wavfil, &pad_zeros, firmware_ck.padlen, &written);
	if (res != FR_OK)
		return (res);
	if (written != firmware_ck.padlen)
		return (FR_INT_ERR);
	*total_written += written;

	f_sync(wavfil);

	return (FR_OK);
}

// Main routine to handle the recording process from SDRAM to SD Card
//
// If we just requested to start recording, it handles creating the new file
// If we're recording, it writes a block of data from the SDRAM buffer onto the SD Card
// If we're done recording, it handles closing the file, adding tags, renaming it
// If we need to close the file because we reached the size limit, but need to
// continue recording, it handles all of that.
//
void Recorder::write_buffer_to_storage() {
	using enum RecStates;

	sample_num_to_record_in = params.sample;

	static uint32_t write_size_ctr = 0;

	check_errors(g_error);
	g_error = 0;

	// Handle write buffers (transfer SDRAM to SD card)
	switch (rec_state) {
		case CREATING_FILE: // first time, create a new file
			if (recfil.obj.fs != 0) {
				rec_state = CLOSING_FILE;
			}

			sample_num_now_recording = sample_num_to_record_in; // i_param[REC_CHAN][SAMPLE];
			sample_bank_now_recording = params.bank;

			if (params.settings.rec_24bits)
				sample_bytesize_now_recording = 3;
			else
				sample_bytesize_now_recording = 2;

			create_new_recording(8 * sample_bytesize_now_recording, 2, params.settings.record_sample_rate);
			printf_("File: %s\n", sample_fname_now_recording);

			break;

		case RECORDING: {
			// read a block from rec_buff.out

			// FixMe: Enable load triaging
			//  if (play_load_triage==0)
			uint32_t buffer_lead = rec_buff.distance(0);

			uint32_t num_underflowed = 0;
			if (buffer_lead > WRITE_BLOCK_SIZE) {
				if (sample_bytesize_now_recording == 3)
					num_underflowed = rec_buff.memory_read24((uint8_t *)rec_buff16, WRITE_BLOCK_SIZE / 3, 0);
				else
					num_underflowed = rec_buff.memory_read16(rec_buff16, WRITE_BLOCK_SIZE >> 1, 0);

				// WATCH_REC_BUFF_OUT = rec_buff.out;

				if (num_underflowed) {
					g_error |= WRITE_BUFF_OVERRUN;
					check_errors(g_error);
				}

				unsigned int written = 0;
				FRESULT res;
				res = f_write(&recfil, rec_buff16, WRITE_BLOCK_SIZE, &written);

				if (res != FR_OK) {
					if (g_error & FILE_WRITE_FAIL) {
						f_close(&recfil);
						rec_state = REC_OFF;
					}
					g_error |= FILE_WRITE_FAIL;
					check_errors(g_error);
					break;
				}
				if (WRITE_BLOCK_SIZE != written) {
					if (g_error & FILE_UNEXPECTEDEOF_WRITE) {
						f_close(&recfil);
						rec_state = REC_OFF;
					}
					g_error |= FILE_UNEXPECTEDEOF_WRITE;
					check_errors(g_error);
				}

				samplebytes_recorded += written;

				// Update the wav file size in the wav header
				if (write_size_ctr++ > 20) {
					write_size_ctr = 0;
					res = write_wav_size(
						&recfil, samplebytes_recorded, samplebytes_recorded + sizeof(WaveHeaderAndChunk) - 8);
					if (res != FR_OK) {
						f_close(&recfil);
						rec_state = REC_OFF;
						g_error |= FILE_WRITE_FAIL;
						check_errors(g_error);
						break;
					}
				}
				f_sync(&recfil);

				if (res != FR_OK) {
					if (g_error & FILE_WRITE_FAIL) {
						f_close(&recfil);
						rec_state = REC_OFF;
					}
					g_error |= FILE_WRITE_FAIL;
					check_errors(g_error);
					break;
				}

				// Stop recording in this file, if we are close the maximum
				// Then we will start recording again in a new file --there is a ~20ms gap between files
				//
				if (samplebytes_recorded >= MAX_REC_SAMPLES)
					rec_state = CLOSING_FILE_TO_REC_AGAIN;
			}

		} break;

		case CLOSING_FILE:
		case CLOSING_FILE_TO_REC_AGAIN: {
			// See if we have more in the buffer to write
			uint32_t buffer_lead = rec_buff.distance(0);

			if (buffer_lead) {
				// Write out remaining data in buffer, one WRITE_BLOCK_SIZE at a time
				if (buffer_lead > WRITE_BLOCK_SIZE)
					buffer_lead = WRITE_BLOCK_SIZE;

				uint32_t num_underflowed = 0;
				if (sample_bytesize_now_recording == 3)
					num_underflowed = rec_buff.memory_read24((uint8_t *)rec_buff16, buffer_lead / 3, 0);
				else
					num_underflowed = rec_buff.memory_read16(rec_buff16, buffer_lead >> 1, 0);

				// WATCH_REC_BUFF_OUT = rec_buff.out;

				if (num_underflowed) {
					g_error |= MATH_ERROR;
					check_errors(g_error);
				}

				unsigned int written = 0;
				FRESULT res;
				res = f_write(&recfil, rec_buff16, buffer_lead, &written);
				f_sync(&recfil);

				if (res != FR_OK) {
					if (g_error & FILE_WRITE_FAIL) {
						f_close(&recfil);
						rec_state = REC_OFF;
					}
					g_error |= FILE_WRITE_FAIL;
					check_errors(g_error);
					break;
				}
				if (written != buffer_lead) {
					if (g_error & FILE_UNEXPECTEDEOF_WRITE) {
						f_close(&recfil);
						rec_state = REC_OFF;
					}
					g_error |= FILE_UNEXPECTEDEOF_WRITE;
					check_errors(g_error);
				}

				samplebytes_recorded += written;

				// Update the wav file size in the wav header
				res = write_wav_size(
					&recfil, samplebytes_recorded, samplebytes_recorded + sizeof(WaveHeaderAndChunk) - 8);
				if (res != FR_OK) {
					f_close(&recfil);
					rec_state = REC_OFF;
					g_error |= FILE_WRITE_FAIL;
					check_errors(g_error);
					break;
				}

			} else {

				// Write comment and Firmware chunks at bottom of wav file
				unsigned int written = 0;
				FRESULT res;
				res = write_wav_info_chunk(&recfil, &written);
				if (res != FR_OK) {
					f_close(&recfil);
					rec_state = REC_OFF;
					g_error |= FILE_WRITE_FAIL;
					check_errors(g_error);
					break;
				}

				// Write new file size and data chunk size
				res = write_wav_size(
					&recfil, samplebytes_recorded, samplebytes_recorded + written + sizeof(WaveHeaderAndChunk) - 8);
				if (res != FR_OK) {
					f_close(&recfil);
					rec_state = REC_OFF;
					g_error |= FILE_WRITE_FAIL;
					check_errors(g_error);
					break;
				}

				f_close(&recfil);

				char final_filepath[FF_MAX_LFN];

				// Rename the tmp file as the proper file in the proper directory
				res = new_filename(sample_bank_now_recording,
								   sample_num_now_recording,
								   final_filepath,
								   sd,
								   banks.samples[sample_bank_now_recording]);
				if (res != FR_OK) {
					rec_state = REC_OFF;
					g_error |= SDCARD_CANT_MOUNT;
					check_errors(g_error);
					printf_("Could not make new filename, err=%d\n", res);
				} else {
					printf_("New filename: %.80s\n", final_filepath);
					res = f_rename(sample_fname_now_recording, final_filepath);
					if (res == FR_OK) {
						str_cpy(sample_fname_now_recording, final_filepath);
					} else
						printf_("Could not rename file %.80s. err %d\n", sample_fname_now_recording, res);
				}

				Sample *s = &banks.samples[sample_bank_now_recording][sample_num_now_recording];
				str_cpy(s->filename, sample_fname_now_recording);
				s->sampleSize = samplebytes_recorded;
				s->sampleByteSize = sample_bytesize_now_recording;
				s->sampleRate = params.settings.record_sample_rate;
				s->numChannels = 2;
				s->blockAlign = 2 * sample_bytesize_now_recording;
				s->startOfData = 44;
				s->PCM = 1;
				s->inst_start = 0;
				s->inst_end = samplebytes_recorded;
				s->inst_size = samplebytes_recorded;
				s->inst_gain = 1.0f;
				s->file_status = FileStatus::NewFile;

				banks.enable_bank(sample_bank_now_recording);

				// TODO: handle updating samples when switching to play mode
				// if (i_param[0][BANK] == sample_bank_now_recording) {
				// 	flags32[SampleFileChangedMask1] |= (1 << sample_num_now_recording);
				// 	if (i_param[0][SAMPLE] == sample_num_now_recording)
				// 		flags[PlaySampleChanged] = 1;
				// }

				sample_fname_now_recording[0] = 0;
				sample_num_now_recording = 0xFF;
				sample_bank_now_recording = 0xFF;

				if (params.settings.auto_inc_slot_num_after_rec_trig && flags.take(Flag::RecStartedWithTrigger)) {
					if (sample_num_to_record_in < 9)
						sample_num_to_record_in++;
					else
						sample_num_to_record_in = 0;
				}

				if (rec_state == CLOSING_FILE)
					rec_state = REC_OFF;

				else if (rec_state == CLOSING_FILE_TO_REC_AGAIN)
					rec_state = CREATING_FILE;
			}
		} break;

		case REC_OFF:
			break;
	}
}

} // namespace SamplerKit
