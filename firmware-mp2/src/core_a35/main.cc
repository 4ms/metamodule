// MetaModule MP2 ("pro") A35 firmware -- hardware bring-up.
//
// Boot path (all from mdrivlib target/stm32mp2_ca35): TF-A BL2 loads this image
// at 0x88000040 in EL3 secure -> boot/startup_ca35.s (stack, .bss, vectors, FPU,
// MMU+caches via system/mmu_ca35.cc, GIC init) -> system_init() (system_init.cc:
// I/O supplies, audio PLL, kernel clocks) -> main().
//
// This is a bring-up test for the MetaModule Pro p1 board, not the app:
//  1. console, then load and start the Cortex-M33, which runs patch storage (SD card, NOR flash)
//  2. probe every I2C device on the board and report present/missing
//  3. button LEDs: light each RGB button
//  4. display: the MetaModule GUI screens (SquareLine export), Main Menu showing
//  5. codec: init PCM3168 + SAI1 TDM, output a triangle wave on all 8 outs
//  6. loop: print control-expander changes (encoders/buttons) and direct GPIO controls,
//     and test FileStorageProxy (storage_test.hh): print the patch list, load a patch, list files

#include "conf/board_codec_conf.hh"
#include "conf/hsem_conf.hh"
#include "conf/console_uart_conf.hh"
#include "conf/control_expander_conf.hh"
#include "conf/i2c_conf.hh"
#include "conf/jack_sense_conf.hh"
#include "conf/led_driver_conf.hh"
#include "conf/screen_conf.hh"
#include "drivers/cache.hh"
#include "drivers/copro_control.hh"
#include "drivers/hsem.hh"
#include "drivers/inter_core_comm.hh"
#include "drivers/ipcc.hh"
#include "drivers/risaf.hh"
#include "drivers/led_driver_lp5024.hh"
#include "drivers/pin.hh"
#include "drivers/system_reg.hh"
#include "drivers/uart.hh"
#include "gui/slsexport/comp_init.hh"
#include "lvgl.h"
#include "lvgl_display.hh"
#include "patch_file/file_storage_proxy.hh"
#include "shared_index.hh"
#include "storage_test.hh"
#include <array>
#include <cstdio>

extern "C" const uint8_t m33_firmware[];	 // m33_firmware.S
extern "C" const uint8_t m33_firmware_end[]; // m33_firmware.S

namespace
{
mdrivlib::Uart<LogUartConfig> console;

// Console output is shared with the M33: lock the UART semaphore once the HSEM is up
// (before that, the M33 isn't running)
bool hsem_ready = false;

void print(const char *s) {
	using UartSem = mdrivlib::HWSemaphore<MetaModule::UartLock>;
	if (hsem_ready) {
		while (UartSem::lock(MetaModule::UartLockA7Core0) != mdrivlib::HWSemaphoreFlag::LockedOk)
			;
	}
	console.write(s);
	if (hsem_ready)
		UartSem::unlock(MetaModule::UartLockA7Core0);
}

void print_num(uint32_t v) {
	char buf[11];
	int len = 0;
	do {
		buf[len++] = '0' + (v % 10);
		v /= 10;
	} while (v);
	char out[11];
	for (int i = 0; i < len; i++)
		out[i] = buf[len - 1 - i];
	out[len] = '\0';
	print(out);
}

void print_hex(uint32_t v, unsigned digits = 2) {
	char buf[9]{};
	for (unsigned i = 0; i < digits; i++) {
		auto nibble = (v >> ((digits - 1 - i) * 4)) & 0xF;
		buf[i] = nibble < 10 ? '0' + nibble : 'A' + nibble - 10;
	}
	print(buf);
}

} // namespace

// printf() etc. output (pr_err(), pr_info(), ...)
extern "C" int _write(int, char *ptr, int len) {
	using UartSem = mdrivlib::HWSemaphore<MetaModule::UartLock>;
	if (hsem_ready) {
		while (UartSem::lock(MetaModule::UartLockA7Core0) != mdrivlib::HWSemaphoreFlag::LockedOk)
			;
	}
	for (int i = 0; i < len; i++)
		console.putchar(ptr[i]);
	if (hsem_ready)
		UartSem::unlock(MetaModule::UartLockA7Core0);
	return len;
}

namespace
{

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

// Shared with the M33 (shared_index.hh). The M33 reads files into raw_patch_data, and writes the
// patch list and dir entries into storage_list_buffer serialized (see dir_list_serial.hh).
__attribute__((section(".sharedmem"))) MetaModule::BringupIPC::Message bringup_message;
__attribute__((section(".sharedmem"))) MetaModule::IntercoreStorageMessage storage_message;
__attribute__((section(".sharedmem"))) std::array<char, 1024 * 1024> raw_patch_data;
__attribute__((section(".sharedmem"))) std::array<char, 256 * 1024> storage_list_buffer;

} // namespace

