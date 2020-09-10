#include "stm32f7xx.h"
#include "stm32f7xx_hal_i2c.h"
#include "interrupt.hh"

//Rename stm32_hal_it.cc ?

extern "C" void I2C1_EV_IRQHandler(void)
{
	if (I2C_IRQ_instances::I2C1_handle != nullptr)
		HAL_I2C_EV_IRQHandler(I2C_IRQ_instances::I2C1_handle);
}
extern "C" void I2C1_ER_IRQHandler(void)
{
	if (I2C_IRQ_instances::I2C1_handle != nullptr)
		HAL_I2C_ER_IRQHandler(I2C_IRQ_instances::I2C1_handle);
}

extern "C" void I2C2_EV_IRQHandler(void)
{
	if (I2C_IRQ_instances::I2C2_handle != nullptr)
		HAL_I2C_EV_IRQHandler(I2C_IRQ_instances::I2C2_handle);
}
extern "C" void I2C2_ER_IRQHandler(void)
{
	if (I2C_IRQ_instances::I2C2_handle != nullptr)
		HAL_I2C_ER_IRQHandler(I2C_IRQ_instances::I2C2_handle);
}

extern "C" void I2C3_EV_IRQHandler(void)
{
	if (I2C_IRQ_instances::I2C3_handle != nullptr)
		HAL_I2C_EV_IRQHandler(I2C_IRQ_instances::I2C3_handle);
}
extern "C" void I2C3_ER_IRQHandler(void)
{
	if (I2C_IRQ_instances::I2C3_handle != nullptr)
		HAL_I2C_ER_IRQHandler(I2C_IRQ_instances::I2C3_handle);
}

