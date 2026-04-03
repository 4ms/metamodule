#include "usb_video_device.hh"
#include "debug.hh"
#include <cstring>

extern "C" USBD_DescriptorsTypeDef UVC_Desc;

static USBD_VIDEO_ItfTypeDef video_fops = {
	MetaModule::UsbVideoDevice::Video_Itf_Init,
	MetaModule::UsbVideoDevice::Video_Itf_DeInit,
	MetaModule::UsbVideoDevice::Video_Itf_Control,
	MetaModule::UsbVideoDevice::Video_Itf_Data,
};

// Packet buffer for USB transmission (4-byte aligned for DMA)
static uint8_t packet_buf[UVC_PACKET_SIZE] __attribute__((aligned(4)));

namespace MetaModule
{

UsbVideoDevice::UsbVideoDevice(USBD_HandleTypeDef *pDevice)
	: pdev{pDevice} {
}

void UsbVideoDevice::start() {
	USBD_Init(pdev, &UVC_Desc, 0);
	USBD_RegisterClass(pdev, USBD_VIDEO_CLASS);
	USBD_VIDEO_RegisterInterface(pdev, &video_fops);
	USBD_Start(pdev);
}

void UsbVideoDevice::stop() {
	USBD_Stop(pdev);
	USBD_DeInit(pdev);
}

void UsbVideoDevice::set_framebuffer(uint16_t *fb) {
	shadow_fb = fb;
}

int8_t UsbVideoDevice::Video_Itf_Init() {
	packet_index = 0;
	pixel_offset = 0;
	return 0;
}

int8_t UsbVideoDevice::Video_Itf_DeInit() {
	return 0;
}

int8_t UsbVideoDevice::Video_Itf_Control(uint8_t cmd, uint8_t *pbuf, uint16_t length) {
	(void)cmd;
	(void)pbuf;
	(void)length;
	return 0;
}

int8_t UsbVideoDevice::Video_Itf_Data(uint8_t **pbuf, uint16_t *psize, uint16_t *pcktidx) {
	if (shadow_fb == nullptr) {
		*psize = 2;
		*pcktidx = 0;
		return 0;
	}

	// Shadow buffer is already YUY2 (converted on A7 side).
	// 2 bytes per pixel in YUY2, same as total byte count.
	constexpr uint32_t payload_per_packet = UVC_PACKET_SIZE - 2;
	// Align to 4 bytes (YUY2 macro-pixel = 4 bytes = 2 pixels)
	constexpr uint32_t bytes_per_packet = payload_per_packet & ~3u;
	constexpr uint32_t total_bytes = UVC_WIDTH * UVC_HEIGHT * 2;

	Debug::Pin1::high();
	if (pixel_offset < total_bytes) {
		uint32_t remaining = total_bytes - pixel_offset;
		uint32_t bytes_this_packet = (remaining < bytes_per_packet) ? remaining : bytes_per_packet;

		// Direct memcpy from pre-converted YUY2 shadow buffer
		auto *src = reinterpret_cast<const uint8_t *>(shadow_fb) + pixel_offset;
		std::memcpy(packet_buf, src, bytes_this_packet);

		*pbuf = packet_buf;
		*psize = (uint16_t)(bytes_this_packet + 2); // +2 for UVC header
		pixel_offset += bytes_this_packet;
	} else {
		// End of frame: header-only packet signals new frame
		*psize = 2;
	}
	Debug::Pin1::low();

	*pcktidx = (uint16_t)packet_index;

	if (pixel_offset >= total_bytes) {
		pixel_offset = 0;
		packet_index = 0;
	} else {
		packet_index++;
	}

	return 0;
}

} // namespace MetaModule
