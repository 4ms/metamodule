#include <cstdio>
#include <span>
#include <string_view>

// These classes assume float-32 wav format

class WavWriter {
	FILE *fp = nullptr;

public:
	WavWriter(std::string_view filename, size_t frames, uint16_t channels, uint32_t sample_rate) {
		fp = fopen(filename.data(), "wb");
		if (fp == nullptr) {
			printf("ERROR: WavWriter: file '%s' cannot be created\n", filename.data());
			return;
		}

		fwrite("RIFF", 4, 1, fp);

		uint32_t len = 44 - 8 + frames * channels * sizeof(float); // file length in bytes
		fwrite(&len, 4, 1, fp);

		fwrite("WAVEfmt ", 8, 1, fp);

		uint32_t bs = 0x12; // block size = 0x12 for float-32, 0x10 for PCM
		fwrite(&bs, 4, 1, fp);

		uint16_t fmt = 0x3; // format: 3: float-32, 1: PCM
		fwrite(&fmt, 2, 1, fp);

		uint16_t chan = channels;
		fwrite(&chan, 2, 1, fp);

		uint32_t freq = sample_rate;
		fwrite(&freq, 4, 1, fp);

		uint32_t bytes_per_sec = sample_rate * sizeof(float) * channels;
		fwrite(&bytes_per_sec, 4, 1, fp);

		uint16_t block_align = channels * sizeof(float);
		fwrite(&block_align, 2, 1, fp);

		uint16_t bits_per_sample = 8 * sizeof(float);
		fwrite(&bits_per_sample, 2, 1, fp);

		uint16_t extension_size = 0;
		fwrite(&extension_size, 2, 1, fp);

		fwrite("data", 4, 1, fp);
		uint32_t datasize = frames * sizeof(float) * channels;
		fwrite(&datasize, 4, 1, fp);
	}

	// output: interlaced samples
	template<typename T>
	void write(std::span<const T> output) {
		if (fp)
			fwrite(output.data(), sizeof(T), output.size(), fp);
	}
};

class WavReader {
	FILE *fp = nullptr;
	uint32_t size_{};
	uint16_t num_channels_{};
	uint32_t sample_rate_{};
	bool valid = false;

public:
	WavReader(std::string_view filename) {
		fp = fopen(filename.data(), "r");
		if (fp == nullptr) {
			printf("ERROR: WavReader: file '%s' not found\n", filename.data());
			return;
		}

		char data[] = "\0\0\0\0\0\0\0\0";

		if (!(fread(data, 1, 4, fp) == 4 && data[0] == 'R' && data[1] == 'I' && data[2] == 'F' && data[3] == 'F')) {
			printf("bad WAV format (RIFF)\n");
			close();
			return;
		}

		uint32_t len; // file size - 8 bytes
		fread(&len, 4, 1, fp);

		if (!(fread(data, 1, 8, fp) == 8 && data[0] == 'W' && data[1] == 'A' && data[2] == 'V' && data[3] == 'E' &&
			  data[4] == 'f' && data[5] == 'm' && data[6] == 't' && data[7] == ' '))
		{
			printf("bad WAV format (WAVEfmt)\n");
			close();
			return;
		}

		uint32_t bs; // size of header section
		fread(&bs, 4, 1, fp);
		if (bs != 0x12 && bs != 0x10) {
			printf("bad WAV format (bs)\n");
			close();
			return;
		}

		uint16_t fmt; // 1=PCM, 3=  float32
		fread(&fmt, 2, 1, fp);
		if (fmt != 0x1 && fmt != 0x3) {
			printf("bad WAV format (fmt)\n");
			close();
			return;
		}

		fread(&num_channels_, 2, 1, fp);
		fread(&sample_rate_, 4, 1, fp);

		uint32_t bytes_per_second;
		fread(&bytes_per_second, 4, 1, fp);

		uint16_t block_align;
		fread(&block_align, 2, 1, fp);

		if (bytes_per_second != sample_rate_ * block_align) {
			printf("bad WAV format (bpb)\n");
			close();
			return;
		}

		uint16_t bpsamples; // bits per samples
		fread(&bpsamples, 2, 1, fp);

		if (bs == 0x12) {
			uint16_t ext_size;
			fread(&ext_size, 2, 1, fp);
		}

		if (!(fread(data, 1, 4, fp) == 4 && data[0] == 'd' && data[1] == 'a' && data[2] == 't' && data[3] == 'a')) {
			printf("bad WAV format (data)\n");
			close();
			return;
		}

		uint32_t datasize;
		fread(&datasize, 4, 1, fp);
		size_ = datasize * 8 / num_channels_ / bpsamples;

		valid = true;
	}

	template<typename T>
	bool read(std::span<T> input) {
		if (fp) {
			auto br = fread(input.data(), sizeof(T), input.size(), fp);
			close();
			return br == input.size();
		} else
			return false;
	}

	void close() {
		fclose(fp);
		fp = nullptr;
	}

	bool is_valid() {
		return valid;
	}

	uint32_t size() {
		return size_;
	}

	int sample_rate() {
		return sample_rate_;
	}

	int num_channels() {
		return num_channels_;
	}
};
