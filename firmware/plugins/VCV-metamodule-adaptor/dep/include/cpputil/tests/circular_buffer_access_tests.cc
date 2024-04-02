#include "doctest.h"
#include "util/circular_buffer_ext.hh"
#include <array>
#include <cstdint>

TEST_CASE("Writing") {
	std::array<int32_t, 16> buf;
	CircularBufferAccess a{buf};

	CHECK(a.size() == 16);

	buf[0] = 1;
	a.clear();
	CHECK(buf[0] == 0);

	std::array<int32_t, 10> newdata{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	CHECK(a.write(newdata) == false);
	CHECK(buf[0] == 1);
	CHECK(buf[1] == 2);
	CHECK(buf[9] == 10);
	CHECK(a.wr_pos() == 10);

	std::array<int32_t, 10> newdata2{11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
	CHECK(a.write(newdata2) == true);
	CHECK(buf[15] == 16);
	CHECK(buf[0] == 17);
	CHECK(buf[1] == 18);
	CHECK(buf[2] == 19);
	CHECK(buf[3] == 20);
	CHECK(buf[4] == 5);
	CHECK(a.wr_pos() == 4);

	{
		// [..s..X..e...] -> true
		size_t marker = 6;
		std::array<int32_t, 3> t;
		CHECK(a.write_check_crossed(t, marker) == true);
		CHECK(a.wr_pos() == 7);
	}
	{
		// [....X..s..e] -> false
		size_t marker = 6;
		std::array<int32_t, 3> t;
		CHECK(a.write_check_crossed(t, marker) == false);
		CHECK(a.wr_pos() == 10);
	}
	{
		// [.e...X..s..] -> false
		size_t marker = 6;
		std::array<int32_t, 9> t;
		CHECK(a.write_check_crossed(t, marker) == false);
		CHECK(a.wr_pos() == 3);
	}
	{
		// [.X..e..s.] -> true
		a.write(newdata);
		CHECK(a.wr_pos() == 13);
		size_t marker = 2;
		std::array<int32_t, 7> t;
		CHECK(a.write_check_crossed(t, marker) == true);
		CHECK(a.wr_pos() == 4);
	}
	{
		// [.s..e..X.] -> false
		size_t marker = 12;
		std::array<int32_t, 3> t;
		CHECK(a.write_check_crossed(t, marker) == false);
		CHECK(a.wr_pos() == 7);
	}
	{
		// [.e..s..X.] -> true
		// [ 4  7  12]
		CHECK(a.wr_pos() == 7);
		size_t marker = 12;
		std::array<int32_t, 13> t;
		CHECK(a.write_check_crossed(t, marker) == true);
		CHECK(a.wr_pos() == 4);
	}

	//TODO check what happens if marker is on start or end
	//TODO check what happens if we write the entire buffer (s==e)
}

TEST_CASE("Reading") {
	std::array<int32_t, 8> buf{1, 2, 3, 4, 5, 6, 7, 8};
	CircularBufferAccess a{buf};

	CHECK(a.size() == 8);

	std::array<int32_t, 8> read_back{};

	CHECK(a.read(read_back) == true);
	CHECK(read_back[0] == 1);
	CHECK(read_back[1] == 2);
	CHECK(read_back[7] == 8);
	CHECK(a.rd_pos() == 0);

	{
		// [s..X..e.] -> true
		size_t marker = 3;
		std::array<int32_t, 6> t;
		CHECK(a.read_check_crossed(t, marker) == true);
		CHECK(a.rd_pos() == 6);
	}

	// Ending a read on the marker does not count as "crossing" the marker
	// Because we don't actually read the marker element, (rd points to the next element
	// to be read).
	{
		// [...e/X..s.] -> true
		CHECK(a.rd_pos() == 6);
		size_t marker = 3;
		std::array<int32_t, 5> t;
		CHECK(a.read_check_crossed(t, marker) == false);
		CHECK(a.rd_pos() == 3);
	}

	// Starting a read on the marker counts as "crossing" the marker
	// Because we do actually read the marker element
	{
		// [...e/X..s.] -> true
		CHECK(a.rd_pos() == 3);
		size_t marker = 3;
		std::array<int32_t, 4> t;
		CHECK(a.read_check_crossed(t, marker) == true);
		CHECK(a.rd_pos() == 7);
	}
}

TEST_CASE("Spans and subspans") {
	// Create three circular buffers from one contigious array
	// One covers the entire backing data, and the other two
	// are halves. Make sure the halves don't interact.
	std::array<int32_t, 8> buf{1, 2, 3, 4, 5, 6, 7, 8};
	CircularBufferAccess big{buf};

	std::span<int32_t> bufspan1{&buf[0], &buf[4]};
	std::span<int32_t> bufspan2{&buf[4], &buf[8]};

	CircularBufferAccess a{bufspan1};
	CHECK(a.size() == 4);
	std::array<int32_t, 4> read1;
	CHECK(a.read(read1) == true);
	CHECK(read1[0] == 1);
	CHECK(read1[1] == 2);
	CHECK(read1[2] == 3);
	CHECK(read1[3] == 4);

	CircularBufferAccess b{bufspan2};
	CHECK(b.size() == 4);
	std::array<int32_t, 4> read2;
	CHECK(b.read(read2) == true);
	CHECK(read2[0] == 5);
	CHECK(read2[1] == 6);
	CHECK(read2[2] == 7);
	CHECK(read2[3] == 8);

	//Make sure buffers are separate by writing to both
	std::array<int32_t, 8> write1{9, 10, 11, 12, 13, 14, 15, 16};
	std::array<int32_t, 8> write2{29, 20, 21, 22, 23, 24, 25, 26};
	a.write(write1);
	b.write(write2);

	std::array<int32_t, 4> read3;
	CHECK(a.read(read3) == true);
	CHECK(read3[0] == 13);
	CHECK(read3[1] == 14);
	CHECK(read3[2] == 15);
	CHECK(read3[3] == 16);

	std::array<int32_t, 4> read4;
	CHECK(b.read(read4) == true);
	CHECK(read4[0] == 23);
	CHECK(read4[1] == 24);
	CHECK(read4[2] == 25);
	CHECK(read4[3] == 26);

	std::array<int32_t, 8> read_big;
	CHECK(big.read(read_big) == true);
	CHECK(read_big[0] == 13);
	CHECK(read_big[1] == 14);
	CHECK(read_big[2] == 15);
	CHECK(read_big[3] == 16);
	CHECK(read_big[4] == 23);
	CHECK(read_big[5] == 24);
	CHECK(read_big[6] == 25);
	CHECK(read_big[7] == 26);
}
