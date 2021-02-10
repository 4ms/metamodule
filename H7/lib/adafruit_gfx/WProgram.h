#include <cstdint>
struct Print {
	void write(uint8_t c) {}
};

template<typename T>
static inline T abs(T a)
{
	return (a < 0) ? -a : a;
}
