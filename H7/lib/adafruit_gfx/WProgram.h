#include <cstdint>
#ifndef PROGMEM
	#define PROGMEM
#endif

template<typename T>
static inline T abs(T a)
{
	return (a < 0) ? -a : a;
}
