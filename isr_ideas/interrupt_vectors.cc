//Interrup vectors
#include <cstdint>

#ifdef STM32F7
	#include "stm32f7xx.h"
using IRQType = IRQn_Type;
#endif

struct ISRBase {
	virtual void isr() = 0;
};

class InterruptManager {
public:
	//using ISRType = void (*)(void); //static funcs
	using ISRType = ISRBase *; //virtual funcs
	static inline void registerISR(IRQType irqnum, ISRType isr) { ISRs[irqnum] = isr; }
	static inline void callISR(IRQType irqnum)
	{
		//ISRs[irqnum]();  //static funcs
		ISRs[irqnum]->isr(); //virt funcs
	}

private:
	static ISRType ISRs[128];
};
extern "C" void ISRHandler(IRQType irqnum) { InterruptManager::callISR(irqnum); } //C wrapper

class myDevice : private ISRBase {
	myDevice()
	{
		InterruptManager::registerISR(I2C1_EV_IRQn, this);
	}

	virtual void isr()
	{
		//run some isr code
		err_code = privateSendData();
	}

private:
	uint32_t privateSendData();
	uint32_t err_code;
};

/*
 A) Getting to our API (ISRHandler())

 A-1) Standard CMSIS ISR --> ISRHandler(#) --> our ISR

 //stm32f7xx_isr_vectors.c
 void WWDG_IRQHandler(void) { ISRHandler(WWDG_IRQn); }
 ...
 void DMA1_Stream0_IRQHandler(void) { ISRHandler(DMA1_Stream0_IRQn); }
 ...
 void ISRHandler(int irqnum) {
	if (isr_vector[irqnum] != nullptr) isr_vector[irqnum]();
 }

 A-2) Standard CMSIS ISR --> our ISR

 void DMA1_Stream0_IRQHandler(void) {
	if (isr_vectors[DMA1_Stream0_IRQn]) isr_vectors[DMA1_Stream0_IRQn]();
 }

 A-3) Manually created Compile-time isr_vector (??bad idea?)
 We set the address of a callable object at compile type by manually adding it to an array
 and store that in an isr_vectors array, which is linked to 0x00000000 + FLASH_RAM_BASE_ADDR

  __attribute__((section("isr_vector"))) const uint32_t isr_vectors[] = {
	_estack,
	getAddrOfFunction(Reset_Handler),
	...
	getAddrOfFunction(MyI2CDeviceDriver::typeNameOfMyFunctionHere); //"register" by manually entering it here
 }
 constexpr uintptr_t getAddrOfFunction(void(f)(void)) { return static_cast<uint32_t>(*f); ??  }

 B)

 using ISRType = (void *)(void); //?
 using ISRType = ...(?);
 using ISRType = ...(?);

 void registerISR(IRQn_Type irqnum, ISRType isr) {
	isr_vectors[irqnum] = isr;
 }



 B) Storing callable objects:
 1) Static member functions:
 (similar to namespaced flat functions)

 //myI2CDevice.cc
 class myI2CDevice {
 	myI2CDevice() {
		instance = this;
		registerISR(I2C1_IRQn, myI2C_ISRHandler);
	}
	static void myI2C_ISRHandler() {
		instance->sendData(...)
		...
	}
	myI2C_ISRHandler *instance;
  };



 */
