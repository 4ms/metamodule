// MetaModule MP2 ("pro") A35 firmware -- hardware bring-up.
//
// Boot path (all from mdrivlib target/stm32mp2_ca35): TF-A BL2 loads this image
// at 0x88000040 in EL3 secure -> boot/startup_ca35.s (stack, .bss, vectors, FPU,
// MMU+caches via system/mmu_ca35.cc, GIC init) -> system_init() (system_init.cc:
// I/O supplies, audio PLL, kernel clocks) -> main().
//
// This is a bring-up test for the MetaModule Pro p1 board, not the app:
//  1. console
//  2. probe every I2C device on the board and report present/missing
//  3. button LEDs: light each RGB button
//  4. display: the MetaModule GUI screens (SquareLine export), Main Menu showing
//  5. SD card: raw read speed, mount FatFS, list the root directory, then a write/verify test file
//  6. codec: init PCM3168 + SAI1 TDM, output a triangle wave on all 8 outs
//  7. loop: print control-expander changes (encoders/buttons) and direct GPIO controls

#include "conf/board_codec_conf.hh"
#include "conf/console_uart_conf.hh"
#include "conf/control_expander_conf.hh"
#include "conf/i2c_conf.hh"
#include "conf/jack_sense_conf.hh"
#include "conf/led_driver_conf.hh"
#include "conf/screen_conf.hh"
#include "drivers/cache.hh"
#include "drivers/led_driver_lp5024.hh"
#include "drivers/pin.hh"
#include "drivers/system_reg.hh"
#include "drivers/uart.hh"
#include "ff.h"
#include "fs/fatfs/sdcard_ops.hh"
#include "gui/slsexport/comp_init.hh"
#include "lvgl.h"
#include "lvgl_display.hh"
#include <array>

bool fatfs_register_disk(DiskOps *ops, uint8_t disk_id); // fs/fatfs/diskio.cc

