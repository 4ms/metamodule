#pragma once
#include "conf/hsem_conf.hh"
#include "conf/screen_conf.hh"
#include "debug.hh"
#include "drivers/cache.hh"
#include "drivers/hsem.hh"
#include "drivers/memory_transfer.hh"
#include "drivers/pin.hh"
#include "drivers/screen_ST77XX.hh"
#include "drivers/spi.hh"
#include "drivers/spi_dma_datacmd_driver.hh"
#include "drivers/stm32xx.h"

#include "examples/hardware-tests/memory_transfer_test.hh"
#include <span>

using namespace mdrivlib;

namespace MetaModule
{
// TODO: Make this class more general so it can be part of mdrivlib
//  template <typename ScreenWriterConfT>
using ScreenWriterConfT = MMScreenConf;
class ScreenFrameWriter : public mdrivlib::SpiDmaDataCmdDriver<ScreenWriterConfT, ScreenTransferDriverT> {
	static constexpr uint32_t FrameSize = ScreenWriterConfT::FrameBytes;
	static constexpr uint32_t HalfFrameSize = ScreenWriterConfT::HalfFrameBytes;

	//Transfer mode:
	//*DoubleBuffer modes copy the buffer using MDMA or BDMA, and then transfer the copy via DMA+SPI
	//*Direct modes just use SPI+DMA
	//PartialFrame means the transferred region is variable sized
	enum TransferMode { Unknown, HalfFrameDoubleBuffer, FullFrameDoubleBuffer, FullFrameDirect, PartialFrameDirect };
	TransferMode mode{Unknown};

	uint32_t dst_addr;
	void *dst;
	void *src;
	void *src_2nd_half;

public:
	// Half frame buffer transfer mode
	ScreenFrameWriter(ScreenWriterConfT::FrameBufferT *readbuf_,
					  ScreenWriterConfT::HalfFrameBufferT *writebuf_,
					  size_t writebuffer_size)
		: mode{HalfFrameDoubleBuffer}
		, dst_addr{reinterpret_cast<uint32_t>(writebuf_)}
		, dst{reinterpret_cast<void *>(writebuf_)}
		, src{reinterpret_cast<void *>(readbuf_->data())}
		, src_2nd_half{reinterpret_cast<void *>((uint32_t)(&readbuf_[0]) + HalfFrameSize)}
		, _rowstart{ScreenWriterConfT::rowstart}
		, _colstart{ScreenWriterConfT::colstart} {
	}

	// Full frame buffer mode
	ScreenFrameWriter(ScreenWriterConfT::FrameBufferT *readbuf_,
					  ScreenWriterConfT::FrameBufferT *writebuf_,
					  size_t writebuffer_size)
		: mode{FullFrameDoubleBuffer}
		, dst_addr{reinterpret_cast<uint32_t>(writebuf_)}
		, dst{reinterpret_cast<void *>(writebuf_->data())}
		, src{reinterpret_cast<void *>(readbuf_->data())}
		, src_2nd_half{src}
		, _rowstart{ScreenWriterConfT::rowstart}
		, _colstart{ScreenWriterConfT::colstart}

	{
	}

	// Direct transfer mode
	ScreenFrameWriter(ScreenWriterConfT::FrameBufferT *readbuf_, size_t writebuffer_size)
		: mode{FullFrameDirect}
		, src{reinterpret_cast<void *>(readbuf_->data())}
		, src_2nd_half{src}
		, _rowstart{ScreenWriterConfT::rowstart}
		, _colstart{ScreenWriterConfT::colstart} {
	}

	// Direct Partial transfer mode
	ScreenFrameWriter()
		: mode{PartialFrameDirect}
		, _rowstart{ScreenWriterConfT::rowstart}
		, _colstart{ScreenWriterConfT::colstart} {
	}

	void reinit() {
		SpiDmaDataCmdDriver<ScreenWriterConfT, ScreenTransferDriverT>::reinit();
	}

