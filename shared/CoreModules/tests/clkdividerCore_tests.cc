#include "CoreModules/clkdividerCore.h"
#include "doctest.h"
#include <stdint.h>

void clockPulse(ClkdividerCore *cIn)
{
	cIn->set_input(0, 1.0f);
	cIn->update();
	cIn->set_input(0, 0.0f);
	cIn->update();
}

void waitCycle(ClkdividerCore *cIn)
{
	cIn->update();
}

TEST_CASE("output defaults to off")
{
	ClkdividerCore c;
	c.update();

	CHECK(c.get_output(0) == 0.0f);
}

TEST_CASE("50% pulsewidth check")
{
	ClkdividerCore c;

	clockPulse(&c);
	waitCycle(&c);
	waitCycle(&c);
	waitCycle(&c);
	clockPulse(&c);
	CHECK(c.get_output(0) == 1.0f);
	waitCycle(&c);
	CHECK(c.get_output(0) == 1.0f);
	waitCycle(&c);
	CHECK(c.get_output(0) == 0.0f);
	waitCycle(&c);
	CHECK(c.get_output(0) == 0.0f);
}

TEST_CASE("test divide by 16")
{
	ClkdividerCore c;
	c.set_samplerate(48000);
	c.set_param(0, 1.0f);

	clockPulse(&c);
	waitCycle(&c);
	waitCycle(&c);
	waitCycle(&c);
	clockPulse(&c); // establish clock duration
	CHECK(c.get_output(0) == 1.0f);
	waitCycle(&c);
	CHECK(c.get_output(0) == 1.0f);
	waitCycle(&c);
	CHECK(c.get_output(0) == 1.0f);
	waitCycle(&c);
	CHECK(c.get_output(0) == 1.0f);
	clockPulse(&c);
	CHECK(c.get_output(0) == 1.0f);
	waitCycle(&c);
	CHECK(c.get_output(0) == 1.0f);
	waitCycle(&c);
	CHECK(c.get_output(0) == 1.0f);
	waitCycle(&c);
	CHECK(c.get_output(0) == 1.0f);
	clockPulse(&c);
	CHECK(c.get_output(0) == 0.0f);
	waitCycle(&c);
	CHECK(c.get_output(0) == 0.0f);
	waitCycle(&c);
	CHECK(c.get_output(0) == 0.0f);
	waitCycle(&c);
	CHECK(c.get_output(0) == 0.0f);
	clockPulse(&c);
	CHECK(c.get_output(0) == 0.0f);
	waitCycle(&c);
	CHECK(c.get_output(0) == 0.0f);
	waitCycle(&c);
	CHECK(c.get_output(0) == 0.0f);
	waitCycle(&c);
	CHECK(c.get_output(0) == 0.0f);
	clockPulse(&c);
}