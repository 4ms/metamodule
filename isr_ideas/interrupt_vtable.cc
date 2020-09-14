#ifdef STM32F7
	#include "stm32f7xx.h"
using IRQType = IRQn_Type;
#endif

class InterruptManager {
public:
	struct ISRBase {
		virtual void isr() = 0;
	};
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
//Todo: combine ISRBase nd InterruptManager into one class?
//The static members will only be instanced once, right? And the virtual function can be overridden, right?

extern "C" void ISRHandler(IRQType irqnum) { InterruptManager::callISR(irqnum); } //C wrapper
void WWDG_IRQHandler(void) { ISRHandler(WWDG_IRQn); }
void PVD_IRQHandler(void) { ISRHandler(PVD_IRQn); }
void TAMP_STAMP_IRQHandler(void) { ISRHandler(TAMP_STAMP_IRQn); }
void RTC_WKUP_IRQHandler(void) { ISRHandler(RTC_WKUP_IRQn); }
void FLASH_IRQHandler(void) { ISRHandler(FLASH_IRQn); }
void RCC_IRQHandler(void) { ISRHandler(RCC_IRQn); }
void EXTI0_IRQHandler(void) { ISRHandler(EXTI0_IRQn); }
void EXTI1_IRQHandler(void) { ISRHandler(EXTI1_IRQn); }
void EXTI2_IRQHandler(void) { ISRHandler(EXTI2_IRQn); }
void EXTI3_IRQHandler(void) { ISRHandler(EXTI3_IRQn); }
void EXTI4_IRQHandler(void) { ISRHandler(EXTI4_IRQn); }
void DMA1_Stream0_IRQHandler(void) { ISRHandler(DMA1_Stream0_IRQn); }
void DMA1_Stream1_IRQHandler(void) { ISRHandler(DMA1_Stream1_IRQn); }
void DMA1_Stream2_IRQHandler(void) { ISRHandler(DMA1_Stream2_IRQn); }
void DMA1_Stream3_IRQHandler(void) { ISRHandler(DMA1_Stream3_IRQn); }
void DMA1_Stream4_IRQHandler(void) { ISRHandler(DMA1_Stream4_IRQn); }
void DMA1_Stream5_IRQHandler(void) { ISRHandler(DMA1_Stream5_IRQn); }
void DMA1_Stream6_IRQHandler(void) { ISRHandler(DMA1_Stream6_IRQn); }
void ADC_IRQHandler(void) { ISRHandler(ADC_IRQn); }
void CAN1_TX_IRQHandler(void) { ISRHandler(CAN1_TX_IRQn); }
void CAN1_RX0_IRQHandler(void) { ISRHandler(CAN1_RX0_IRQn); }
void CAN1_RX1_IRQHandler(void) { ISRHandler(CAN1_RX1_IRQn); }
void CAN1_SCE_IRQHandler(void) { ISRHandler(CAN1_SCE_IRQn); }
void EXTI9_5_IRQHandler(void) { ISRHandler(EXTI9_5_IRQn); }
void TIM1_BRK_TIM9_IRQHandler(void) { ISRHandler(TIM1_BRK_TIM9_IRQn); }
void TIM1_UP_TIM10_IRQHandler(void) { ISRHandler(TIM1_UP_TIM10_IRQn); }
void TIM1_TRG_COM_TIM11_IRQHandler(void) { ISRHandler(TIM1_TRG_COM_TIM11_IRQn); }
void TIM1_CC_IRQHandler(void) { ISRHandler(TIM1_CC_IRQn); }
void TIM2_IRQHandler(void) { ISRHandler(TIM2_IRQn); }
void TIM3_IRQHandler(void) { ISRHandler(TIM3_IRQn); }
void TIM4_IRQHandler(void) { ISRHandler(TIM4_IRQn); }
void I2C1_EV_IRQHandler(void) { ISRHandler(I2C1_EV_IRQn); }
void I2C1_ER_IRQHandler(void) { ISRHandler(I2C1_ER_IRQn); }
void I2C2_EV_IRQHandler(void) { ISRHandler(I2C2_EV_IRQn); }
void I2C2_ER_IRQHandler(void) { ISRHandler(I2C2_ER_IRQn); }
void SPI1_IRQHandler(void) { ISRHandler(SPI1_IRQn); }
void SPI2_IRQHandler(void) { ISRHandler(SPI2_IRQn); }
void USART1_IRQHandler(void) { ISRHandler(USART1_IRQn); }
void USART2_IRQHandler(void) { ISRHandler(USART2_IRQn); }
void USART3_IRQHandler(void) { ISRHandler(USART3_IRQn); }
void EXTI15_10_IRQHandler(void) { ISRHandler(EXTI15_10_IRQn); }
void RTC_Alarm_IRQHandler(void) { ISRHandler(RTC_Alarm_IRQn); }
void OTG_FS_WKUP_IRQHandler(void) { ISRHandler(OTG_FS_WKUP_IRQn); }
void TIM8_BRK_TIM12_IRQHandler(void) { ISRHandler(TIM8_BRK_TIM12_IRQn); }
void TIM8_UP_TIM13_IRQHandler(void) { ISRHandler(TIM8_UP_TIM13_IRQn); }
void TIM8_TRG_COM_TIM14_IRQHandler(void) { ISRHandler(TIM8_TRG_COM_TIM14_IRQn); }
void TIM8_CC_IRQHandler(void) { ISRHandler(TIM8_CC_IRQn); }
void DMA1_Stream7_IRQHandler(void) { ISRHandler(DMA1_Stream7_IRQn); }
void FMC_IRQHandler(void) { ISRHandler(FMC_IRQn); }
void SDMMC1_IRQHandler(void) { ISRHandler(SDMMC1_IRQn); }
void TIM5_IRQHandler(void) { ISRHandler(TIM5_IRQn); }
void SPI3_IRQHandler(void) { ISRHandler(SPI3_IRQn); }
void UART4_IRQHandler(void) { ISRHandler(UART4_IRQn); }
void UART5_IRQHandler(void) { ISRHandler(UART5_IRQn); }
void TIM6_DAC_IRQHandler(void) { ISRHandler(TIM6_DAC_IRQn); }
void TIM7_IRQHandler(void) { ISRHandler(TIM7_IRQn); }
void DMA2_Stream0_IRQHandler(void) { ISRHandler(DMA2_Stream0_IRQn); }
void DMA2_Stream1_IRQHandler(void) { ISRHandler(DMA2_Stream1_IRQn); }
void DMA2_Stream2_IRQHandler(void) { ISRHandler(DMA2_Stream2_IRQn); }
void DMA2_Stream3_IRQHandler(void) { ISRHandler(DMA2_Stream3_IRQn); }
void DMA2_Stream4_IRQHandler(void) { ISRHandler(DMA2_Stream4_IRQn); }
void OTG_FS_IRQHandler(void) { ISRHandler(OTG_FS_IRQn); }
void DMA2_Stream5_IRQHandler(void) { ISRHandler(DMA2_Stream5_IRQn); }
void DMA2_Stream6_IRQHandler(void) { ISRHandler(DMA2_Stream6_IRQn); }
void DMA2_Stream7_IRQHandler(void) { ISRHandler(DMA2_Stream7_IRQn); }
void USART6_IRQHandler(void) { ISRHandler(USART6_IRQn); }
void I2C3_EV_IRQHandler(void) { ISRHandler(I2C3_EV_IRQn); }
void I2C3_ER_IRQHandler(void) { ISRHandler(I2C3_ER_IRQn); }
void OTG_HS_EP1_OUT_IRQHandler(void) { ISRHandler(OTG_HS_EP1_OUT_IRQn); }
void OTG_HS_EP1_IN_IRQHandler(void) { ISRHandler(OTG_HS_EP1_IN_IRQn); }
void OTG_HS_WKUP_IRQHandler(void) { ISRHandler(OTG_HS_WKUP_IRQn); }
void OTG_HS_IRQHandler(void) { ISRHandler(OTG_HS_IRQn); }
void AES_IRQHandler(void) { ISRHandler(AES_IRQn); }
void RNG_IRQHandler(void) { ISRHandler(RNG_IRQn); }
void FPU_IRQHandler(void) { ISRHandler(FPU_IRQn); }
void UART7_IRQHandler(void) { ISRHandler(UART7_IRQn); }
void UART8_IRQHandler(void) { ISRHandler(UART8_IRQn); }
void SPI4_IRQHandler(void) { ISRHandler(SPI4_IRQn); }
void SPI5_IRQHandler(void) { ISRHandler(SPI5_IRQn); }
void SAI1_IRQHandler(void) { ISRHandler(SAI1_IRQn); }
void SAI2_IRQHandler(void) { ISRHandler(SAI2_IRQn); }
void QUADSPI_IRQHandler(void) { ISRHandler(QUADSPI_IRQn); }
void LPTIM1_IRQHandler(void) { ISRHandler(LPTIM1_IRQn); }
void SDMMC2_IRQHandler(void) { ISRHandler(SDMMC2_IRQn); }

// MyClass.cc:
//
class myDevice : private InterruptManager::ISRBase {
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
	uint32_t privateSendData()
	{
		volatile uint32_t doNothing;
		doNothing = 0;
		return doNothing;
	}
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
