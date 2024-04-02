#pragma once
#include <vector>

struct ByteBlock {
	using DataType = std::vector<unsigned char>;
	DataType data;

	ByteBlock() {
		data.clear();
	}

	void print(uint8_t x) {
		printU8(x);
	}
	void print(uint16_t x) {
		printU16LE(x);
	}
	void print(uint32_t x) {
		printU32LE(x);
	}

	void printU8(uint8_t x) {
		data.push_back((x >> 0) & 0xFF);
	}
	void printU16LE(uint16_t x) {
		data.push_back((x >> 0) & 0xFF);
		data.push_back((x >> 8) & 0xFF);
	}
	void printU32LE(uint32_t x) {
		data.push_back((x >> 0) & 0xFF);
		data.push_back((x >> 8) & 0xFF);
		data.push_back((x >> 16) & 0xFF);
		data.push_back((x >> 24) & 0xFF);
	}

	void printRaw(unsigned char *x, size_t size) {
		while (size--)
			data.push_back(*x++);
	}
};
