#pragma once
#include "conf/screen_conf.hh"
#include "drivers/memory_transfer.hh"
#include "drivers/pin.hh"
#include "drivers/spi.hh"
#include "drivers/spi_screen_ST77XX.hh"
#include "drivers/spi_screen_driver.hh"
#include "drivers/stm32xx.h"
#include "drivers/system.hh"

using namespace mdrivlib;
using ScreenConfT = MMScreenConf;

// template <typename ScreenConfT>
class ScreenFrameWriter : public DmaSpiScreenDriver<ScreenConfT> {
	static constexpr uint32_t FrameSize = ScreenConfT::FrameBytes;
	static constexpr uint32_t HalfFrameSize = ScreenConfT::HalfFrameBytes;

	bool using_half_buffer_transfers;

	uint32_t dst_addr;
	void *dst;
	void *src;
	void *src_2nd_half;

public:
	ScreenFrameWriter(ScreenConfT::FrameBufferT *readbuf_,
					  ScreenConfT::HalfFrameBufferT *writebuf_,
					  size_t writebuffer_size)
		: using_half_buffer_transfers{true}
		, dst_addr{reinterpret_cast<uint32_t>(writebuf_)}
		, dst{reinterpret_cast<void *>(writebuf_)}
		, src{reinterpret_cast<void *>(readbuf_->data())}
		, src_2nd_half{reinterpret_cast<void *>((uint32_t)(&readbuf_[0]) + HalfFrameSize)}
		, _rowstart{ScreenConfT::rowstart}
		, _colstart{ScreenConfT::colstart}
	{}

	ScreenFrameWriter(ScreenConfT::FrameBufferT *readbuf_,
					  ScreenConfT::FrameBufferT *writebuf_,
					  size_t writebuffer_size)
		: using_half_buffer_transfers{false}
		, dst_addr{reinterpret_cast<uint32_t>(writebuf_)}
		, dst{reinterpret_cast<void *>(writebuf_)}
		, src{reinterpret_cast<void *>(readbuf_->data())}
		, src_2nd_half{src}
		, _rowstart{ScreenConfT::rowstart}
		, _colstart{ScreenConfT::colstart}
	{}

	void init()
	{
		DmaSpiScreenDriver<ScreenConfT>::init();
		init_display(generic_st7789);
		set_rotation(ScreenConfT::rotation);
	}

	void set_rotation(ScreenConfT::Rotation rot)
	{
		_rotation = rot;

		uint8_t madctl = 0;
		switch (_rotation) {
			case ScreenConfT::None:
				madctl = ST77XX::MADCTL_MX | ST77XX::MADCTL_MY | ST77XX::MADCTL_RGB;
				_xstart = _colstart;
				_ystart = _rowstart;
				_width = ScreenConfT::width;
				_height = ScreenConfT::height;
				break;
			case ScreenConfT::CW90:
				madctl = ST77XX::MADCTL_MY | ST77XX::MADCTL_MV | ST77XX::MADCTL_RGB;
				_xstart = _rowstart;
				_ystart = _colstart;
				_height = ScreenConfT::width;
				_width = ScreenConfT::height;
				break;
			case ScreenConfT::Flip180:
				madctl = ST77XX::MADCTL_RGB;
				_xstart = 0;
				_ystart = 0;
				_width = ScreenConfT::width;
				_height = ScreenConfT::height;
				break;
			case ScreenConfT::CCW90:
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

	void transfer_buffer_to_screen()
	{
		if (using_half_buffer_transfers) {
			set_pos(0, 0, _width - 1, _height - 1);
			config_bdma_transfer(dst_addr, HalfFrameSize);
			mem_xfer.config_transfer(dst, src, HalfFrameSize);
			mem_xfer.register_callback([&]() {
				Debug::Pin1::low();
				start_bdma_transfer([&]() {
					Debug::Pin1::high();
					mem_xfer.config_transfer(dst, src_2nd_half, HalfFrameSize);
					mem_xfer.register_callback([&]() {
						Debug::Pin1::low();
						Debug::Pin1::high();
						start_bdma_transfer([&]() { Debug::Pin1::low(); });
					});
					mem_xfer.start_transfer();
				});
			});
			mem_xfer.start_transfer();
			Debug::Pin1::high();
		} else {
			// Todo: test full buffer xfer
			set_pos(0, 0, _width - 1, _height - 1);
			config_bdma_transfer(dst_addr, FrameSize);
			mem_xfer.config_transfer(dst, src, FrameSize);
			mem_xfer.register_callback([&]() { start_bdma_transfer([]() {}); });
			mem_xfer.start_transfer();
		}
	}

protected:
	const int _colstart;
	const int _rowstart;
	ScreenConfT::Rotation _rotation;
	int _xstart;
	int _ystart;
	int _width;
	int _height;

	struct ScreenMemXferConfT : MemoryTransferDefaultConfT {
		static constexpr unsigned channel = 0;
		static constexpr bool swap_bytes = true;
	};
	MemoryTransfer<ScreenMemXferConfT> mem_xfer;

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
