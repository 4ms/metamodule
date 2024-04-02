#include "doctest.h"
#include "util/circular_stack.hh"

TEST_CASE("Basic usage") {
	CircularStack<int, 4> t;
	CHECK(t.size() == 0);

	t.push_back(2);
	CHECK(t.size() == 1);

	CHECK(t.pop_back() == 2);
	CHECK(t.size() == 0);

	t.push_back(3);
	CHECK(t.pop_back() == 3);

	t.push_back(4);
	CHECK(t.pop_back() == 4);

	t.push_back(5);
	CHECK(t.pop_back() == 5);

	t.push_back(6);
	CHECK(t.pop_back() == 6);
}

TEST_CASE("Pushing more elements than MaxElements overwrites from beginning") {
	CircularStack<int, 4> t;
	CHECK(t.size() == 0);

	t.push_back(7);
	CHECK(t.size() == 1);

	t.push_back(8);
	CHECK(t.size() == 2);

	t.push_back(9);
	CHECK(t.size() == 3);

	t.push_back(10);
	CHECK(t.size() == 4);

	//Size never exceeds MaxElements
	t.push_back(11);
	CHECK(t.size() == 4);

	CHECK(t.pop_back() == 11);
	CHECK(t.size() == 3);

	CHECK(t.pop_back() == 10);
	CHECK(t.size() == 2);

	CHECK(t.pop_back() == 9);
	CHECK(t.size() == 1);

	CHECK(t.pop_back() == 8);
	CHECK(t.size() == 0);
}

TEST_CASE("Popping an empty stack returns nullopt") {
	CircularStack<int, 4> t;
	CHECK(t.pop_back() == std::nullopt);
	CHECK(t.size() == 0);

	t.push_back(1);
	CHECK(t.size() == 1);

	CHECK(t.pop_back() == 1);
	CHECK(t.size() == 0);
	CHECK(t.pop_back() == std::nullopt);
	CHECK(t.pop_back() == std::nullopt);

	t.push_back(2);
	CHECK(t.size() == 1);
	CHECK(t.pop_back() == 2);
	CHECK(t.size() == 0);
	CHECK(t.pop_back() == std::nullopt);

	//Check it still works after overwriting
	t.push_back(22);
	t.push_back(23);
	t.push_back(24);
	t.push_back(25);
	t.push_back(26);
	t.push_back(27);

	CHECK(t.pop_back() != std::nullopt);
	CHECK(t.pop_back() != std::nullopt);
	CHECK(t.pop_back() != std::nullopt);
	CHECK(t.pop_back() != std::nullopt);
	CHECK(t.pop_back() == std::nullopt);

	t.push_back(32);
	t.push_back(33);
	t.push_back(34);
	t.push_back(35);
	CHECK(t.pop_back() == 35);
	CHECK(t.pop_back() == 34);
	CHECK(t.pop_back() == 33);
	CHECK(t.pop_back() == 32);
}

// TEST_CASE("Clearing does its job") {
// 	CircularStack<int, 4> t;
// 	t.push_back(2);
// 	t.push_back(3);
// }
