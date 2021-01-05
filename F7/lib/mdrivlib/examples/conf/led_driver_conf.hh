#pragma once
#include "drivers/dma_config_struct.hh"
#include "stm32f7xx.h"

const DMAConfig led_driver_dma_conf = {
	.DMAx = DMA1,
	.stream = DMA1_Stream6,
	.channel = DMA_CHANNEL_1,
	.IRQn = DMA1_Stream6_IRQn,
	.pri = 3,
	.subpri = 1,
};

const uint32_t kNumLedDriverChips = 2;

