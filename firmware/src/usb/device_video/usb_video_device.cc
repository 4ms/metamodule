#include "usb_video_device.hh"
#include "rgb565_to_yuy2.hh"
#include <cstring>

extern "C" USBD_DescriptorsTypeDef UVC_Desc;

static USBD_VIDEO_ItfTypeDef video_fops = {
	MetaModule::UsbVideoDevice::Video_Itf_Init,
	MetaModule::UsbVideoDevice::Video_Itf_DeInit,
	MetaModule::UsbVideoDevice::Video_Itf_Control,
	MetaModule::UsbVideoDevice::Video_Itf_Data,
};

// Temporary buffer for YUY2 packet data
static uint8_t yuy2_packet_buf[UVC_PACKET_SIZE] __attribute__((aligned(4)));

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

	// Payload size per packet (excluding 2-byte UVC header added by the class driver)
	constexpr uint32_t payload_per_packet = UVC_PACKET_SIZE - 2;
	// YUY2: 2 bytes per pixel (same as RGB565), so pixels per packet.
	// Round down to even so YUY2 pairs are never split across packets.
	constexpr uint32_t pixels_per_packet = (payload_per_packet / 2) & ~1u;
	// Total packets needed for one frame
	constexpr uint32_t total_pixels = UVC_WIDTH * UVC_HEIGHT;
	constexpr uint32_t total_packets = (total_pixels + pixels_per_packet - 1) / pixels_per_packet;

	if (pixel_offset < total_pixels) {
		uint32_t pixels_remaining = total_pixels - pixel_offset;
		uint32_t pixels_this_packet = (pixels_remaining < pixels_per_packet) ? pixels_remaining : pixels_per_packet;

		// Ensure even number of pixels for YUY2 pair conversion
		pixels_this_packet &= ~1u;

		// Convert RGB565 to YUY2 directly into packet buffer
		rgb565_to_yuy2(&shadow_fb[pixel_offset], yuy2_packet_buf, pixels_this_packet);

		*pbuf = yuy2_packet_buf;
		*psize = (uint16_t)(pixels_this_packet * 2 + 2); // +2 for UVC header
		pixel_offset += pixels_this_packet;
	} else {
		// End of frame: header-only packet signals new frame
		*psize = 2;
	}

	*pcktidx = (uint16_t)packet_index;

	if (pixel_offset >= total_pixels) {
		pixel_offset = 0;
		packet_index = 0;
	} else {
		packet_index++;
	}

	return 0;
}

} // namespace MetaModule