	void init() {
		SpiDmaDataCmdDriver<ScreenWriterConfT, ScreenTransferDriverT>::init();
		reset();
		using InitCommands =
			mdrivlib::ST77XX::ST7789Init<ScreenWriterConfT::width,
										 ScreenWriterConfT::height,
										 ScreenWriterConfT::IsInverted ? ST77XX::Inverted : ST77XX::NotInverted>;
		init_display_driver(InitCommands::cmds);
		set_rotation(ScreenWriterConfT::rotation);

		////TESTS:
		// HardwareExample::MemoryTransferByteSwapTest::run(src, dst, FrameSize);
		// Debug::Pin2::high();
		// set_pos(0, 0, _width - 1, _height - 1);
		// for (uint32_t pix = 0; pix < (_width * _height / 2); pix++)
		// 	transmit_blocking<Data>(0x0700, 0x0700);
		// Debug::Pin2::low();
		/////
	}

	//TODO: incorporate the MADCTL stuff in ST7789Init
	void set_rotation(ScreenWriterConfT::Rotation rot) {
		_rotation = rot;

		uint8_t madctl = 0;
		switch (_rotation) {
			case ScreenWriterConfT::None:
				madctl = ST77XX::MADCTL_MX | ST77XX::MADCTL_MY | ST77XX::MADCTL_RGB;
				_xstart = _colstart;
				_ystart = _rowstart;
				_width = ScreenWriterConfT::width;
				_height = ScreenWriterConfT::height;
				break;
			case ScreenWriterConfT::CW90:
				madctl = ST77XX::MADCTL_MY | ST77XX::MADCTL_MV | ST77XX::MADCTL_RGB;
				_xstart = _rowstart;
				_ystart = _colstart;
				_height = ScreenWriterConfT::width;
				_width = ScreenWriterConfT::height;
				break;
			case ScreenWriterConfT::Flip180:
				madctl = ST77XX::MADCTL_RGB;
				_xstart = 0;
				_ystart = 0;
				_width = ScreenWriterConfT::width;
				_height = ScreenWriterConfT::height;
				break;
			case ScreenWriterConfT::CCW90:
				madctl = ST77XX::MADCTL_MX | ST77XX::MADCTL_MV | ST77XX::MADCTL_RGB;
				_xstart = 0;
				_ystart = 0;
				_height = ScreenWriterConfT::width;
				_width = ScreenWriterConfT::height;
				break;
		}
		transmit_blocking<Cmd>(ST77XX::MADCTL);
		transmit_blocking<Data>(madctl);
	}

	void transfer_buffer_to_screen() {
		if (mode == HalfFrameDoubleBuffer) {
			//Total setup times = 12.5+1.6+12.5+1.6 = 28.2us, every 16Hz (or 33Hz) = <0.1 %
			// Debug::Pin5::high(); // time to setup the first mem_xfer = 12-13us
			HWSemaphore<ScreenFrameWriteLock>::lock();

			set_pos(0, 0, _width - 1, _height - 1);
			mem_xfer.config_transfer(dst, src, HalfFrameSize);

			// Debug::Pin2::high(); // start MDMA xfer #1
			mem_xfer.register_callback([&]() {
				// Debug::Pin4::high(); // time to setup the SPI transfer = 1.6us, starting 180us after first mem_xfer
				// Debug::Pin2::low(); // completed MDMA xfer#1
				// Debug::Pin3::high(); // start BDMA transfer #1
				config_dma_transfer(dst_addr, HalfFrameSize);
				start_dma_transfer([&]() {
					// Debug::Pin5::high(); //time to setup mem_xfer = 12-13us, starting 12ms after first SPI transfer
					// Debug::Pin3::low(); // completed BDMA xfer #1

					//Start transferring the second half:
					// set_pos(0, _height / 2, _width - 1, _height - 1);
					mem_xfer.config_transfer(dst, src_2nd_half, HalfFrameSize);

					// Debug::Pin2::high(); // start MDMA xfer #2
					mem_xfer.register_callback([&]() {
						// Debug::Pin4::high(); //time to setup second SPI transfer = 1.6us, starting 180us after mem_xfer
						// Debug::Pin2::low();	 // completed MDMA xfer #2
						// Debug::Pin3::high(); // start BDMA xfer #2
						config_dma_transfer(dst_addr, HalfFrameSize);
						start_dma_transfer([&]() {
							// Debug::Pin3::low(); // completed BDMA xfer #3
							HWSemaphore<ScreenFrameWriteLock>::unlock();
						});
						// Debug::Pin4::low(); //end setup measurement
					});
					mem_xfer.start_transfer();
					// Debug::Pin5::low(); //end setup measurement
				});
				// Debug::Pin4::low(); //end setup measurement
			});
			mem_xfer.start_transfer();
			// Debug::Pin5::low(); //end setup measurement

		} else if (mode == FullFrameDoubleBuffer) {
			HWSemaphore<ScreenFrameWriteLock>::lock();
			set_pos(0, 0, _width - 1, _height - 1);

			// Setup transfer from mem-to-mem destination (dst_addr) to the SPI peripheral
			config_dma_transfer(dst_addr, FrameSize);

			// Setup the mem-to-mem transfer
			mem_xfer.config_transfer(dst, src, FrameSize);
			mem_xfer.register_callback(
				[&] { start_dma_transfer([]() { HWSemaphore<ScreenFrameWriteLock>::unlock(); }); });
			mem_xfer.start_transfer();

		} else if (mode == FullFrameDirect) {
			HWSemaphore<ScreenFrameWriteLock>::lock();
			set_pos(0, 0, _width - 1, _height - 1);
			config_dma_transfer(reinterpret_cast<uint32_t>(src), FrameSize);
			start_dma_transfer([] { HWSemaphore<ScreenFrameWriteLock>::unlock(); });
		}
	}

