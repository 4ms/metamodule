// Fault handlers: print what faulted to the console, then halt. (Without these, startup_cm33.s
// sends faults to Default_Handler, which spins silently.)

#include "console/uart_log.hh"
#include "drivers/stm32xx.h"
#include <cstdio>

namespace
{
// The registers the core pushed on entry
struct ExceptionFrame {
	uint32_t r0, r1, r2, r3, r12, lr, pc, xpsr;
};

void print(const char *str) {
	MetaModule::UartLog::write_stdout(str, __builtin_strlen(str));
}
} // namespace

extern "C" [[noreturn]] void report_fault(const ExceptionFrame *frame, uint32_t exc_return) {
	char buf[160];
	auto ipsr = __get_IPSR();

	snprintf(buf, sizeof buf, "\nM33: FAULT (exception %lu) pc=%08lx lr=%08lx xpsr=%08lx exc_return=%08lx\n",
			 (unsigned long)ipsr, (unsigned long)frame->pc, (unsigned long)frame->lr, (unsigned long)frame->xpsr,
			 (unsigned long)exc_return);
	print(buf);
	snprintf(buf, sizeof buf, "M33: CFSR=%08lx HFSR=%08lx MMFAR=%08lx BFAR=%08lx\n", (unsigned long)SCB->CFSR,
			 (unsigned long)SCB->HFSR, (unsigned long)SCB->MMFAR, (unsigned long)SCB->BFAR);
	print(buf);
#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
	snprintf(buf, sizeof buf, "M33: SFSR=%08lx SFAR=%08lx\n", (unsigned long)SAU->SFSR, (unsigned long)SAU->SFAR);
	print(buf);
#endif

	while (true)
		__BKPT(0);
}

// Passes the stack the frame was pushed to (MSP or PSP, per EXC_RETURN bit 2) and EXC_RETURN
extern "C" __attribute__((naked)) void fault_entry() {
	asm volatile("tst lr, #4		\n"
				 "ite eq			\n"
				 "mrseq r0, msp		\n"
				 "mrsne r0, psp		\n"
				 "mov r1, lr		\n"
				 "b report_fault	\n");
}

extern "C" void HardFault_Handler() __attribute__((alias("fault_entry")));
extern "C" void MemManage_Handler() __attribute__((alias("fault_entry")));
extern "C" void BusFault_Handler() __attribute__((alias("fault_entry")));
extern "C" void UsageFault_Handler() __attribute__((alias("fault_entry")));
extern "C" void SecureFault_Handler() __attribute__((alias("fault_entry")));