namespace
{
mdrivlib::Uart<LogUartConfig> console;

void print(const char *s) {
	console.write(s);
}

void print_hex(uint32_t v, unsigned digits = 2) {
	char buf[9]{};
	for (unsigned i = 0; i < digits; i++) {
		auto nibble = (v >> ((digits - 1 - i) * 4)) & 0xF;
		buf[i] = nibble < 10 ? '0' + nibble : 'A' + nibble - 10;
	}
	console.write(buf);
}

void delay_ms(uint32_t ms) {
	auto start = mdrivlib::read_cntpct();
	auto ticks = mdrivlib::read_cntfreq() / 1000 * ms;
	while (mdrivlib::read_cntpct() - start < ticks)
		;
}

bool probe(mdrivlib::I2CPeriph &i2c, const char *bus, uint8_t addr7, const char *name) {
	bool ok = i2c.probe(addr7 << 1);
	print(ok ? "  [ok]      " : "  [MISSING] ");
	print(bus);
	print(" 0x");
	print_hex(addr7);
	print(" ");
	print(name);
	print("\n");
	return ok;
}

// Audio test: 440Hz triangle on all outputs, 6 inputs captured
constexpr uint32_t BlockSize = 256;
constexpr uint32_t NumOuts = 8;
constexpr uint32_t NumIns = 6;
alignas(64) std::array<int32_t, 2 * BlockSize * NumOuts> audio_out;
alignas(64) std::array<int32_t, 2 * BlockSize * NumIns> audio_in;
std::array<float, NumOuts> phases{};

void fill_audio_block(unsigned half) {
	constexpr float freq[NumOuts]{40.f, 100.f, 210.f, 440.f, 2000.f, 5000.f, 10000.f, 20000.f};
	auto *out = &audio_out[half * BlockSize * NumOuts];
	for (unsigned ch = 0; ch < NumOuts; ch++) {
		auto &phase = phases[ch];
		for (unsigned i = 0; i < BlockSize; i++) {
			phase += freq[ch] / 48000.f;
			if (phase >= 1.f)
				phase -= 1.f;
			// Triangle at -12dB. 24-bit samples are right-aligned in the 32-bit slot:
			// the SAI (DataSize 24) transmits bits [23:0] (same as MP1's AudioFrame::scaleOutput)
			float tri = phase < 0.5f ? (4.f * phase - 1.f) : (3.f - 4.f * phase);
			auto s = static_cast<int32_t>(tri * 0x1FFFFF);
			out[i * NumOuts + ch] = s;
		}
	}
	mdrivlib::SystemCache::clean_dcache_by_range(out, BlockSize * NumOuts * sizeof(int32_t));
}

// Display memory
__attribute__((section(".framebuffers"))) alignas(4096) std::array<uint32_t, 720 * 1280> framebuffer;
std::array<lv_color_t, 1280 * 80> lvgl_draw_buffer; // partial render buffer: 1/9 of the view

// FatFS write test: write 1MB with a position-dependent pattern, read back and verify, then delete.
// Each 32-bit word encodes its own offset, so misplaced or shifted data shows up as a mismatch.
void sd_write_test() {
	constexpr const char *path = "1:/mp2_write_test.bin";
	constexpr uint32_t ChunkWords = 16 * 1024; // 64kB
	constexpr uint32_t NumChunks = 16;		   // 1MB total
	static std::array<uint32_t, ChunkWords> chunk;

	auto pattern = [](uint32_t word_index) {
		return (word_index * 2654435761u) ^ 0xA5A5A5A5u;
	};

	print("  Write test (");
	print(path);
	print("): ");

	FIL f;
	if (auto res = f_open(&f, path, FA_CREATE_ALWAYS | FA_WRITE); res != FR_OK) {
		print("f_open for write FAILED: ");
		console.write(static_cast<uint32_t>(res));
		print("\n");
		return;
	}

	auto start = HAL_GetTick();
	for (uint32_t c = 0; c < NumChunks; c++) {
		for (uint32_t i = 0; i < ChunkWords; i++)
			chunk[i] = pattern(c * ChunkWords + i);
		UINT written = 0;
		if (auto res = f_write(&f, chunk.data(), sizeof(chunk), &written); res != FR_OK || written != sizeof(chunk)) {
			print("f_write FAILED: ");
			console.write(static_cast<uint32_t>(res));
			print("\n");
			f_close(&f);
			return;
		}
	}
	if (auto res = f_close(&f); res != FR_OK) {
		print("f_close FAILED: ");
		console.write(static_cast<uint32_t>(res));
		print("\n");
		return;
	}
	auto write_ms = HAL_GetTick() - start;

	if (auto res = f_open(&f, path, FA_READ); res != FR_OK) {
		print("f_open for read FAILED: ");
		console.write(static_cast<uint32_t>(res));
		print("\n");
		return;
	}
	start = HAL_GetTick();
	uint32_t mismatches = 0;
	uint32_t first_bad_word = 0;
	for (uint32_t c = 0; c < NumChunks; c++) {
		UINT bytes_read = 0;
		if (auto res = f_read(&f, chunk.data(), sizeof(chunk), &bytes_read); res != FR_OK || bytes_read != sizeof(chunk)) {
			print("f_read FAILED: ");
			console.write(static_cast<uint32_t>(res));
			print("\n");
			f_close(&f);
			return;
		}
		for (uint32_t i = 0; i < ChunkWords; i++) {
			if (chunk[i] != pattern(c * ChunkWords + i)) {
				if (mismatches++ == 0)
					first_bad_word = c * ChunkWords + i;
			}
		}
	}
	auto read_ms = HAL_GetTick() - start;
	f_close(&f);

	auto unlink_res = f_unlink(path);

	if (mismatches == 0) {
		print("OK. Wrote 1MB in ");
		console.write(write_ms);
		print(" ms, read back and verified in ");
		console.write(read_ms);
		print(" ms\n");
	} else {
		print("VERIFY FAILED: ");
		console.write(mismatches);
		print(" bad words, first at byte offset ");
		console.write(first_bad_word * 4);
		print("\n");
	}
	if (unlink_res != FR_OK) {
		print("  f_unlink FAILED: ");
		console.write(static_cast<uint32_t>(unlink_res));
		print("\n");
	}
}

auto &sd_card_ops() {
	using namespace MetaModule;
#ifdef MP2_TEST_CARRIER
	// Drive the common side of the detect switch low before the SD driver first reads it
	static mdrivlib::Pin detect_common{SDCardDetectCommonPin, mdrivlib::PinMode::Output};
	detect_common.low();
#endif
	static SDCardOps<SDCardConf> ops;
	return ops;
}

void sd_card_test() {
	using namespace MetaModule;

	print("SD card: ");
	auto &sd_ops = sd_card_ops();
	if (sd_ops.initialize() != 0) {
		print("no card\n");
		return;
	}

	uint32_t num_sectors = 0;
	sd_ops.ioctl(GET_SECTOR_COUNT, reinterpret_cast<uint8_t *>(&num_sectors));
	console.write(num_sectors / 2048);
	print(" MB\n");

	// Raw read speed: 1MB in 64kB reads
	static std::array<uint8_t, 64 * 1024> buf;
	constexpr uint32_t SectorsPerRead = buf.size() / 512;
	auto start = HAL_GetTick();
	for (uint32_t sector = 0; sector < 2048; sector += SectorsPerRead) {
		if (sd_ops.read(buf.data(), sector, SectorsPerRead) != RES_OK) {
			print("  Read FAILED at sector ");
			console.write(sector);
			print("\n");
			return;
		}
	}
	auto ms = HAL_GetTick() - start;
	print("  Read 1MB in ");
	console.write(ms);
	print(" ms\n");

	// FatFS: drive "1:" is the SD card (see VolToPart in fs/fatfs/diskio.cc)
	if (!fatfs_register_disk(&sd_ops, 1)) {
		print("  fatfs_register_disk FAILED\n");
		return;
	}
	static FATFS fs;
	if (auto res = f_mount(&fs, "1:", 1); res != FR_OK) {
		print("  f_mount FAILED: ");
		console.write(static_cast<uint32_t>(res));
		print("\n");
		return;
	}

	DIR dir;
	if (f_opendir(&dir, "1:/") != FR_OK) {
		print("  f_opendir FAILED\n");
		return;
	}
	print("  Root directory:\n");
	FILINFO info;
	unsigned count = 0;
	while (f_readdir(&dir, &info) == FR_OK && info.fname[0] != 0) {
		if (++count > 30) {
			print("    ...\n");
			break;
		}
		print((info.fattrib & AM_DIR) ? "    [dir] " : "    ");
		print(info.fname);
		if (!(info.fattrib & AM_DIR)) {
			print("  (");
			console.write(static_cast<uint32_t>(info.fsize));
			print(" bytes)");
		}
		print("\n");
	}
	f_closedir(&dir);

	sd_write_test();
}

} // namespace

