#pragma once
#include "conf/screen_buffer_conf.hh"
#include "usb/device_video/rgb565_to_yuy2.hh"
#include <cstdint>

namespace MetaModule
{

class UsbVideoBuffer {
	// Pointer to external shadow framebuffer for USB video streaming.
	// Points to a shared memory buffer accessible from both cores.

	static inline uint16_t *uvc_shadow_fb = nullptr;
	static inline bool mirror_x = false;

public:
	static void set_frame_buffer(uint16_t *fb) {
		uvc_shadow_fb = fb;
	}

	static void set_mirroring(bool mirror) {
		mirror_x = mirror;
	}

	// Convert flushed region from RGB565 to YUY2 into the shadow framebuffer.
	// The M4 USB side will then memcpy directly
	static void flush(int xstart, int ystart, int xend, int yend, uint16_t *buffer) {
		if (uvc_shadow_fb) {
			auto region_w = xend - xstart + 1;
			auto src = buffer;
			auto *yuy2_buf = reinterpret_cast<uint8_t *>(uvc_shadow_fb);

			if (mirror_x) {
				for (auto y = ystart; y <= yend; y++) {
					auto *yuy2_row = &yuy2_buf[y * ScreenBufferConf::viewWidth * 2];
					auto dest_x = ScreenBufferConf::viewWidth - 1 - xstart;
					for (int i = 0; i < region_w; i++) {
						write_yuy2_pixel(yuy2_row, dest_x - i, src[i]);
					}
					src += region_w;
				}
			} else {
				for (auto y = ystart; y <= yend; y++) {
					auto *yuy2_row = &yuy2_buf[y * ScreenBufferConf::viewWidth * 2];
					for (int i = 0; i < region_w; i++) {
						write_yuy2_pixel(yuy2_row, xstart + i, src[i]);
					}
					src += region_w;
				}
			}
		}
	}
};
} // namespace MetaModule
