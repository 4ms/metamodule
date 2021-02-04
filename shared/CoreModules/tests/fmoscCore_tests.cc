#include "CoreModules/fmoscCore.h"
#include "doctest.h"
#include <iostream>
#include <stdint.h>

#include <chrono>

using namespace std::chrono;

TEST_CASE("timing test")
{
	/*
	FmoscCore fm;
	auto start = high_resolution_clock::now();
	fm.set_param(0, 0);
	for (int i = 0; i < 100000; i++) {
		fm.update();
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(stop - start);

	 std::cout << "nanoseconds to run " + std::to_string(duration.count() / 100000.0f) << std::endl;
	 */
}