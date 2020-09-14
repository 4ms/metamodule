#include "interrupt.hh"
#include "stm32f7xx.h"
#include "stm32f7xx_hal_i2c.h"

//Rename stm32_hal_it.cc ?
using namespace Interrupts;

extern "C" void I2C1_EV_IRQHandler(void)
{
	if (I2C::I2C1_handle != nullptr)
		HAL_I2C_EV_IRQHandler(I2C::I2C1_handle);
}
extern "C" void I2C1_ER_IRQHandler(void)
{
	if (I2C::I2C1_handle != nullptr)
		HAL_I2C_ER_IRQHandler(I2C::I2C1_handle);
}

extern "C" void I2C2_EV_IRQHandler(void)
{
	if (I2C::I2C2_handle != nullptr)
		HAL_I2C_EV_IRQHandler(I2C::I2C2_handle);
}
extern "C" void I2C2_ER_IRQHandler(void)
{
	if (I2C::I2C2_handle != nullptr)
		HAL_I2C_ER_IRQHandler(I2C::I2C2_handle);
}

extern "C" void I2C3_EV_IRQHandler(void)
{
	if (I2C::I2C3_handle != nullptr)
		HAL_I2C_EV_IRQHandler(I2C::I2C3_handle);
}
extern "C" void I2C3_ER_IRQHandler(void)
{
	if (I2C::I2C3_handle != nullptr)
		HAL_I2C_ER_IRQHandler(I2C::I2C3_handle);
}

extern "C" void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	//if i2c==I2C::I2C_MemTxCplt_handle[0]
	// 	if (I2C::I2C_MemTxCplt_cb[0] != nullptr)
	// 	    I2C::I2C_MemTxCplt_cb[0]();
}

extern "C" void DMA1_Stream6_IRQHandler(void)
{
	if (DMA::DMA1_S6_handle != nullptr)
		HAL_DMA_IRQHandler(DMA::DMA1_S6_handle);
}

