#include "doctest.h"
#include "util/fixed_vector.hh"

TEST_CASE("Constructor  inits back_idx variable") {
	FixedVector<int, 8> a{1, 3, 5};
	CHECK(a.size() == 3);
}

TEST_CASE("Basic usage: operator[] reads") {
	FixedVector<int, 4> a{1, 2, 3, 4};
	CHECK(a[0] == 1);
	CHECK(a[1] == 2);
	CHECK(a[2] == 3);
	CHECK(a[3] == 4);
}

TEST_CASE("Basic usage: operator[] writes") {
	FixedVector<int, 4> a{1, 2, 3, 4};
	a[0] = 5;
	CHECK(a[0] == 5);
	a[1] = 6;
	CHECK(a[1] == 6);
	a[2] = 7;
	CHECK(a[2] == 7);
	a[3] = 8;
	CHECK(a[3] == 8);

	SUBCASE("Can write to any element, even past size()") {
		FixedVector<int, 4> b;
		b[3] = 9;
		CHECK(b.size() == 0);
		CHECK(b[3] == 9);
	}
}

TEST_CASE("Two element construction makes two elements (not an element repeated N times)") {
	FixedVector<int, 7> a{4, 7};
	CHECK(a[1] == 7);
}

TEST_CASE("Push back creates elements in the right order") {

	FixedVector<unsigned, 5> a;
	CHECK(a.size() == 0);

	a.push_back(3);
	CHECK(a[0] == 3);
	CHECK(a.size() == 1);

	a.push_back(4);
	CHECK(a[1] == 4);
	CHECK(a.size() == 2);

	a.push_back(5);
	CHECK(a[2] == 5);
	CHECK(a.size() == 3);

	SUBCASE("Pop back does the opposite of push back") {
		auto x = a.pop_back();
		CHECK(x == 5);
		CHECK(a.size() == 2);

		x = a.pop_back();
		CHECK(x == 4);
		CHECK(a.size() == 1);

		x = a.pop_back();
		CHECK(x == 3);
		CHECK(a.size() == 0);

		SUBCASE("Popping an empty vector returns default-constructed type") {
			x = a.pop_back();
			CHECK(x == 0);

			x = a.pop_back();
			CHECK(x == 0);
		}
	}
}

TEST_CASE("Insert/erase") {

	constexpr auto vsize = 4;
	FixedVector<int, vsize> fv;

	// make sure size is 0 on init
	CHECK(fv.size() == 0);

	// try erasing
	fv.erase(0);
	fv.erase(10);
	CHECK(fv.size() == 0);

	constexpr auto A = 16;
	constexpr auto B = 31;
	constexpr auto C = 99;

	// Inserting at values > size() does nothing
	fv.insert(1, A);
	fv.insert(13, A);
	CHECK(fv.size() == 0);

	// Insert at 0
	fv.insert(0, A);
	CHECK(fv.size() == 1);
	CHECK(fv[0] == A);

	// Erase past end does nothing
	fv.erase(1);
	CHECK(fv.size() == 1);

	// Erase first element works
	fv.erase(0);
	CHECK(fv.size() == 0);

	// Insert and erase two elements
	fv.insert(0, A);
	fv.insert(1, B);
	CHECK(fv[0] == A);
	CHECK(fv[1] == B);
	CHECK(fv.size() == 2);
	fv.erase(0);
	fv.erase(0);
	CHECK(fv.size() == 0);

	// Insert an element at the start
	fv.insert(0, A);
	fv.insert(0, B);
	fv.insert(0, C);
	CHECK(fv[0] == C);
	CHECK(fv[1] == B);
	CHECK(fv[2] == A);

	// Erase at the end
	fv.erase(2);
	CHECK(fv[0] == C);
	CHECK(fv[1] == B);
	CHECK(fv.size() == 2);
	fv.erase(1);
	CHECK(fv[0] == C);
	CHECK(fv.size() == 1);
	fv.erase(0);
	CHECK(fv.size() == 0);

	// Erase in the middle
	fv.insert(0, A);
	fv.insert(1, B);
	fv.insert(2, C);
	CHECK(fv[0] == A);
	CHECK(fv[1] == B);
	CHECK(fv[2] == C);
	fv.erase(1);
	CHECK(fv[0] == A);
	CHECK(fv[1] == C);

	// Erase at the begining
	fv.erase(0);
	CHECK(fv[0] == C);

	// Erase too much
	fv.erase(0);
	fv.erase(0);
	fv.erase(0);
	CHECK(fv.size() == 0);
	fv.insert(fv.size(), A);
	CHECK(fv.size() == 1);
	CHECK(fv[0] == A);

	// try to overflow
	fv.insert(fv.size(), A);
	fv.insert(fv.size(), B);
	fv.insert(fv.size(), C);
	fv.insert(fv.size(), -1);
	fv.insert(fv.size(), -1);
	CHECK(fv.size() == 4);
}

//TODO: Test with custom types and count number of ctors/dtors in custom type
