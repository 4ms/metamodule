#pragma once
#include "conf/screen_conf.hh"
#include "drivers/memory_transfer.hh"
#include "drivers/pin.hh"
#include "drivers/spi.hh"
#include "drivers/spi_screen_ST77XX.hh"
#include "drivers/spi_screen_driver.hh"
#include "drivers/stm32xx.h"
#include "drivers/system.hh"

using ScreenConfT = MMScreenConf;

// template <typename ScreenConfT>
class ScreenFrameWriter : public DmaSpiScreenDriver<ScreenConfT> {
	ScreenConfT::FrameBufferT *framebuf;
	static constexpr uint32_t FrameSize = sizeof(ScreenConfT::FrameBufferT);
	static constexpr uint32_t HalfFrameSize = sizeof(ScreenConfT::FrameBufferT) / 2;

	void *writebuffer;
	uint32_t writebuffer_size;

public:
	ScreenFrameWriter(ScreenConfT::FrameBufferT *framebuf_, void *writebuffer, size_t writebuffer_size)
		: framebuf{framebuf_}
		, writebuffer{writebuffer}
		, writebuffer_size{writebuffer_size}
		, _rowstart{ScreenConfT::rowstart}
		, _colstart{ScreenConfT::colstart}
	{}

	void init()
	{
		DmaSpiScreenDriver<ScreenConfT>::init();
		init_display(generic_st7789);
		set_rotation(1); // ScreenConfT::rotation
	}

	void set_rotation(uint8_t m)
	{
		uint8_t madctl = 0;

		_rotation = m & 3;

		switch (_rotation) {
			case 0:
				madctl = ST77XX::MADCTL_MX | ST77XX::MADCTL_MY | ST77XX::MADCTL_RGB;
				_xstart = _colstart;
				_ystart = _rowstart;
				_width = ScreenConfT::width;
				_height = ScreenConfT::height;
				break;
			case 1:
				madctl = ST77XX::MADCTL_MY | ST77XX::MADCTL_MV | ST77XX::MADCTL_RGB;
				_xstart = _rowstart;
				_ystart = _colstart;
				_height = ScreenConfT::width;
				_width = ScreenConfT::height;
				break;
			case 2:
				madctl = ST77XX::MADCTL_RGB;
				_xstart = 0;
				_ystart = 0;
				_width = ScreenConfT::width;
				_height = ScreenConfT::height;
				break;
			case 3:
				madctl = ST77XX::MADCTL_MX | ST77XX::MADCTL_MV | ST77XX::MADCTL_RGB;
				_xstart = 0;
				_ystart = 0;
				_height = ScreenConfT::width;
				_width = ScreenConfT::height;
				break;
		}
		transmit_blocking<Cmd>(ST77XX::MADCTL);
		transmit_blocking<Data>(madctl);
	}

	static constexpr bool using_mdma = false;
	void transfer_buffer_to_screen()
	{
		if (!using_mdma && writebuffer_size == HalfFrameSize) {
			set_pos(0, 0, _width - 1, _height - 1);

			// mdma takes 0.6 - 3ms
			// bdma takes 4.7ms 
			// mdma takes 0.5us
			// bdma takes 4.7ms
			config_bdma_transfer(reinterpret_cast<uint32_t>(writebuffer), HalfFrameSize);
			mem_xfer.config_transfer(dst, src, HalfFrameSize);
			mem_xfer.register_callback([&]() {
				Debug::Pin1::low();
				start_bdma_transfer([&]() {
					Debug::Pin2::high();
					mem_xfer.config_transfer(dst, src2, HalfFrameSize);
					mem_xfer.register_callback([&]() {
						Debug::Pin2::low();
						Debug::Pin1::high();
						start_bdma_transfer([&]() { Debug::Pin1::low(); });
					});
					mem_xfer.start_transfer();
				});
			});
			Debug::Pin1::high();
			mem_xfer.start_transfer();
			return;
		}
		// if (using_mdma && writebuffer_size == HalfFrameSize) {
		// 	Debug::Pin1::high();
		// 	set_pos(0, 0, _width - 1, _height - 1);

		// 	// memcpy(writebuffer, (void *)(&framebuf[0]), HalfFrameSize);

		// 	config_bdma_transfer(reinterpret_cast<uint32_t>(writebuffer), HalfFrameSize);
		// 	start_bdma_transfer([&]() {
		// 		Debug::Pin1::low();
		// 		// memcpy(writebuffer, (void *)((uint32_t)(&framebuf[0]) + HalfFrameSize), HalfFrameSize);
		// 		Debug::Pin2::high();
		// 		config_bdma_transfer(reinterpret_cast<uint32_t>(writebuffer), HalfFrameSize);
		// 		start_bdma_transfer([&]() { Debug::Pin2::low(); });
		// 	});
		// 	return;
		// }
		// if (writebuffer_size == FrameSize) {
		// 	// Todo: test full buffer xfer
		// 	set_pos(0, 0, _width - 1, _height - 1);

		// 	// memcpy(writebuffer, (void *)(&framebuf[0]), FrameSize);

		// 	config_bdma_transfer(reinterpret_cast<uint32_t>(writebuffer), FrameSize);
		// 	start_bdma_transfer([]() {});
		// 	return;
		// }
	}
	// init_mdma([&]() {
	// 	wait_until_ready();
	// 	// Debug::Pin1::low();
	// 	// set_pos(0, 120, 240, 240);
	// 	// Debug::Pin2::high();
	// 	// init_mdma([&]() { Debug::Pin2::low(); });
	// 	// start_dma_transfer(0x24000000 + sizeof(ScreenConfT::FrameBufferT) / 2,
	// 	// 				   sizeof(ScreenConfT::FrameBufferT) / 2);
	// });
	// start_dma_transfer(0x24000000, sizeof(ScreenConfT::FrameBufferT) / 2);

protected:
	const int _colstart;
	const int _rowstart;
	int _rotation;
	int _xstart;
	int _ystart;
	int _width;
	int _height;

	void *dst = reinterpret_cast<void *>(writebuffer);
	void *src = reinterpret_cast<void *>(&framebuf[0]);
	void *src2 = reinterpret_cast<void *>((uint32_t)(&framebuf[0]) + HalfFrameSize);
	MemoryTransfer mem_xfer;
	MemoryTransfer mem_xfer2;

	void set_pos(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend)
	{
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

	// Todo re-write as just a sequence of commands with delays
	// Make a fake transmit_blocking<>(uint8_t) and fake HAL_Delay() to record results
	void init_display(const uint8_t *addr)
	{
		uint8_t numCommands, cmd, numArgs;
		uint16_t ms;

		numCommands = *addr++;					 // Number of commands to follow
		while (numCommands--) {					 // For each command...
			cmd = *addr++;						 // Read command
			numArgs = *addr++;					 // Number of args to follow
			ms = numArgs & ST77XX::ST_CMD_DELAY; // If hibit set, delay follows args
			numArgs &= ~ST77XX::ST_CMD_DELAY;	 // Mask out delay bit
			transmit_blocking<Cmd>(cmd);
			while (numArgs--) {
				transmit_blocking<Data>(*addr++);
			}

			if (ms) {
				ms = *addr++; // Read post-command delay time (ms)
				if (ms == 255)
					ms = 500; // If 255, delay for 500 ms
				HAL_Delay(ms);
			}
		}
	}
};
