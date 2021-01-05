#include "interrupt.hh"

static void ISRHandler(IRQType irqnum) { InterruptManager::callISR(irqnum); }

extern "C" void WWDG_IRQHandler(void) { ISRHandler(WWDG_IRQn); }
extern "C" void PVD_IRQHandler(void) { ISRHandler(PVD_IRQn); }
extern "C" void TAMP_STAMP_IRQHandler(void) { ISRHandler(TAMP_STAMP_IRQn); }
extern "C" void RTC_WKUP_IRQHandler(void) { ISRHandler(RTC_WKUP_IRQn); }
extern "C" void FLASH_IRQHandler(void) { ISRHandler(FLASH_IRQn); }
extern "C" void RCC_IRQHandler(void) { ISRHandler(RCC_IRQn); }
extern "C" void EXTI0_IRQHandler(void) { ISRHandler(EXTI0_IRQn); }
extern "C" void EXTI1_IRQHandler(void) { ISRHandler(EXTI1_IRQn); }
extern "C" void EXTI2_IRQHandler(void) { ISRHandler(EXTI2_IRQn); }
extern "C" void EXTI3_IRQHandler(void) { ISRHandler(EXTI3_IRQn); }
extern "C" void EXTI4_IRQHandler(void) { ISRHandler(EXTI4_IRQn); }
extern "C" void DMA1_Stream0_IRQHandler(void) { ISRHandler(DMA1_Stream0_IRQn); }
extern "C" void DMA1_Stream1_IRQHandler(void) { ISRHandler(DMA1_Stream1_IRQn); }
extern "C" void DMA1_Stream2_IRQHandler(void) { ISRHandler(DMA1_Stream2_IRQn); }
extern "C" void DMA1_Stream3_IRQHandler(void) { ISRHandler(DMA1_Stream3_IRQn); }
extern "C" void DMA1_Stream4_IRQHandler(void) { ISRHandler(DMA1_Stream4_IRQn); }
extern "C" void DMA1_Stream5_IRQHandler(void) { ISRHandler(DMA1_Stream5_IRQn); }
extern "C" void DMA1_Stream6_IRQHandler(void) { ISRHandler(DMA1_Stream6_IRQn); }
extern "C" void ADC_IRQHandler(void) { ISRHandler(ADC_IRQn); }
extern "C" void CAN1_TX_IRQHandler(void) { ISRHandler(CAN1_TX_IRQn); }
extern "C" void CAN1_RX0_IRQHandler(void) { ISRHandler(CAN1_RX0_IRQn); }
extern "C" void CAN1_RX1_IRQHandler(void) { ISRHandler(CAN1_RX1_IRQn); }
extern "C" void CAN1_SCE_IRQHandler(void) { ISRHandler(CAN1_SCE_IRQn); }
extern "C" void EXTI9_5_IRQHandler(void) { ISRHandler(EXTI9_5_IRQn); }
extern "C" void TIM1_BRK_TIM9_IRQHandler(void) { ISRHandler(TIM1_BRK_TIM9_IRQn); }
extern "C" void TIM1_UP_TIM10_IRQHandler(void) { ISRHandler(TIM1_UP_TIM10_IRQn); }
extern "C" void TIM1_TRG_COM_TIM11_IRQHandler(void) { ISRHandler(TIM1_TRG_COM_TIM11_IRQn); }
extern "C" void TIM1_CC_IRQHandler(void) { ISRHandler(TIM1_CC_IRQn); }
extern "C" void TIM2_IRQHandler(void) { ISRHandler(TIM2_IRQn); }
extern "C" void TIM3_IRQHandler(void) { ISRHandler(TIM3_IRQn); }
extern "C" void TIM4_IRQHandler(void) { ISRHandler(TIM4_IRQn); }
extern "C" void I2C1_EV_IRQHandler(void) { ISRHandler(I2C1_EV_IRQn); }
extern "C" void I2C1_ER_IRQHandler(void) { ISRHandler(I2C1_ER_IRQn); }
extern "C" void I2C2_EV_IRQHandler(void) { ISRHandler(I2C2_EV_IRQn); }
extern "C" void I2C2_ER_IRQHandler(void) { ISRHandler(I2C2_ER_IRQn); }
extern "C" void SPI1_IRQHandler(void) { ISRHandler(SPI1_IRQn); }
extern "C" void SPI2_IRQHandler(void) { ISRHandler(SPI2_IRQn); }
extern "C" void USART1_IRQHandler(void) { ISRHandler(USART1_IRQn); }
extern "C" void USART2_IRQHandler(void) { ISRHandler(USART2_IRQn); }
extern "C" void USART3_IRQHandler(void) { ISRHandler(USART3_IRQn); }
extern "C" void EXTI15_10_IRQHandler(void) { ISRHandler(EXTI15_10_IRQn); }
extern "C" void RTC_Alarm_IRQHandler(void) { ISRHandler(RTC_Alarm_IRQn); }
extern "C" void OTG_FS_WKUP_IRQHandler(void) { ISRHandler(OTG_FS_WKUP_IRQn); }
extern "C" void TIM8_BRK_TIM12_IRQHandler(void) { ISRHandler(TIM8_BRK_TIM12_IRQn); }
extern "C" void TIM8_UP_TIM13_IRQHandler(void) { ISRHandler(TIM8_UP_TIM13_IRQn); }
extern "C" void TIM8_TRG_COM_TIM14_IRQHandler(void) { ISRHandler(TIM8_TRG_COM_TIM14_IRQn); }
extern "C" void TIM8_CC_IRQHandler(void) { ISRHandler(TIM8_CC_IRQn); }
extern "C" void DMA1_Stream7_IRQHandler(void) { ISRHandler(DMA1_Stream7_IRQn); }
extern "C" void FMC_IRQHandler(void) { ISRHandler(FMC_IRQn); }
extern "C" void SDMMC1_IRQHandler(void) { ISRHandler(SDMMC1_IRQn); }
extern "C" void TIM5_IRQHandler(void) { ISRHandler(TIM5_IRQn); }
extern "C" void SPI3_IRQHandler(void) { ISRHandler(SPI3_IRQn); }
extern "C" void UART4_IRQHandler(void) { ISRHandler(UART4_IRQn); }
extern "C" void UART5_IRQHandler(void) { ISRHandler(UART5_IRQn); }
extern "C" void TIM6_DAC_IRQHandler(void) { ISRHandler(TIM6_DAC_IRQn); }
extern "C" void TIM7_IRQHandler(void) { ISRHandler(TIM7_IRQn); }
extern "C" void DMA2_Stream0_IRQHandler(void) { ISRHandler(DMA2_Stream0_IRQn); }
extern "C" void DMA2_Stream1_IRQHandler(void) { ISRHandler(DMA2_Stream1_IRQn); }
extern "C" void DMA2_Stream2_IRQHandler(void) { ISRHandler(DMA2_Stream2_IRQn); }
extern "C" void DMA2_Stream3_IRQHandler(void) { ISRHandler(DMA2_Stream3_IRQn); }
extern "C" void DMA2_Stream4_IRQHandler(void) { ISRHandler(DMA2_Stream4_IRQn); }
extern "C" void OTG_FS_IRQHandler(void) { ISRHandler(OTG_FS_IRQn); }
extern "C" void DMA2_Stream5_IRQHandler(void) { ISRHandler(DMA2_Stream5_IRQn); }
extern "C" void DMA2_Stream6_IRQHandler(void) { ISRHandler(DMA2_Stream6_IRQn); }
extern "C" void DMA2_Stream7_IRQHandler(void) { ISRHandler(DMA2_Stream7_IRQn); }
extern "C" void USART6_IRQHandler(void) { ISRHandler(USART6_IRQn); }
extern "C" void I2C3_EV_IRQHandler(void) { ISRHandler(I2C3_EV_IRQn); }
extern "C" void I2C3_ER_IRQHandler(void) { ISRHandler(I2C3_ER_IRQn); }
extern "C" void OTG_HS_EP1_OUT_IRQHandler(void) { ISRHandler(OTG_HS_EP1_OUT_IRQn); }
extern "C" void OTG_HS_EP1_IN_IRQHandler(void) { ISRHandler(OTG_HS_EP1_IN_IRQn); }
extern "C" void OTG_HS_WKUP_IRQHandler(void) { ISRHandler(OTG_HS_WKUP_IRQn); }
extern "C" void OTG_HS_IRQHandler(void) { ISRHandler(OTG_HS_IRQn); }
#ifdef AES
extern "C" void AES_IRQHandler(void) { ISRHandler(AES_IRQn); }
#endif
extern "C" void RNG_IRQHandler(void) { ISRHandler(RNG_IRQn); }
extern "C" void FPU_IRQHandler(void) { ISRHandler(FPU_IRQn); }
extern "C" void UART7_IRQHandler(void) { ISRHandler(UART7_IRQn); }
extern "C" void UART8_IRQHandler(void) { ISRHandler(UART8_IRQn); }
extern "C" void SPI4_IRQHandler(void) { ISRHandler(SPI4_IRQn); }
extern "C" void SPI5_IRQHandler(void) { ISRHandler(SPI5_IRQn); }
extern "C" void SAI1_IRQHandler(void) { ISRHandler(SAI1_IRQn); }
extern "C" void SAI2_IRQHandler(void) { ISRHandler(SAI2_IRQn); }
extern "C" void QUADSPI_IRQHandler(void) { ISRHandler(QUADSPI_IRQn); }
extern "C" void LPTIM1_IRQHandler(void) { ISRHandler(LPTIM1_IRQn); }
#ifdef SDMMC2
extern "C" void SDMMC2_IRQHandler(void) { ISRHandler(SDMMC2_IRQn); }
#endif
#ifdef SPI6
extern "C" void SPI6_IRQHandler(void) { ISRHandler(SPI6_IRQn); }
#endif
#ifdef LTDC
extern "C" void LTDC_IRQHandler(void) { ISRHandler(LTDC_IRQn); } 
#endif
#ifdef LTDC
extern "C" void LTDC_ER_IRQHandler(void) { ISRHandler(LTDC_ER_IRQn); }
#endif
#ifdef DMA2D
extern "C" void DMA2D_IRQHandler(void) { ISRHandler(DMA2D_IRQn); }  
#endif
#ifdef CEC
extern "C" void CEC_IRQHandler(void) { ISRHandler(CEC_IRQn); }    
#endif
#ifdef I2C4
extern "C" void I2C4_EV_IRQHandler(void) { ISRHandler(I2C4_EV_IRQn); }
#endif
#ifdef I2C4
extern "C" void I2C4_ER_IRQHandler(void) { ISRHandler(I2C4_ER_IRQn); }
#endif
#ifdef SPDIF_RX
extern "C" void SPDIF_RX_IRQHandler(void) { ISRHandler(SPDIF_RX_IRQn); }
#endif
