#pragma once

#include "easiglib/buffer.hh"
#include "easiglib/numtypes.hh"

struct Data {
	static const Buffer<s1_15, 257> sine;
	static const Buffer<uint32_t, 1024> exp2_u0_23;
	static const Buffer<f, 17> normalization_factors;
	static const Buffer<Buffer<f, 257>, 12> cheby;
	static const Buffer<f, 1025> fold;
	static const Buffer<Buffer<f, 9>, 8> triangles;
	static const Buffer<f, 16> harm;
};
