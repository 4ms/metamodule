#pragma once
#include "stm32f7xx.h"

struct I2C_IRQ_instances {
	static inline I2C_HandleTypeDef *I2C1_handle = nullptr;
	static inline I2C_HandleTypeDef *I2C2_handle = nullptr;
	static inline I2C_HandleTypeDef *I2C3_handle = nullptr;
};

