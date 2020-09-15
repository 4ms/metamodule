#ifndef _SRC_DRIVERS_INTERRUPT
#define _SRC_DRIVERS_INTERRUPT

#ifdef STM32F7
	#include "stm32f7xx.h"
using IRQType = IRQn_Type;
#else
	#include <cstdint>
using IRQType = uint32_t;
#endif

class InterruptManager {
public:
	struct ISRBase {
		virtual void isr() = 0;
	};
	//using ISRType = void (*)(void); //static funcs
	using ISRType = ISRBase *; //virtual funcs
	static inline void registerISR(IRQType irqnum, ISRType isr)
	{
		ISRs[irqnum] = isr;
	}
	static inline void callISR(IRQType irqnum)
	{
		//ISRs[irqnum]();  //static funcs
		ISRs[irqnum]->isr(); //virt funcs
	}

private:
	static inline ISRType ISRs[128];
};

#endif
