#include "doctest.h"
#include "util/circular_buffer.hh"

TEST_CASE("Basic usage: FIFO") {
	CircularBuffer<int, 4> a;
	CHECK(a.SIZE_MASK == 0b11);
	CHECK(a.max_size() == 4);

	a.put(1);
	a.put(2);
	a.put(3);
	a.put(4);
	CHECK(a.get() == 1);
	CHECK(a.get() == 2);
	CHECK(a.get() == 3);
	CHECK(a.get() == 4);
}

TEST_CASE("Basic usage: Overwrites if put() past end") {
	CircularBuffer<int, 4> a;

	a.put(1);
	a.put(2);
	a.put(3);
	a.put(4);
	a.put(5);

	//1 is dropped
	CHECK(a.get() == 2);
	CHECK(a.get() == 3);
	CHECK(a.get() == 4);
	CHECK(a.get() == 5);
}

TEST_CASE("Basic usage: Interleaving put/get is ok") {
	CircularBuffer<int, 4> a;

	a.put(1);
	a.put(2);
	CHECK(a.get() == 1);
	CHECK(a.get() == 2);
	a.put(3);
	CHECK(a.get() == 3);
	a.put(4);
	CHECK(a.get() == 4);
}

TEST_CASE("Basic usage: get() when empty returns default value (0)") {
	CircularBuffer<int, 4> a;
	CHECK(a.get() == 0);
	CHECK(a.get() == 0);
	CHECK(a.get() == 0);
	CHECK(a.get() == 0);

	a.put(1);
	CHECK(a.get() == 1);
	CHECK(a.get() == 0);
	CHECK(a.get() == 0);
	CHECK(a.get() == 0);
	CHECK(a.get() == 0);
}

TEST_CASE("Basic usage: size()") {
	CircularBuffer<int, 4> a;
	CHECK(a.count() == 0);
	a.put(1);
	CHECK(a.count() == 1);
	a.put(2);
	CHECK(a.count() == 2);
	a.put(3);
	CHECK(a.count() == 3);
	a.put(4);
	CHECK(a.count() == 4);
}

TEST_CASE("Basic usage: full/empty()") {
	CircularBuffer<int, 4> a;
	CHECK(a.empty());
	CHECK(!a.full());

	a.put(1);
	CHECK(!a.empty());
	CHECK(!a.full());

	a.put(2);
	a.put(3);
	a.put(4);
	CHECK(!a.empty());
	CHECK(a.full());

	a.put(5);
	CHECK(!a.empty());
	CHECK(a.full());

	a.get();
	CHECK(!a.empty());
	CHECK(!a.full());

	a.get();
	a.get();
	a.get();
	CHECK(a.empty());
	CHECK(!a.full());
}
TEST_CASE("Basic usage: reset") {
	CircularBuffer<int, 4> a;

	a.put(1);
	a.put(2);
	a.put(3);
	a.put(4);
	a.reset();
	CHECK(a.empty());
	CHECK(!a.full());
	CHECK(a.count() == 0);
}
