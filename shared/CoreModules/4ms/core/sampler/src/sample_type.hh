#pragma once
#include <cstdint>

enum class FileStatus : uint8_t { NotFound = 0, Found = 1, NewFile = 2 };

struct Sample {
	char filename[255];
	uint32_t sampleSize;
	uint32_t startOfData;
	uint8_t sampleByteSize;
	uint32_t sampleRate;
	uint8_t numChannels;
	uint8_t blockAlign;

	uint32_t inst_start;
	uint32_t inst_end;
	uint32_t inst_size;
	float inst_gain;

	uint16_t PCM;
	FileStatus file_status;

	uint8_t num_cues;
	uint32_t cue[4];

	Sample() { clear(); }
	void clear() {
		filename[0] = 0;
		sampleSize = 0;
		sampleByteSize = 0;
		sampleRate = 0;
		numChannels = 0;
		blockAlign = 0;
		startOfData = 0;
		PCM = 0;
		file_status = FileStatus::NotFound;
		inst_start = 0;
		inst_end = 0;
		inst_size = 0;
		inst_gain = 1.0;
		num_cues = 0;
	}
};
