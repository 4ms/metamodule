#include "CoreModules/bitcrushCore.h"
#include "doctest.h"
#include "processors/tools/quantizeBits.h"
#include <stdint.h>

TEST_CASE("pass through with sample rate and bit rate at max")
{
	BitcrushCore b;
	b.set_samplerate(48000.0f);
	b.set_param(0, 1.0f);
	b.set_param(1, 1.0f);
	for (int i = 0; i < 10; i++) {
		float rand = randomNumber(0.0f, 1.0f);
		b.set_input(0, rand);
		b.update();

		CHECK(rand == b.get_output(0));
	}
}

TEST_CASE("test that bit reduction calculates properly")
{
	BitQuantizer q;
	q.setSteps(4);
	q.setMin(-1);
	q.setMax(1);
	CHECK(q.update(1) == 1.0);
	CHECK(q.update(-1) == -1);
	CHECK(q.update(0.3) == doctest::Approx(0.33333f));
	CHECK(q.update(-0.5f) == doctest::Approx(-0.33333f));
}