#pragma once
#include "stm32f7xx.h"

namespace Interrupts {

struct I2C {
	static inline I2C_HandleTypeDef *I2C1_handle = nullptr;
	static inline I2C_HandleTypeDef *I2C2_handle = nullptr;
	static inline I2C_HandleTypeDef *I2C3_handle = nullptr;
};

struct DMA {
	static inline DMA_HandleTypeDef *DMA1_S0_handle = nullptr;
	static inline DMA_HandleTypeDef *DMA1_S1_handle = nullptr;
	static inline DMA_HandleTypeDef *DMA1_S2_handle = nullptr;
	static inline DMA_HandleTypeDef *DMA1_S3_handle = nullptr;
	static inline DMA_HandleTypeDef *DMA1_S4_handle = nullptr;
	static inline DMA_HandleTypeDef *DMA1_S5_handle = nullptr;
	static inline DMA_HandleTypeDef *DMA1_S6_handle = nullptr;
	static inline DMA_HandleTypeDef *DMA1_S7_handle = nullptr;
	static inline DMA_HandleTypeDef *DMA2_S0_handle = nullptr;
	static inline DMA_HandleTypeDef *DMA2_S1_handle = nullptr;
	static inline DMA_HandleTypeDef *DMA2_S2_handle = nullptr;
	static inline DMA_HandleTypeDef *DMA2_S3_handle = nullptr;
	static inline DMA_HandleTypeDef *DMA2_S4_handle = nullptr;
	static inline DMA_HandleTypeDef *DMA2_S5_handle = nullptr;
	static inline DMA_HandleTypeDef *DMA2_S6_handle = nullptr;
	static inline DMA_HandleTypeDef *DMA2_S7_handle = nullptr;
};

}; // namespace Interrupts
