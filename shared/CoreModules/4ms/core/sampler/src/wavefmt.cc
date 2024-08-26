/*
 * wavefmt.c - wav file: header validation and creation
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

#include "wavefmt.hh"

namespace SamplerKit
{

uint8_t is_valid_wav_header(WaveHeader sample_header) {
	if (sample_header.RIFFId != ccRIFF) //"RIFF"
		return 0;
	else if (sample_header.fileSize < 16)
		return 0;
	else if (sample_header.WAVEId != ccWAVE) //"WAVE"
		return 0;
	else
		return 1;
}

uint8_t is_valid_format_chunk(WaveFmtChunk fmt_chunk) {
	if (fmt_chunk.fmtId == ccFMT   //'fmt '
		&& fmt_chunk.fmtSize >= 16 // Format Chunk size is valid

		&& ((fmt_chunk.audioFormat == 0x0001 // PCM format and 16/24-bit
			 && (fmt_chunk.bitsPerSample == 16 || fmt_chunk.bitsPerSample == 8 || fmt_chunk.bitsPerSample == 24 ||
				 fmt_chunk.bitsPerSample == 32)) ||
			(fmt_chunk.audioFormat == 0x0003 // Float format and 32-bit
			 && fmt_chunk.bitsPerSample == 32) ||
			(fmt_chunk.audioFormat == 0xFFFE // Extended format (float) format and 32-bit
			 && fmt_chunk.bitsPerSample == 32) ||
			(fmt_chunk.audioFormat == 0xFFFE // Exteneded format and 16-bit
			 && fmt_chunk.bitsPerSample == 16) ||
			(fmt_chunk.audioFormat == 0xFFFE // Exteneded format and 24-bit
			 && fmt_chunk.bitsPerSample == 24))

		&& (fmt_chunk.numChannels == 0x0002 || fmt_chunk.numChannels == 0x0001)

		&& fmt_chunk.sampleRate <= 96000 // Between 8k and 96k sampling rate allowed
		&& fmt_chunk.sampleRate >= 8000

	)
		return (1);
	else
		return (0);
}

void create_waveheader(
	WaveHeader *w, WaveFmtChunk *f, uint8_t bitsPerSample, uint8_t numChannels, uint32_t sample_rate) {
	if (bitsPerSample != 8 && bitsPerSample != 16 && bitsPerSample != 24 && bitsPerSample != 32)
		bitsPerSample = 16;

	if (numChannels != 1 && numChannels != 2)
		numChannels = 2;

	w->RIFFId = ccRIFF;
	w->fileSize = sizeof(WaveHeaderAndChunk) - 8; // size of file, minus 8 for 'RIFFsize'
	w->WAVEId = ccWAVE;

	f->fmtId = ccFMT;
	f->fmtSize = 16;
	f->audioFormat = 1;
	f->numChannels = numChannels;
	f->sampleRate = sample_rate;
	f->byteRate = (sample_rate * numChannels * (bitsPerSample / 8)); // sampleRate * blockAlign
	f->blockAlign = numChannels * (bitsPerSample / 8);
	f->bitsPerSample = bitsPerSample;
}

void create_chunk(uint32_t chunkId, uint32_t chunkSize, WaveChunkHeader *wc) {
	wc->chunkId = chunkId;
	wc->chunkSize = chunkSize;
}
} // namespace SamplerKit
