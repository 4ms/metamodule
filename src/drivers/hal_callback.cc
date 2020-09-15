#include "hal_callback.hh"

static void HALCallbackHandler(HALCallbackID cbnum, void *handle) { HALCallbackManager::callHALCB(cbnum); }

extern "C" void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *hi2c) { HALCallbackHandler(HALCallbackID::MemTxCplt, (void *)(hi2c)); }