int main() {
	using namespace MetaModule;

	console.init();
	print("\n\nMetaModule Pro p1 bring-up\n");

	HAL_Init();

	//
	// I2C device probe
	//
	print("I2C devices:\n");

	auto &codec_i2c = Hardware::i2c; // I2C4, also used by the codec driver
	probe(codec_i2c, "I2C4", JackSense::gpio_expander_conf.addr, "TCA9555 jack sense (U1212)");
	probe(codec_i2c, "I2C4", 0x22, "FUSB302 USB-C");

	// I2C2: p1 boards need the PB4/PB5 trace swap for these to respond
	mdrivlib::I2CPeriph controls_a_i2c{controls_a_i2c_conf};
	probe(controls_a_i2c, "I2C2", Controls::ExpA.chip.addr, "TCA9555 controls (U1210) [p1: needs PB4/PB5 swap bodge]");
	probe(controls_a_i2c, "I2C2", Controls::ExpB.chip.addr, "TCA9555 controls (U1211) [p1: needs PB4/PB5 swap bodge]");

	mdrivlib::I2CPeriph controls_b_i2c{controls_b_i2c_conf};
	probe(controls_b_i2c, "I2C3", Controls::ExpC.chip.addr, "TCA9555 controls (U1213)");
	probe(controls_b_i2c, "I2C3", Controls::ExpD.chip.addr, "TCA9555 controls (U1209)");

	mdrivlib::I2CPeriph led_i2c{led_i2c_conf};
	bool leds_ok[2];
	leds_ok[0] = probe(led_i2c, "I2C6", ButtonLEDs::LedChipAddr7bit[0], "LP5018 button LEDs (U5)");
	leds_ok[1] = probe(led_i2c, "I2C6", ButtonLEDs::LedChipAddr7bit[1], "LP5018 button LEDs (U8)");

	//
	// Button LEDs: cycle each button through R, G, B
	//
	mdrivlib::LP5024::Device led_chips[2]{
		{led_i2c, ButtonLEDs::led_chip_addr_8bit(0)},
		{led_i2c, ButtonLEDs::led_chip_addr_8bit(1)},
	};
	for (unsigned chip = 0; chip < 2; chip++) {
		if (leds_ok[chip])
			led_chips[chip].init();
	}

	print("Button LEDs: R, G, B on each button\n");
	for (auto led : ButtonLEDs::ButtonLeds) {
		if (!leds_ok[led.chip])
			continue;
		for (unsigned c = 0; c < 3; c++) {
			uint8_t color[3]{};
			color[c] = 0x80;
			led_chips[led.chip].set_rgb_led(led.rgb_led_id, color);
			delay_ms(100);
		}
		uint8_t off[3]{};
		led_chips[led.chip].set_rgb_led(led.rgb_led_id, off);
	}

	//
	// Display
	//
	print("Display init: ");
	static mdrivlib::DsiScreen screen{ScreenConf};
	framebuffer.fill(0xFF000000);
	screen.clean_framebuffer_cache(framebuffer.data());
	auto screen_err = screen.init(framebuffer.data());
	if (screen_err == mdrivlib::DsiScreen::Error::None) {
		print("ok, ");
		console.write(screen.refresh_rate_millihz());
		print(" mHz refresh, ");
		console.write(screen.dcs_write_errors());
		print(" DCS write errors\n");
	} else {
		print("FAILED (error ");
		console.write(static_cast<uint32_t>(screen_err));
		print(")\n");
	}

	static LvglDisplay lvgl_display;
	lvgl_display.init(framebuffer, lvgl_draw_buffer);
	lv_log_register_print_cb([](const char *msg) { print(msg); });
	// The real MetaModule screens, as the GUI's PageManager sets them up (loads the Main Menu)
	static SlsComponentInit sls_comp_init;
	print("LVGL started\n");

	//
	// SD card
	//
	sd_card_test();

	//
	// Codec + SAI: triangle wave on all outputs
	//
	print("Codec init: ");
	auto &codec = Hardware::codec;
	if (codec.init() == CodecT::CODEC_NO_ERR) {
		print("ok\n");
		// The codec only answers I2C once init() has released its reset pin
		probe(codec_i2c, "I2C4", CodecAddr7bit, "PCM3168 codec");
		fill_audio_block(0);
		fill_audio_block(1);
		codec.set_tx_buffer(std::span<int32_t>{audio_out}, BlockSize);
		codec.set_rx_buffer(std::span<int32_t>{audio_in}, BlockSize);
		// Half-transfer: DMA finished reading block 0, so refill it. Complete: same for block 1.
		codec.set_callbacks([] { fill_audio_block(1); }, [] { fill_audio_block(0); });
		codec.start();
		print("Audio started: 440Hz triangle on all outputs\n");
	} else {
		print("FAILED\n");
	}

	//
	// Controls: poll expanders and direct GPIO, print changes
	//
	mdrivlib::I2CPeriph *exp_bus[4] = {&controls_a_i2c, &controls_a_i2c, &controls_b_i2c, &controls_b_i2c};
	uint16_t last_exp[4]{};

	using namespace Controls::Direct;
	mdrivlib::Pin direct_pins[] = {
		{CtlEncA, mdrivlib::PinMode::Input, mdrivlib::PinPull::Up},
		{CtlEncB, mdrivlib::PinMode::Input, mdrivlib::PinPull::Up},
		{CtlEncBut, mdrivlib::PinMode::Input, mdrivlib::PinPull::Up},
		{NavEncA, mdrivlib::PinMode::Input, mdrivlib::PinPull::Up},
		{NavEncB, mdrivlib::PinMode::Input, mdrivlib::PinPull::Up},
		{NavEncBut, mdrivlib::PinMode::Input, mdrivlib::PinPull::Up},
		{BackBut, mdrivlib::PinMode::Input, mdrivlib::PinPull::Up},
		{GateIn1, mdrivlib::PinMode::Input, mdrivlib::PinPull::None},
		{GateIn2, mdrivlib::PinMode::Input, mdrivlib::PinPull::None},
	};
	const char *direct_names[] = {
		"CtlEncA", "CtlEncB", "CtlEncBut", "NavEncA", "NavEncB", "NavEncBut", "BackBut", "GateIn1", "GateIn2"};
	uint32_t last_direct = 0;

	uint16_t last_jacks = 0;

	print("Polling controls...\n");
	while (true) {
		for (unsigned i = 0; i < Controls::Expanders.size(); i++) {
			uint8_t data[2]{};
			auto addr = Controls::Expanders[i].chip.addr << 1;
			if (exp_bus[i]->mem_read(addr, 0x00, I2C_MEMADD_SIZE_8BIT, data, 2) != mdrivlib::I2CPeriph::I2C_NO_ERR)
				continue;
			uint16_t reading = data[0] | (data[1] << 8);
			if (reading != last_exp[i]) {
				print("Expander 0x");
				print_hex(Controls::Expanders[i].chip.addr);
				print(": 0x");
				print_hex(reading, 4);
				print("\n");
				last_exp[i] = reading;
			}
		}

		uint32_t direct = 0;
		for (unsigned i = 0; i < std::size(direct_pins); i++)
			direct |= direct_pins[i].read_raw() ? (1 << i) : 0;
		if (direct != last_direct) {
			for (unsigned i = 0; i < std::size(direct_pins); i++) {
				if ((direct ^ last_direct) & (1 << i)) {
					print(direct_names[i]);
					print((direct & (1 << i)) ? " high\n" : " low\n");
				}
			}
			last_direct = direct;
		}

		uint8_t jacks[2]{};
		if (codec_i2c.mem_read(JackSense::gpio_expander_conf.addr << 1, 0x00, I2C_MEMADD_SIZE_8BIT, jacks, 2) ==
			mdrivlib::I2CPeriph::I2C_NO_ERR)
		{
			uint16_t reading = jacks[0] | (jacks[1] << 8);
			if (reading != last_jacks) {
				print("Jack sense: 0x");
				print_hex(reading, 4);
				print("\n");
				last_jacks = reading;
			}
		}

		lv_timer_handler();

		// SD card insert/remove
		static uint32_t last_sd_check = 0;
		static uint8_t last_sd_present = 0xFF;
		if (HAL_GetTick() - last_sd_check > 500) {
			last_sd_check = HAL_GetTick();
			uint8_t present = 0;
			sd_card_ops().ioctl(MMC_GET_SDSTAT, &present);
			if (present != last_sd_present) {
				if (last_sd_present != 0xFF)
					print(present ? "SD card inserted\n" : "SD card removed\n");
				last_sd_present = present;
			}
		}

		delay_ms(5);
	}
}
