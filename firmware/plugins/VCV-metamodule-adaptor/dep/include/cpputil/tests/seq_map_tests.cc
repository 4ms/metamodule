#include "doctest.h"
#include "util/seq_map.hh"
#include "util/static_string.hh"
#include <cstdint>
#include <vector>

TEST_CASE("Basic usage with static_string") {
	StaticString<3> key1 = {"abc"};
	StaticString<3> key2 = {"def"};

	SeqMap<StaticString<3>, uint32_t, 16> map;

	map.insert(key1, 11);
	map.insert(key2, 22);

	CHECK(map.keys[0] == key1);
	CHECK(map.keys[1] == key2);

	auto *val1 = map.get(key1);
	auto *val2 = map.get(key2);

	CHECK(*val1 == 11);
	CHECK(*val2 == 22);
}

TEST_CASE("Basic usage with complex type") {

	SeqMap<StaticString<3>, std::vector<int>, 16> map;
	// rvalue
	map.insert("abc", {1, 2, 3});

	// lvalue
	std::vector<int> b{4, 5, 6, 7, 8, 9};
	map.insert("def", b);
}

TEST_CASE("Can use empty keys") {
	StaticString<3> key1{"abc"};
	StaticString<3> key2{};

	SeqMap<StaticString<3>, uint32_t, 16> map;

	map.insert(key1, 11);
	map.insert(key2, 22);

	CHECK(map.keys[1] == key2);

	auto *val2 = map.get(key2);

	CHECK(*val2 == 22);
}

TEST_CASE("Does not match empty key unless an entry with empty key was added") {
	SeqMap<StaticString<3>, uint32_t, 16> map;

	// Empty map: get() does not return an element given an empty key
	CHECK(map.size() == 0);
	auto *empty = map.get({});
	CHECK(empty == nullptr);

	map.insert("abc", 11);
	map.insert("def", 22);

	// Non-empty map: get with all non-empty keys does not return an element
	CHECK(map.get({}) == nullptr);

	// element with an empty key can be found
	map.insert({}, 33);
	CHECK(*map.get({}) == 33);
}

TEST_CASE("overwriting") {
	SeqMap<StaticString<3>, uint32_t, 4> map;

	map.overwrite("a", 1);
	map.overwrite("b", 2);
	map.overwrite("c", 3);
	map.overwrite("d", 4);
	CHECK(map.size() == 4);
	CHECK(*map.get("a") == 1);
	CHECK(*map.get("b") == 2);
	CHECK(*map.get("c") == 3);
	CHECK(*map.get("d") == 4);

	auto e = map.overwrite("e", 5);
	CHECK(map.get("a") == nullptr);
	CHECK(*map.get("e") == 5);
	CHECK(e == map.get("e"));

	// Overwrite replaces values
	auto b = map.overwrite("b", 6);
	CHECK(*b == 6);
	CHECK(b == map.get("b"));

	// inseting a full map returns false
	bool ok = map.insert("f", 7);
	CHECK(ok == false);
	CHECK(map.get("f") == nullptr);
}

TEST_CASE("inserting and overwriting") {
	SeqMap<StaticString<3>, uint32_t, 4> map;

	map.insert("a", 1);
	map.insert("b", 2);
	map.overwrite("c", 3);
	map.overwrite("d", 4);
	CHECK(map.size() == 4);
	CHECK(*map.get("a") == 1);
	CHECK(*map.get("b") == 2);
	CHECK(*map.get("c") == 3);
	CHECK(*map.get("d") == 4);

	// inserting in a full map fails
	CHECK(map.insert("b", 22) == false);
	CHECK(*map.get("b") == 2);

	// overwriting in a full map works, but inserting has no effect
	CHECK(*map.overwrite("b", 22) == 22);
	CHECK(map.insert("b", 22) == false);
	map.overwrite("c", 33);
	CHECK(map.insert("b", 22) == false);
	map.overwrite("d", 44);
	CHECK(map.insert("b", 22) == false);
	map.overwrite("e", 55);
	CHECK(map.insert("b", 22) == false);
	CHECK(map.size() == 4);
	CHECK(*map.get("b") == 22);
	CHECK(*map.get("c") == 33);
	CHECK(*map.get("d") == 44);
	CHECK(*map.get("e") == 55);
}

TEST_CASE("Check if Key exists") {
	SeqMap<StaticString<31>, uint32_t, 4> map;
	StaticString<31> test = "ABC";
	CHECK_FALSE(map.key_exists(test));

	CHECK(map.insert("ABC", 9999));
	CHECK(map.key_exists(test));

	CHECK(map.insert("DDD", 10000));
	CHECK(map.insert("EEE", 10001));
	CHECK(map.insert("FFF", 10002));
	CHECK_FALSE(map.insert("GGG", 10003));

	CHECK(map.key_exists(test));

	CHECK(*map.get("DDD") == 10000);
	map.overwrite("DDD", 123);
	CHECK(*map.get("DDD") == 123);

	// Overwrite should not overwrite non-matching keys unless full
	CHECK(map.key_exists(test));

	// Overwrite will remove oldest key if full
	auto hhh = map.overwrite("HHH", 888);
	CHECK_FALSE(map.key_exists(test));
	CHECK(*hhh == 888);
}
