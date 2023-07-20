#pragma once

#include "easiglib/dsp.hh"

static constexpr int sine_size = 512 + 1;
static constexpr int cheby_tables = 16;
static constexpr int cheby_size = 512 + 1;
static constexpr int fold_size = 1024 + 1;

struct DynamicData {
	DynamicData();
	static Buffer<std::pair<s1_15, s1_15>, sine_size> sine;
	static Buffer<Buffer<f, cheby_size>, cheby_tables> cheby;
	static Buffer<std::pair<f, f>, fold_size> fold;
	static Buffer<f, (fold_size - 1) / 2 + 1> fold_max;
	static Buffer<Buffer<f, 9>, 8> triangles;
};
