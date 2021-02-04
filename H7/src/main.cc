#include "conf/codec_sai_conf.hh"
#include "conf/i2c_conf.hh"
#include "conf/qspi_flash_conf.hh"
#include "conf/sdram_conf.hh"
#include "debug.hh"
#include "drivers/arch.hh"
#include "drivers/codec_WM8731.hh"
#include "drivers/mpu.hh"
#include "drivers/qspi_flash_driver.hh"
#include "drivers/sdram.hh"
#include "drivers/stm32xx.h"
#include "drivers/system.hh"
#include "muxed_adc.hh"
#include "shared_bus.hh"
#include "sys/system_clocks.hh"
#include "ui.hh"

namespace MetaModule
{
struct Hardware : SystemClocks, /*SDRAMPeriph,*/ Debug, SharedBus {
	Hardware()
		//: SDRAMPeriph{SDRAM_AS4C_T6_conf}
		: SharedBus{i2c_conf}
	{}

	MuxedADC potadc{SharedBus::i2c, muxed_adc_conf};
	CodecWM8731 codec{SharedBus::i2c, codec_sai_conf};
	QSpiFlash qspi{qspi_flash_conf};
} _hw;

struct StaticBuffers {
	static inline __attribute__((section(".dma_buffer"))) PCA9685DmaDriver::FrameBuffer led_frame_buffer;
	static inline __attribute__((section(".dma_buffer"))) Audio::AudioStreamBlock audio_dma_block[4];

	StaticBuffers()
	{
		target::MPU_::disable_cache_for_dma_buffer(audio_dma_block, sizeof(audio_dma_block));
		target::MPU_::disable_cache_for_dma_buffer(led_frame_buffer, sizeof(led_frame_buffer));
	}
} _sb;

} // namespace MetaModule

void main()
{
	using namespace MetaModule;

	PCA9685DmaDriver led_driver{SharedBus::i2c, kNumLedDriverChips, {}, StaticBuffers::led_frame_buffer};
	LedCtl leds{led_driver};

	__HAL_DBGMCU_FREEZE_TIM6();

	Controls controls{_hw.potadc}; //{potadc, cvadc, gpio_expander};
	Params params{controls};

	Audio audio{params, _hw.codec, StaticBuffers::audio_dma_block};

	Ui ui{params, leds};

	audio.start();
	ui.start();

	uint8_t cur_pot;
	enum I2CClients {
		Leds = 0,
		SelectPots = 1,
		ReadPots = 2,
		SelectPatchCV = 3,
		ReadPatchCV = 4,
		NUMCLIENTS,
	};
	I2CClients cur_client;

	while (1) {
		ui.update();
		if (SharedBus::i2c.is_ready()) {
			switch (cur_client) {
				case Leds:
					Debug::set_3(true);
					leds.update();
					leds.refresh();
					Debug::set_3(false);
					cur_client = SelectPots;
					break;

				case SelectPots:
					Debug::set_2(true);
					params.controls.potadc.select_channel(MuxedADC::Channel::Pots);
					cur_client = ReadPots;
					cur_pot = 0;
					params.controls.potadc.select_pot_source(cur_pot);
					Debug::set_2(false);
					break;

				case ReadPots:
					Debug::set_2(true);
					params.controls.potadc.initiate_read(MuxedADC::Channel::Pots);
					params.controls.potadc.finalize_read(MuxedADC::Channel::Pots);
					params.knobs[cur_pot] = params.controls.potadc.get_last_pot_reading(cur_pot);
					if (++cur_pot >= 8) {
						cur_client = SelectPatchCV;
						cur_pot = 0;
					}
					params.controls.potadc.select_pot_source(cur_pot);
					Debug::set_2(false);
					break;

				case SelectPatchCV:
					Debug::set_2(true);
					params.controls.potadc.select_channel(MuxedADC::Channel::PatchCV);
					cur_client = ReadPatchCV;
					Debug::set_2(false);
					break;

				case ReadPatchCV:
					Debug::set_2(true);
					params.controls.potadc.initiate_read(MuxedADC::Channel::PatchCV);
					params.controls.potadc.finalize_read(MuxedADC::Channel::PatchCV);
					params.patchcv = params.controls.potadc.get_last_cvjack_reading();
					cur_client = Leds;
					Debug::set_2(false);
					break;

				default:
					cur_client = Leds;
					break;
			}
		}
		__NOP();
	}
}

void recover_from_task_fault(void)
{
	main();
}
