#include "drivers/stm32xx.h"

volatile bool sd_rx = false;
volatile bool sd_tx = false;

extern "C" void HAL_SD_RxCpltCallback(SD_HandleTypeDef *hsd) { sd_rx = true; }
extern "C" void HAL_SD_TxCpltCallback(SD_HandleTypeDef *hsd) { sd_tx = true; }

