#include "CppUTest/TestHarness.h"
#include "fff.h"
#undef STM32F7
#include "interrupt.hh"

static int g_state = 0;
TEST_GROUP(interrupt_tests){

	void setup(){g_state = 0;
}

void teardown() {}
}
;

static void some_func(int some_arg)
{
	g_state = some_arg;
}

TEST(interrupt_tests, lambda_gets_called)
{
	unsigned testIRQnum = 5;

	Interrupt myint{
		testIRQnum,
		[&]() { some_func(222222); },
	};

	LONGS_EQUAL(0, g_state);
	InterruptManager::callISR(testIRQnum);
	LONGS_EQUAL(222222, g_state);
}

TEST(interrupt_tests, static_init)
{
	unsigned testIRQnum = 5;
	InterruptManager::registerISR(testIRQnum, []() { some_func(33333); });

	LONGS_EQUAL(0, g_state);
	InterruptManager::callISR(testIRQnum);
	LONGS_EQUAL(33333, g_state);
}

static void register_a_local_lamba(uint32_t testIRQnum, uint32_t state_value)
{
	auto isrfunc = [state_value = state_value]() { some_func(state_value); };
	InterruptManager::registerISR(testIRQnum, isrfunc);
}

TEST(interrupt_tests, lambda_scope_ends_but_still_gets_called)
{
	unsigned testIRQnum = 5;

	register_a_local_lamba(testIRQnum, 4444);

	LONGS_EQUAL(0, g_state);
	InterruptManager::callISR(testIRQnum);
	LONGS_EQUAL(4444, g_state);
}

