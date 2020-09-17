#ifndef _SRC_DRIVERS_INTERRUPT
#define _SRC_DRIVERS_INTERRUPT

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
	using ISRType = std::function<void(void)>;

	Interrupt() {}
	void registerISR(IRQType irqnum, ISRType func)
	{
		ISRs[irqnum] = func;
	}
	Interrupt(IRQType irqnum, ISRType func)
	{
		registerISR(irqnum, func);
	}
	static inline void callISR(IRQType irqnum)
	{
		ISRs[irqnum]();
	}

private:
	static inline ISRType ISRs[128];
};

using InterruptManager = Interrupt;
#endif
