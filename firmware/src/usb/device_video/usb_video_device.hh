#pragma once
#include "usbd_core.h"
#include "usbd_video.h"
#include <cstdint>

namespace MetaModule
{

class UsbVideoDevice {
public:
	UsbVideoDevice(USBD_HandleTypeDef *pDevice);

	void start();
	void stop();
	void soft_stop();

	// Set the pointer to the shadow framebuffer (pre-converted on A7).
	// Contents are either YUY2 (2 bytes/pixel) or BGR24 (3 bytes/pixel),
	// selected at compile time via USE_UVC_FORMAT_BGR3.
	static void set_framebuffer(uint8_t *fb);

	static int8_t Video_Itf_Init();
	static int8_t Video_Itf_DeInit();
	static int8_t Video_Itf_Control(uint8_t cmd, uint8_t *pbuf, uint16_t length);
	static int8_t Video_Itf_Data(uint8_t **pbuf, uint16_t *psize, uint16_t *pcktidx);

private:
	USBD_HandleTypeDef *pdev;

	static inline uint8_t *shadow_fb = nullptr;
	static inline uint32_t pixel_offset = 0;
	static inline uint32_t packet_index = 0;
};

} // namespace MetaModule
