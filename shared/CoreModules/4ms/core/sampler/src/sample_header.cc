#include "sample_header.hh"
#include "errors.hh"
#include "wavefmt.hh"
#include <cstdio>

#if TESTPROJECT
#define printf_ printf
#endif

namespace SamplerKit
{

static uint32_t read(FIL *file, void *data, uint32_t bytes_to_read, unsigned int *bytes_read) {
	FRESULT res = f_read(file, data, bytes_to_read, bytes_read);

	if (res != FR_OK) {
		f_close(file);
		return HEADER_READ_FAIL;
	}
	if (bytes_to_read < *bytes_read) {
		f_close(file);
		// printf_("Read %d bytes, requested %d\n", *bytes_read, bytes_to_read);
		return FILE_WAVEFORMATERR;
	}
	return 0;
}

//
// Load the sample header from the provided file
//
uint32_t load_sample_header(Sample *s_sample, FIL *sample_file) {
	WaveHeader sample_header;
	WaveFmtChunk fmt_chunk;
	UINT br;
	uint32_t rd;
	WaveChunkHeader chunk_hdr;
	uint32_t next_chunk_start;

	rd = sizeof(WaveHeader);
	if (auto err = read(sample_file, &sample_header, rd, &br); err)
		return err;

	if (!is_valid_wav_header(sample_header)) {
		f_close(sample_file);
		return FILE_WAVEFORMATERR;
	}

	// Look for a WaveFmtChunk (which starts off as a chunk)
	chunk_hdr.chunkId = 0;
	rd = sizeof(WaveChunkHeader);

	while (chunk_hdr.chunkId != ccFMT) {
		if (auto err = read(sample_file, &chunk_hdr, rd, &br); err) {
			// printf_("fmt chunk read err\n");
			return err;
		}

		// Fix an odd-sized chunk, it should always be even
		if (chunk_hdr.chunkSize & 0b1)
			chunk_hdr.chunkSize++;

		next_chunk_start = f_tell(sample_file) + chunk_hdr.chunkSize;
		// fast-forward to the next chunk
		if (chunk_hdr.chunkId != ccFMT)
			f_lseek(sample_file, next_chunk_start);
	}

	// Go back to beginning of chunk --probably could do this more elegantly by removing fmtID and fmtSize from
	// WaveFmtChunk and just reading the next bit of data
	f_lseek(sample_file, f_tell(sample_file) - sizeof(WaveChunkHeader));

	// Re-read the whole chunk (or at least the fields we need) since it's a WaveFmtChunk
	rd = sizeof(WaveFmtChunk);
	if (auto err = read(sample_file, &fmt_chunk, rd, &br); err)
		return err;

	if (!is_valid_format_chunk(fmt_chunk)) {
		// printf_("Invalid format chunk: %x %x %x\n", fmt_chunk.byteRate, fmt_chunk.audioFormat, fmt_chunk.sampleRate);
		f_close(sample_file);
		return FILE_WAVEFORMATERR;
	}

	// Populate Sample entry with info from fmt chunk
	s_sample->sampleByteSize = fmt_chunk.bitsPerSample >> 3;
	s_sample->sampleRate = fmt_chunk.sampleRate;
	s_sample->numChannels = fmt_chunk.numChannels;
	s_sample->blockAlign = fmt_chunk.numChannels * fmt_chunk.bitsPerSample >> 3;
	s_sample->PCM = (fmt_chunk.audioFormat == 0xFFFE) ? 3 : fmt_chunk.audioFormat;

	// Skip to the next chunk
	f_lseek(sample_file, next_chunk_start);

	// Look for the data and cue chunks
	chunk_hdr.chunkId = 0;
	rd = sizeof(WaveChunkHeader);

	// repeat until we found data and cue, or end of file
	bool found_data_chunk = false;
	bool found_cue_chunk = false;
	while (!found_data_chunk || !found_cue_chunk) {
		if (auto err = read(sample_file, &chunk_hdr, rd, &br); err)
			return err;

		next_chunk_start = f_tell(sample_file) + chunk_hdr.chunkSize;

		// Fix an odd-sized chunk, it should always be even
		if (chunk_hdr.chunkSize & 0b1) {
			// printf_("Invalid chunkSize (%d), adding 1\n", chunk_hdr.chunkSize);
			chunk_hdr.chunkSize++;
		}

		if (chunk_hdr.chunkId == ccDATA) {
			// check valid data chunk size
			if (chunk_hdr.chunkSize == 0) {
				f_close(sample_file);
				return FR_INT_ERR;
			}

			// Check the file is really as long as the data chunkSize says it is
			if (f_size(sample_file) < (f_tell(sample_file) + chunk_hdr.chunkSize)) {
				chunk_hdr.chunkSize = f_size(sample_file) - f_tell(sample_file);
			}

			s_sample->sampleSize = chunk_hdr.chunkSize;
			s_sample->startOfData = f_tell(sample_file);
			s_sample->file_status = FileStatus::Found;
			s_sample->inst_end = s_sample->sampleSize;
			s_sample->inst_size = s_sample->sampleSize;
			s_sample->inst_start = 0;
			s_sample->inst_gain = 1.0;

			found_data_chunk = true;

		} else if (chunk_hdr.chunkId == ccCUE) {
			// TODO: skip searching for cues if disabled in settings

			// Re-read the whole chunk (or at least the fields we need) since it's a WaveFmtChunk
			rd = chunk_hdr.chunkSize;
			if (rd == 0)
				continue;

			CueChunk cue_chunk;
			if (auto err = read(sample_file, &cue_chunk, sizeof(CueChunk), &br); err)
				continue; // ignore cue chunk in case of error

			s_sample->num_cues = cue_chunk.num_cues;

			unsigned s_i = 0;
			for (unsigned c_i = 0; c_i < cue_chunk.num_cues; c_i++) {
				CueMarker cue;
				if (auto err = read(sample_file, &cue, sizeof(CueMarker), &br); err)
					continue; // ignore cue chunk in case of error
				auto start = cue.sample_start;
				// printf_("\nCue %d @%d\n", c_i, start);
				// Use non-zero cues that are increasing
				// TODO: take all non-zero cues and then sort
				if (start > 0) {
					if (s_i == 0 || start > s_sample->cue[s_i - 1]) {
						s_sample->cue[s_i++] = start;
					}
					// else printf_("Skipped\n");
				}
			}
			// FIXME: Units is in sample (frame) number

			found_cue_chunk = true;
		}

		// stop if this is the last chunk
		if ((next_chunk_start + sizeof(WaveChunkHeader)) >= f_size(sample_file))
			break;

		// keeping scanning chunks
		f_lseek(sample_file, next_chunk_start);
	}

	if (!found_data_chunk)
		return FILE_WAVEFORMATERR;

	if (!found_cue_chunk) {
		s_sample->num_cues = 0;
		// TODO: Search for labels txt file and populate cues from it
	}

	return 0;
}

} // namespace SamplerKit
