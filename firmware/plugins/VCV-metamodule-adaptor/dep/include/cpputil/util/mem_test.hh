#include <cstdint>

struct MemTest {
	static bool check(uint32_t *start, uint32_t *stop) {
		auto encode = [](uint32_t x) { return x * 0x55555555 + 0x00700707; };
		const uint32_t initseed = 0x1234FEDC;

		//Write
		{
			uint32_t seed = initseed;
			for (uint32_t *wr = start; wr < stop; wr++) {
				*wr = seed;
				seed = encode(seed);
			}
		}

		//Read
		{
			uint32_t seed = initseed;
			for (uint32_t *rd = start; rd < stop; rd++) {
				if (*rd != seed) {
					return false;
				}
				seed = encode(seed);
			}
		}

		return true;
	}

	static bool check(uint32_t startaddr, uint32_t stopaddr) {
		if (startaddr > stopaddr)
			return false;
		auto *start = reinterpret_cast<uint32_t *>(startaddr);
		auto *stop = reinterpret_cast<uint32_t *>(stopaddr);
		return check(start, stop);
	}
};
