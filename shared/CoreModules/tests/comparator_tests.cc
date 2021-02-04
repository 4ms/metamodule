#include "doctest.h"
#include "processors/tools/windowComparator.h"
#include <iostream>
#include <stdint.h>

TEST_CASE("basic functionality")
{
	WindowComparator wc;
	wc.set_highThreshold(0.8f);
	wc.set_lowThreshhold(0.5f);
	wc.update(0.9f);
	CHECK(wc.get_output() == true);
	wc.update(0.3f);
	CHECK(wc.get_output() == false);
}

TEST_CASE("check initial state is false")
{
	WindowComparator wc;
	CHECK(wc.get_output() == false);
}