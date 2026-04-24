#pragma once
#include "conf/screen_buffer_conf.hh"
#include "usb/device_video/rgb565_to_bgr24.hh"
#include "usb/device_video/rgb565_to_yuy2.hh"
#include "usb/device_video/uvc_format_config.hh"
#include <cstdint>

namespace MetaModule
{

class UsbVideoBuffer {
public:
	enum class Format { YUY2, BGR24 };

private:
	// Pointer to external shadow framebuffer for USB video streaming.
	// Points to a shared memory buffer accessible from both cores.
	static inline uint8_t *uvc_shadow_fb = nullptr;
	static inline bool mirror_x = false;
#ifdef USE_UVC_FORMAT_BGR3
	static inline Format format = Format::BGR24;
#else
	static inline Format format = Format::YUY2;
#endif

	static constexpr bool dither = true;

	template<auto Writer, int BytesPerPixel>
	static void flush_impl(int xstart, int ystart, int xend, int yend, uint16_t const *buffer) {
		auto region_w = xend - xstart + 1;
		auto src = buffer;
		auto *dest_buf = uvc_shadow_fb;
		constexpr auto row_stride = ScreenBufferConf::viewWidth * BytesPerPixel;

		if (mirror_x) {
			auto dest_x = ScreenBufferConf::viewWidth - 1 - xstart;
			for (auto y = ystart; y <= yend; y++) {
				auto *row = &dest_buf[y * row_stride];
				for (int i = 0; i < region_w; i++)
					Writer(row, dest_x - i, src[i]);
				src += region_w;
			}
		} else {
			for (auto y = ystart; y <= yend; y++) {
				auto *row = &dest_buf[y * row_stride];
				for (int i = 0; i < region_w; i++)
					Writer(row, xstart + i, src[i]);
				src += region_w;
			}
		}
	}

	// Pair-aware YUY2 flush: averages the chroma of each YUY2 macro-pixel
	// (two horizontally-adjacent source pixels) into the single U,V sample
	// that 4:2:2 forces them to share. This spreads the subsampling error
	// symmetrically across both pixels of the pair instead of putting the
	// full error on one side of each edge (the classic "co-sited" fringe).
	// Pixels at a boundary where the YUY2 partner falls outside the flush
	// region fall back to per-pixel chroma.
	static void flush_yuy2_averaged(int xstart, int ystart, int xend, int yend, uint16_t const *buffer) {
		int region_w = xend - xstart + 1;
		auto src = buffer;
		auto *dest_buf = uvc_shadow_fb;
		constexpr int VW = ScreenBufferConf::viewWidth;
		constexpr auto row_stride = VW * 2;

		for (int y = ystart; y <= yend; y++) {
			auto *row = &dest_buf[y * row_stride];

			for (int i = 0; i < region_w;) {
				int dst_x = mirror_x ? (VW - 1 - xstart - i) : (xstart + i);
				auto e0 = rgb565_yuv_lut[src[i]];

				// src[i] and src[i+1] land on adjacent destination columns
				// (in either direction) and form a YUY2 pair iff (xstart+i)
				// is even — that's when the lower of the two dst_x values
				// is the even half of a macro-pixel.
				bool can_pair = (i + 1 < region_w) && (((xstart + i) & 1) == 0);

				if (can_pair) {
					int dst_x_next = mirror_x ? (VW - 2 - xstart - i) : (xstart + i + 1);
					auto e1 = rgb565_yuv_lut[src[i + 1]];

					uint8_t u_avg = (uint8_t)(((unsigned)e0.u + (unsigned)e1.u) >> 1);
					uint8_t v_avg = (uint8_t)(((unsigned)e0.v + (unsigned)e1.v) >> 1);

					row[dst_x * 2] = e0.y;
					row[dst_x_next * 2] = e1.y;

					// Whichever destination column is even holds U; the odd one holds V.
					if (dst_x & 1) {
						row[dst_x * 2 + 1] = v_avg;
						row[dst_x_next * 2 + 1] = u_avg;
					} else {
						row[dst_x * 2 + 1] = u_avg;
						row[dst_x_next * 2 + 1] = v_avg;
					}

					i += 2;
				} else {
					// Unpaired boundary: use this pixel's own chroma.
					row[dst_x * 2] = e0.y;
					row[dst_x * 2 + 1] = (dst_x & 1) ? e0.v : e0.u;
					i += 1;
				}
			}

			src += region_w;
		}
	}

public:
	static void set_frame_buffer(uint8_t *fb) {
		uvc_shadow_fb = fb;
	}

	static void set_mirroring(bool mirror) {
		mirror_x = mirror;
	}

	static void set_format(Format fmt) {
		format = fmt;
	}

	static Format get_format() {
		return format;
	}

	// Convert a flushed region from RGB565 into the shadow framebuffer
	// using the currently selected format. The M4 USB side then memcpys
	// the shadow buffer directly into USB packets.
	static void flush(int xstart, int ystart, int xend, int yend, uint16_t *buffer) {
		if (!uvc_shadow_fb)
			return;

		if (format == Format::BGR24)
			flush_impl<write_bgr24_pixel, 3>(xstart, ystart, xend, yend, buffer);
		else if (dither)
			flush_yuy2_averaged(xstart, ystart, xend, yend, buffer);
		else
			flush_impl<write_yuy2_pixel, 2>(xstart, ystart, xend, yend, buffer);
	}
};
} // namespace MetaModule
