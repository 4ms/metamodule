#pragma once
#include "dig_inout_pins.hh"

#ifdef TRIGDEBUGMODE
#define DEBUGON DigIO::TrigJack::high();
#define DEBUGOFF DigIO::TrigJack::low();
#else
#define DEBUGON DigIO::DebugOut::high();
#define DEBUGOFF DigIO::DebugOut::low();
#endif

void init_dig_inouts(void);
