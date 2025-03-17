#pragma once
#include "stm32mp1xx.h"
#include <stdint.h>

inline uint32_t LL_USB_GetMode(USB_OTG_GlobalTypeDef *USBx) {
	return ((USBx->GINTSTS) & 0x1U);
}

inline uint32_t LL_USB_ReadInterrupts(USB_OTG_GlobalTypeDef *USBx) {
	uint32_t tmpreg;

	tmpreg = USBx->GINTSTS;
	tmpreg &= USBx->GINTMSK;

	return tmpreg;
	// return USBx->GINTSTS & USBx->GINTMSK;
}

inline void LL_USB_CLEAR_INT_FLAG(USB_OTG_GlobalTypeDef *USBx, uint32_t interrupt) {
	USBx->GINTSTS = interrupt;
}

inline uint32_t flag_is_set(uint32_t flags, uint32_t interrupt) {
	return (flags & interrupt) == interrupt;
}

inline uint32_t LL_USB_HC_ReadInterrupt(USB_OTG_GlobalTypeDef *USBx) {
	uint32_t USBx_BASE = (uint32_t)USBx;

	return ((USBx_HOST->HAINT) & 0xFFFFU);
}
