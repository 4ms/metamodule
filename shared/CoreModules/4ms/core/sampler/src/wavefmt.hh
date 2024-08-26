/*
 * wavefmt.h - wav file: header validation and creation
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
#include <cstdint>

namespace SamplerKit
{

#define ccWAVE 0x45564157
#define ccRIFF 0x46464952
#define ccFMT 0x20746D66
#define ccDATA 0x61746164
#define ccCUE 0x20657563

struct WaveHeader {
	// Riff Wave Header
	uint32_t RIFFId;
	uint32_t fileSize;
	uint32_t WAVEId;
};

struct WaveChunkHeader {
	uint32_t chunkId;
	uint32_t chunkSize;
};

struct WaveFmtChunk {
	// Format Subchunk: includes WaveChunkHeader
	uint32_t fmtId;
	uint32_t fmtSize;
	uint16_t audioFormat;
	uint16_t numChannels;
	uint32_t sampleRate;
	uint32_t byteRate;
	uint16_t blockAlign;
	uint16_t bitsPerSample;
};

struct WaveHeaderAndChunk {
	WaveHeader wh;
	WaveFmtChunk fc;
	WaveChunkHeader wc;
};

struct CueMarker {
	uint32_t index;
	uint32_t position;
	uint32_t data_slug;	  // always 'data' (use) or 'sint' (ignore)
	uint32_t chunk_start; // 00000000
	uint32_t block_start; // 00000000
	uint32_t sample_start;
};
static_assert(sizeof(CueMarker) == 24);

struct CueChunk {
	uint32_t num_cues;
};
static_assert(sizeof(CueChunk) == 4);

uint8_t is_valid_wav_header(WaveHeader sample_header);
uint8_t is_valid_format_chunk(WaveFmtChunk fmt_chunk);

void create_waveheader(
	WaveHeader *w, WaveFmtChunk *f, uint8_t bitsPerSample, uint8_t numChannels, uint32_t sample_rate);
void create_chunk(uint32_t chunkId, uint32_t chunkSize, WaveChunkHeader *wc);

} // namespace SamplerKit
