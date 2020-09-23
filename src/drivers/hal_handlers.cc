#include "stm32xx.h"

extern "C" {
void SysTick_Handler(void)
{
	HAL_IncTick();
}

__attribute__((optimize("O0")))
void HardFault_Handler()
{
	volatile uint32_t hfsr, dfsr, afsr, bfar, mmfar, cfsr;
	mmfar = SCB->MMFAR;
	bfar = SCB->BFAR;

	hfsr = SCB->HFSR;
	afsr = SCB->AFSR;
	dfsr = SCB->DFSR;
	cfsr = SCB->CFSR;

	//https://interrupt.memfault.com/blog/cortex-m-fault-debug
	//UFSR
	volatile uint16_t UsageFaultStatusReg = cfsr >> 16;
	volatile bool ufsr_undef_instruction = UsageFaultStatusReg & (1<<0);
	volatile bool ufsr_invstate_invalid_EPSR = UsageFaultStatusReg & (1<<1); //e.g. thumb mode, interworking addresses
	volatile bool ufsr_invalid_PC = UsageFaultStatusReg & (1<<2); //failed integrety test on EXC_RETURN (exception return)
	volatile bool ufsr_no_coproc = UsageFaultStatusReg & (1<<3); //co-processor, e.g. FPU, not enabled
	volatile bool ufsr_unaligned = UsageFaultStatusReg & (1<<8); 
	volatile bool ufsr_divbyzero = UsageFaultStatusReg & (1<<9); 

	//BFSR
	volatile uint8_t BusFaultStatusReg = (cfsr >> 8) & 0xFF;
	volatile bool bfsr_ibuserr = BusFaultStatusReg & (1<<0);
	volatile bool bfsr_preciserr = BusFaultStatusReg & (1<<1); //instruction which was executing prior to exception entry triggered the fault
	volatile bool bfsr_impreciserr = BusFaultStatusReg & (1<<2); //hardware was not able to determine exact location of fault
	volatile bool bfsr_unstkerr = BusFaultStatusReg & (1<<3); //error returning from exception
	volatile bool bfsr_stkerr = BusFaultStatusReg & (1<<4); //fault occured during exception entry
	volatile bool bfsr_lsperr = BusFaultStatusReg & (1<<5); //fault occured during lazy state preservation
	volatile bool bfsr_BFAR_valid = BusFaultStatusReg & (1<<7); //indicates if BFAR has address that triggrered the fault

	//MMFSR
	volatile uint8_t MemManageFaultStatusReg = cfsr & 0xFF;
	volatile bool mmfsr_instr_access_violation = MemManageFaultStatusReg & (1<<0);
	volatile bool mmfsr_data_access_violation = MemManageFaultStatusReg & (1<<1);
	volatile bool mmfsr_munstkerr = MemManageFaultStatusReg & (1<<3);
	volatile bool mmfsr_mlsperr = MemManageFaultStatusReg & (1<<4);
	volatile bool mmfsr_mstkerr = MemManageFaultStatusReg & (1<<5);
	volatile bool mmfsr_mmfar_valid = MemManageFaultStatusReg & (1<<7); //indicates that MMFAR holds the address that triggered the fault

	//HFSR
	volatile bool hfsr_vectable = hfsr & (1<<1); //fault occured due to reading address in vector table
	volatile bool hfsr_forced = hfsr & (1<<30); //configurable fault was escalated to HardFault (handler not enabled, or fault occurred in handler)
	volatile bool hfsr_debugevt = hfsr & (1<<31); //Debug event (breakpoint) occured while debug subsystem not enabled


	while (1)
		;

}
//
// void assert_failed(const char* file, uint32_t line) { while (1); }
void NMI_Handler()
{
	while (1)
		;
}
void MemManage_Handler()
{
	while (1)
		;
}
void BusFault_Handler()
{
	while (1)
		;
}
void UsageFault_Handler()
{
	while (1)
		;
}
void SVC_Handler()
{
	while (1)
		;
}
void DebugMon_Handler()
{
	while (1)
		;
}
void PendSV_Handler()
{
	while (1)
		;
}
void __cxa_pure_virtual()
{
	while (1)
		;
}
}
