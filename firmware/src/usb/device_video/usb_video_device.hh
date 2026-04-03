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

	// Set the pointer to the YUY2 shadow framebuffer (320x240, pre-converted on A7)
	static void set_framebuffer(uint16_t *fb);

	static int8_t Video_Itf_Init();
	static int8_t Video_Itf_DeInit();
	static int8_t Video_Itf_Control(uint8_t cmd, uint8_t *pbuf, uint16_t length);
	static int8_t Video_Itf_Data(uint8_t **pbuf, uint16_t *psize, uint16_t *pcktidx);

private:
	USBD_HandleTypeDef *pdev;

	static inline uint16_t *shadow_fb = nullptr;
	static inline uint32_t pixel_offset = 0;
	static inline uint32_t packet_index = 0;
};

} // namespace MetaModule
