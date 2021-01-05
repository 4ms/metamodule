#pragma once

#ifdef STM32F7
	#include "stm32f7xx.h"
using IRQType = IRQn_Type;
#else
	#include <cstdint>
using IRQType = uint32_t;
#endif
#include <functional>

class Interrupt {
public:
	// Todo: Try inplace_function<void(void)> instead of std::function
	// https://github.com/WG21-SG14/SG14/blob/master/Docs/Proposals/NonAllocatingStandardFunction.pdf
	using ISRType = std::function<void(void)>;

	Interrupt() {}
	static void registerISR(IRQType irqnum, ISRType &&func)
	{
		ISRs[irqnum] = std::move(func);
	}
	Interrupt(IRQType irqnum, ISRType &&func)
	{
		ISRs[irqnum] = std::move(func);
	}
	static inline void callISR(IRQType irqnum)
	{
		ISRs[irqnum]();
	}

private:
	static inline ISRType ISRs[128];
};

using InterruptManager = Interrupt;
