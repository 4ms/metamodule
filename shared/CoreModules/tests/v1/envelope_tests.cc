#include "doctest.h"
#include "processors/envelope.h"
#include <iostream>
#include <stdint.h>

TEST_CASE("sustain test")
{
	Envelope e;
	float testValue = 0.717f;
	e.set_sustain(testValue);
	e.set_samplerate(48000);
	e.set_envelope_time(0, 1);
	e.set_envelope_time(1, 0);
	e.set_envelope_time(2, 1);
	e.update(1.0f);
	int samplesUntilSustain = 2.0f * 48.0f;
	for (int i = 0; i < samplesUntilSustain; i++) {
		e.update(1.0f);
	}
	CHECK(e.update(1) == doctest::Approx(testValue));
}

TEST_CASE("end of envelope test")
{
	Envelope e;
	e.set_sustain(0.5f);
	e.set_samplerate(48000);
	e.set_envelope_time(0, 1);
	e.set_envelope_time(1, 0);
	e.set_envelope_time(2, 1);
	e.update(1.0f); // gate high
	int samplesUntilSustain = 2.0f * 48.0f;
	for (int i = 0; i < samplesUntilSustain; i++) {
		e.update(1.0f);
	}
	e.update(0); // gate low
	e.set_envelope_time(3, 1);
	int releaseSamples = 48;
	for (int i = 0; i < releaseSamples; i++) {
		e.update(0);
	}
	CHECK(e.update(0) == doctest::Approx(0));
}

TEST_CASE("envelope output starts at 0")
{
	Envelope e;
	CHECK(e.update(0) == doctest::Approx(0));
}