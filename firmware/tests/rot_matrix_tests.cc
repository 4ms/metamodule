#include "doctest.h"
#include <cstdio>

template<size_t W, size_t H>
static void transpose(uint16_t *a, uint16_t *b) {
	for (unsigned x = 0; x < W; x++) {
		for (unsigned y = 0; y < H; y++) {
			b[y * W + x] = a[x * H + y];
		}
	}
}

TEST_CASE("Rotate matrix") {
	// 4 arrays of 3 elements
	// 4 rows of 3 columns
	// std::array<std::array<uint16_t, 3>, 4> a;
	uint16_t a[4][3];
	uint16_t *aa = &(a[0][0]);

	a[0][0] = 0;
	a[0][1] = 1;
	a[0][2] = 2;
	a[1][0] = 3;
	a[1][1] = 4;
	a[1][2] = 5;
	a[2][0] = 6;
	a[2][1] = 7;
	a[2][2] = 8;
	a[3][0] = 9;
	a[3][1] = 10;
	a[3][2] = 11;

	// Data is in order major x, minor y
	CHECK(*(aa + 0) == 0);
	CHECK(*(aa + 1) == 1);
	CHECK(*(aa + 2) == 2);
	CHECK(*(aa + 3) == 3);
	CHECK(*(aa + 4) == 4);
	CHECK(*(aa + 5) == 5);
	CHECK(*(aa + 6) == 6);
	CHECK(*(aa + 7) == 7);
	CHECK(*(aa + 8) == 8);
	CHECK(*(aa + 9) == 9);
	CHECK(*(aa + 10) == 10);
	CHECK(*(aa + 11) == 11);

	// output
	// std::array<std::array<uint16_t, 4>, 3> b;
	uint16_t b[3][4];
	uint16_t *bb = &(b[0][0]);

	b[0][0] = 0xFFFF;
	b[0][1] = 0xFFFF;
	b[0][2] = 0xFFFF;
	b[0][3] = 0xFFFF;
	b[1][0] = 0xFFFF;
	b[1][1] = 0xFFFF;
	b[1][2] = 0xFFFF;
	b[1][3] = 0xFFFF;
	b[2][0] = 0xFFFF;
	b[2][1] = 0xFFFF;
	b[2][2] = 0xFFFF;
	b[2][3] = 0xFFFF;

	transpose<4, 3>(aa, bb);

	CHECK(a[0][0] == b[0][0]);
	CHECK(a[0][1] == b[1][0]);
	CHECK(a[0][2] == b[2][0]);
	CHECK(a[1][0] == b[0][1]);
	CHECK(a[1][1] == b[1][1]);
	CHECK(a[1][2] == b[2][1]);
	CHECK(a[2][0] == b[0][2]);
	CHECK(a[2][1] == b[1][2]);
	CHECK(a[2][2] == b[2][2]);
	CHECK(a[3][0] == b[0][3]);
	CHECK(a[3][1] == b[1][3]);
	CHECK(a[3][2] == b[2][3]);

	CHECK(b[0][0] == 0);
	CHECK(b[0][1] == 3);
	CHECK(b[0][2] == 6);
	CHECK(b[0][3] == 9);
	CHECK(b[1][0] == 1);
	CHECK(b[1][1] == 4);
	CHECK(b[1][2] == 7);
	CHECK(b[1][3] == 10);
	CHECK(b[2][0] == 2);
	CHECK(b[2][1] == 5);
	CHECK(b[2][2] == 8);
	CHECK(b[2][3] == 11);

	// Data is in order major y, minor x
	CHECK(*(bb + 0) == 0);
	CHECK(*(bb + 1) == 3);
	CHECK(*(bb + 2) == 6);
	CHECK(*(bb + 3) == 9);
	CHECK(*(bb + 4) == 1);
	CHECK(*(bb + 5) == 4);
	CHECK(*(bb + 6) == 7);
	CHECK(*(bb + 7) == 10);
	CHECK(*(bb + 8) == 2);
	CHECK(*(bb + 9) == 5);
	CHECK(*(bb + 10) == 8);
	CHECK(*(bb + 11) == 11);
}