int main() {
	using namespace MetaModule;

	console.init();
	print("\n\nMetaModule Pro p1 bring-up\n");
	// Line-buffered, so lines from the two cores don't interleave
	setvbuf(stdout, nullptr, _IOLBF, 256);

	HAL_Init();

	//
	// Cortex-M33
	//
	// Park the M33 before (re)initializing the peripherals it uses
	mdrivlib::CoproController::reset();
	mdrivlib::HWSemaphoreGlobalBase::init_peripheral();
	mdrivlib::IPCC_<1>::init_peripheral();
	hsem_ready = true;

	// Shared memory: open it to the M33 in the DDR firewall, create the shared objects in
	// .sharedmem, and publish pointers to them in the index the M33 reads
	{
		using namespace mdrivlib::RISAF;
		constexpr unsigned SharedMemRegionIndex = 10;
		if (!add_ddr_region(SharedMemRegionIndex,
							SHAREDMEM_ADDR,
							SHAREDMEM_ADDR + SHAREDMEM_SIZE - 1,
							CID_A35 | CID_M33,
							CID_A35 | CID_M33,
							true))
			print("Shared memory: RISAF4 is locked, can't open it to the M33!\n");
	}
	bringup_message = {};
	storage_message = {};
	auto &index = shared_index();
	index.bringup_message = &bringup_message;
	index.storage_message = &storage_message;
	index.magic = SharedIndex::ValidMagic;

	if constexpr (M33_LOAD_ADDR >= mdrivlib::RISAF::DDRBase) {
		// TF-A's DDR region only allows CID0/CID1: open the M33's region to it (CID2)
		using namespace mdrivlib::RISAF;
		constexpr unsigned M33RegionIndex = 11;
		if (!add_ddr_region(M33RegionIndex,
							M33_LOAD_ADDR,
							M33_LOAD_ADDR + M33_REGION_SIZE - 1,
							CID_A35 | CID_M33,
							CID_A35 | CID_M33,
							true))
			print("M33: RISAF4 is locked, can't open DDR to the M33!\n");
	}

	print("M33: loading ");
	print_num(uint32_t(m33_firmware_end - m33_firmware));
	print(" bytes to 0x");
	print_hex(M33_LOAD_ADDR, 8);
	print(" and starting\n");
	mdrivlib::CoproController::load_and_start({m33_firmware, size_t(m33_firmware_end - m33_firmware)}, M33_LOAD_ADDR);
	{
		using mdrivlib::CoproController;
		auto reset_us = CoproController::wait_for_breadcrumb(M33_LOAD_ADDR, 0, CoproController::BreadcrumbResetRan, 100);
		auto main_us = CoproController::wait_for_breadcrumb(M33_LOAD_ADDR, 1, CoproController::BreadcrumbReachedMain, 1000);
		print("M33 boot breadcrumbs: reset handler ");
		if (reset_us >= 0) {
			print("ran, main() ");
			if (main_us >= 0) {
				print("reached after ");
				print_num(reset_us + main_us);
				print(" us\n");
			} else
				print("NOT REACHED\n");
		} else
			print("DID NOT RUN\n");
	}

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
		print_num(screen.refresh_rate_millihz());
		print(" mHz refresh, ");
		print_num(screen.dcs_write_errors());
		print(" DCS write errors\n");
	} else {
		print("FAILED (error ");
		print_num(static_cast<uint32_t>(screen_err));
		print(")\n");
	}

	static LvglDisplay lvgl_display;
	lvgl_display.init(framebuffer, lvgl_draw_buffer);
	lv_log_register_print_cb([](const char *msg) { print(msg); });
	// The real MetaModule screens, as the GUI's PageManager sets them up (loads the Main Menu)
	static SlsComponentInit sls_comp_init;
	print("LVGL started\n");

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

	// A35 <-> M33 messaging test (shared_index.hh): ping every second, print the reply
	using IPC = mdrivlib::InterCoreComm<mdrivlib::ICCRoleType::Initiator, BringupIPC::Message, BringupIPC::Channel>;
	static IPC ipc{bringup_message};

	// Patch storage, on the M33
	static FileStorageComm storage_comm{storage_message};
	static PatchDirList patch_dir_list;
	static FileStorageProxy file_storage{raw_patch_data, storage_comm, patch_dir_list, storage_list_buffer};
	static StorageTest storage_test{file_storage};
	uint32_t ipc_seq = 0;
	uint64_t ipc_sent_at = 0;
	uint32_t last_ipc_send = HAL_GetTick();

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

		storage_test.process();

		// A35 <-> M33 messaging
		if (auto reply = ipc.get_new_message(); reply.seq) {
			auto round_trip_us = uint32_t((mdrivlib::read_cntpct() - ipc_sent_at) * 1'000'000 / mdrivlib::read_cntfreq());
			print("IPC: sent ");
			print_num(reply.seq);
			print(reply.value == reply.seq * 2 ? ", M33 replied ok (" : ", M33 replied WRONG VALUE (");
			print_num(reply.value);
			print("), round trip ");
			print_num(round_trip_us);
			print(" us\n");
		}
		if (HAL_GetTick() - last_ipc_send >= 1000) {
			last_ipc_send = HAL_GetTick();
			ipc_sent_at = mdrivlib::read_cntpct();
			if (ipc.send_message({.seq = ++ipc_seq, .value = 0}) == false) {
				print("IPC: send ");
				print_num(ipc_seq);
				print(" skipped: M33 hasn't replied to the last one\n");
			}
		}

		delay_ms(5);
	}
}