	void register_partial_frame_cb(auto cb) {
		register_callback(cb);
	}

	//~110us, as needed, typically 2.5ms spaced
	void transfer_partial_frame(int xstart, int ystart, int xend, int yend, uint16_t *buffer) {
		set_pos(xstart, ystart, xend, yend);
		auto buffer_size_bytes = (xend - xstart + 1) * (yend - ystart + 1) * 2;
		config_dma_transfer(reinterpret_cast<uint32_t>(buffer), buffer_size_bytes);
		mdrivlib::SystemCache::clean_dcache_by_range(buffer, buffer_size_bytes);
		__DSB();

		start_dma_transfer();
	}

	void reset() {
		Pin reset_pin{ScreenWriterConfT::ResetPin, PinMode::Output};
		reset_pin.high();
		HAL_Delay(1);
		reset_pin.low();
		HAL_Delay(10);
		reset_pin.high();
		HAL_Delay(120);
	}

protected:
	const int _rowstart;
	const int _colstart;
	ScreenWriterConfT::Rotation _rotation;
	int _xstart;
	int _ystart;
	int _width;
	int _height;

	struct ScreenMemXferConfT : mdrivlib::MemoryTransferDefaultConfT {
		static constexpr unsigned channel = 0;
		static constexpr bool swap_bytes = false;
		static constexpr bool bufferable_write_mode = true;
		static constexpr uint32_t PriorityLevel = Medium;
		static constexpr uint32_t src_burst = 0b100;
		static constexpr uint32_t dst_burst = 0b100;
	};
	mdrivlib::MemoryTransfer<ScreenMemXferConfT> mem_xfer;

	void set_pos(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend) {
		Xstart += _xstart;
		Ystart += _ystart;
		Xend += _xstart;
		Yend += _ystart;
		transmit_blocking<Cmd>(ST77XX::CASET);
		transmit_blocking<Data>(Xstart, Xend);

		transmit_blocking<Cmd>(ST77XX::RASET);
		transmit_blocking<Data>(Ystart, Yend);

		transmit_blocking<Cmd>(ST77XX::RAMWR);
	}

	void init_display_driver(std::span<const ScreenInitCommand> cmds) {
		for (auto &c : cmds) {
			transmit_blocking<Cmd>(c.cmd);
			for (int i = 0; i < c.num_args; i++) {
				transmit_blocking<Data>(c.args[i]);
			}
			if (c.delay_ms)
				HAL_Delay(c.delay_ms);
		}
	}
};
} // namespace MetaModule
