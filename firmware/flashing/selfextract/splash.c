// Boot-splash for the self-extract stub: blank the screen and draw a centered
// bitmap over SPI4 before the firmware is decompressed.
//
// The panel is an ST7789 (240x320, RGB565) wired to SPI4 exactly as the app
// configures it in src/medium/conf/screen_conf.hh:
//   SPI4: SCLK=PE12/AF5, COPI=PE6/AF5, NSS=PE11/AF5 (hardware SS, pulse mode)
//   DC   = PB7 (output, low=command / high=data)
//   RESET= PC4 (output, active low)
// Mode 0, MSB-first, TX-only, 8-bit frames, baud = fPCLK2/2.
//
// This runs with the MMU on (peripherals are mapped Device, stub DDR is
// cacheable Normal), so plain volatile register writes and aligned reads from
// the const logo array are safe. It uses no .bss and no 64-bit division, so it
// stays self-contained (the linker asserts SIZEOF(.bss)==0 and we link without
// libgcc). See flashing/selfextract/stub.c for where splash_show() is called.
//
// The whole panel is streamed once: black everywhere, with the logo composited
// into the centered rectangle. The application later re-resets and re-inits the
// panel from scratch, so nothing here needs to survive the hand-off.

#include <stdint.h>
#include "splash_logo.h"

// ---- Peripheral addresses (STM32MP157, Cortex-A7 view) ---------------------
#define RCC_BASE 0x50000000u
#define RCC_SPI45CKSELR (RCC_BASE + 0x8E0u) // SPI45SRC[2:0], 0 = pclk2
// Peripheral clock enables exist per power domain. The stub runs on the A7, so
// the MPU-domain bank (MP_*) is the one that matters; we also set the MCU-domain
// bank (MC_*) so the clock stays gated on regardless of domain state. Bit
// positions are identical in both banks: SPI4EN=9, GPIOB/C/E EN=1/2/4.
#define RCC_MP_APB2ENSETR (RCC_BASE + 0xA08u) // MPU (A7)
#define RCC_MP_AHB4ENSETR (RCC_BASE + 0xA28u)
#define RCC_MC_APB2ENSETR (RCC_BASE + 0xA88u) // MCU (M4)
#define RCC_MC_AHB4ENSETR (RCC_BASE + 0xAA8u)

#define GPIOB_BASE 0x50003000u
#define GPIOC_BASE 0x50004000u
#define GPIOE_BASE 0x50006000u
#define SPI4_BASE 0x44005000u

// GPIO register offsets
#define GPIO_MODER 0x00u
#define GPIO_OTYPER 0x04u
#define GPIO_OSPEEDR 0x08u
#define GPIO_PUPDR 0x0Cu
#define GPIO_BSRR 0x18u
#define GPIO_AFRL 0x20u
#define GPIO_AFRH 0x24u

// SPI (H7/MP1 SPIv2) register offsets
#define SPI_CR1 0x00u
#define SPI_CR2 0x04u
#define SPI_CFG1 0x08u
#define SPI_CFG2 0x0Cu
#define SPI_SR 0x14u
#define SPI_IFCR 0x18u
#define SPI_TXDR 0x20u

#define SPI_CR1_SPE (1u << 0)
#define SPI_CR1_CSTART (1u << 9)
#define SPI_SR_TXP (1u << 1)
#define SPI_SR_TXC (1u << 12)
#define SPI_IFCR_EOTC (1u << 3)
#define SPI_IFCR_TXTFC (1u << 4)

// Computed once from screen_conf.hh (see file header): 8-bit, FTHLV=1;
// TX-only, master, mode 0, MSB-first, MBR=0, hardware NSS + SSOM pulse, AFCNTR.
#define SPI_CFG1_INIT 0x00000027u
#define SPI_CFG2_INIT 0xE0420000u

// ST7789 command opcodes
#define ST_SWRESET 0x01
#define ST_SLPOUT 0x11
#define ST_INVOFF 0x20
#define ST_NORON 0x13
#define ST_DISPON 0x29
#define ST_CASET 0x2A
#define ST_RASET 0x2B
#define ST_RAMWR 0x2C
#define ST_COLMOD 0x3A
#define ST_MADCTL 0x36

// Effective view geometry after CW90 rotation (matches the running app)
#define VIEW_W 320u
#define VIEW_H 240u
#define MADCTL_CW90 0xA0u // MY | MV | RGB
#define BG_COLOR 0x0000u  // black

static inline void reg_write(uint32_t addr, uint32_t val) {
	*(volatile uint32_t *)addr = val;
}
static inline uint32_t reg_read(uint32_t addr) {
	return *(volatile uint32_t *)addr;
}

// ---- Delay -----------------------------------------------------------------
// Prefer the ARM generic timer (accurate, independent of CPU clock). If the
// system counter is not running we fall back to a bounded CPU spin, so this can
// never hang and never under-delays the ST7789 reset/init timings.
static inline uint32_t read_cntfrq(void) {
	uint32_t f;
	__asm__ volatile("mrc p15, 0, %0, c14, c0, 0" : "=r"(f));
	return f;
}
static inline uint64_t read_cntpct(void) {
	uint32_t lo, hi;
	__asm__ volatile("isb\n\tmrrc p15, 0, %0, %1, c14" : "=r"(lo), "=r"(hi));
	return ((uint64_t)hi << 32) | lo;
}
static void delay_ms(uint32_t ms) {
	uint32_t f = read_cntfrq();
	if (f >= 1000u) {
		uint32_t per_ms = f / 1000u;			   // 32-bit divide by constant
		uint64_t target = (uint64_t)ms * per_ms;   // 32x32->64, inline umull
		uint64_t start = read_cntpct();
		uint32_t safety = ms * 4000000u + 4000000u; // bound if counter is dead
		while ((read_cntpct() - start) < target) {
			if (safety-- == 0)
				return;
		}
		return;
	}
	// Fallback: >=1 cycle/iter at <=800 MHz guarantees at least ms.
	volatile uint32_t c = ms * 800000u;
	while (c) {
		c = c - 1;
		__asm__ volatile("nop");
	}
}

// ---- GPIO helpers ----------------------------------------------------------
static void gpio_set_alt(uint32_t port, uint32_t pin, uint32_t af) {
	uint32_t m = reg_read(port + GPIO_MODER);
	m &= ~(0x3u << (pin * 2));
	m |= (0x2u << (pin * 2)); // alternate function
	reg_write(port + GPIO_MODER, m);

	uint32_t s = reg_read(port + GPIO_OSPEEDR);
	s |= (0x3u << (pin * 2)); // very high speed
	reg_write(port + GPIO_OSPEEDR, s);

	uint32_t afr_off = (pin < 8) ? GPIO_AFRL : GPIO_AFRH;
	uint32_t shift = (pin & 7u) * 4u;
	uint32_t a = reg_read(port + afr_off);
	a &= ~(0xFu << shift);
	a |= (af << shift);
	reg_write(port + afr_off, a);
}
static void gpio_set_output(uint32_t port, uint32_t pin) {
	uint32_t m = reg_read(port + GPIO_MODER);
	m &= ~(0x3u << (pin * 2));
	m |= (0x1u << (pin * 2)); // general-purpose output
	reg_write(port + GPIO_MODER, m);
}
static inline void gpio_write(uint32_t port, uint32_t pin, int high) {
	reg_write(port + GPIO_BSRR, high ? (1u << pin) : (1u << (pin + 16)));
}

// DC = PB7, RESET = PC4
#define DC_HIGH() gpio_write(GPIOB_BASE, 7, 1)
#define DC_LOW() gpio_write(GPIOB_BASE, 7, 0)
#define RESET_HIGH() gpio_write(GPIOC_BASE, 4, 1)
#define RESET_LOW() gpio_write(GPIOC_BASE, 4, 0)

// ---- SPI4 transfers --------------------------------------------------------
// One CS-framed transfer of `nframes` 8-bit frames, mirroring the app's proven
// finite-TSIZE + wait-TXC path (target/stm32mp1/drivers/spi.hh). DC selects
// command (low) vs data (high) and is set before any byte clocks out. NSS
// deasserts when the chunk completes; the ST7789 tolerates that mid-RAMWR
// because no command is sent between consecutive data chunks. Each TXDR access
// is an 8-bit write, packing one byte into the FIFO.
static void spi_chunk_begin(uint32_t nframes, int is_data) {
	reg_write(SPI4_BASE + SPI_CR1, reg_read(SPI4_BASE + SPI_CR1) & ~SPI_CR1_SPE);
	reg_write(SPI4_BASE + SPI_IFCR, SPI_IFCR_EOTC | SPI_IFCR_TXTFC);
	reg_write(SPI4_BASE + SPI_CR2, nframes); // TSIZE
	reg_write(SPI4_BASE + SPI_CR1, reg_read(SPI4_BASE + SPI_CR1) | SPI_CR1_SPE);
	if (is_data)
		DC_HIGH();
	else
		DC_LOW();
	reg_write(SPI4_BASE + SPI_CR1, reg_read(SPI4_BASE + SPI_CR1) | SPI_CR1_CSTART);
}
static inline void spi_push(uint8_t byte) {
	while (!(reg_read(SPI4_BASE + SPI_SR) & SPI_SR_TXP))
		;
	*(volatile uint8_t *)(SPI4_BASE + SPI_TXDR) = byte;
}
static void spi_chunk_end(void) {
	while (!(reg_read(SPI4_BASE + SPI_SR) & SPI_SR_TXC)) // transmission complete
		;
	reg_write(SPI4_BASE + SPI_CR1, reg_read(SPI4_BASE + SPI_CR1) & ~SPI_CR1_SPE);
}

static void write_cmd(uint8_t cmd) {
	spi_chunk_begin(1, 0);
	spi_push(cmd);
	spi_chunk_end();
}
static void write_data1(uint8_t d) {
	spi_chunk_begin(1, 1);
	spi_push(d);
	spi_chunk_end();
}

// ---- Panel bring-up + draw -------------------------------------------------
static void spi_gpio_init(void) {
	// Enable peripheral clocks (set-only registers, no read-modify-write).
	reg_write(RCC_MP_AHB4ENSETR, (1u << 1) | (1u << 2) | (1u << 4)); // GPIOB/C/E (A7)
	reg_write(RCC_MP_APB2ENSETR, (1u << 9));						// SPI4 (A7)
	reg_write(RCC_MC_AHB4ENSETR, (1u << 1) | (1u << 2) | (1u << 4)); // GPIOB/C/E (M4)
	reg_write(RCC_MC_APB2ENSETR, (1u << 9));						// SPI4 (M4)
	reg_write(RCC_SPI45CKSELR, 0);								   // SPI4 kernel clk = pclk2
	(void)reg_read(RCC_MP_APB2ENSETR);							   // ensure clocks settle

	gpio_set_alt(GPIOE_BASE, 12, 5); // SCLK
	gpio_set_alt(GPIOE_BASE, 6, 5);  // COPI
	gpio_set_alt(GPIOE_BASE, 11, 5); // NSS
	gpio_set_output(GPIOB_BASE, 7);  // DC
	gpio_set_output(GPIOC_BASE, 4);  // RESET

	// Configure SPI4 while disabled, then enable happens per-transfer.
	reg_write(SPI4_BASE + SPI_CR1, 0);
	reg_write(SPI4_BASE + SPI_CFG1, SPI_CFG1_INIT);
	reg_write(SPI4_BASE + SPI_CFG2, SPI_CFG2_INIT);
}

static void panel_reset(void) {
	RESET_HIGH();
	delay_ms(1);
	RESET_LOW();
	delay_ms(10);
	RESET_HIGH();
	delay_ms(120);
}

static void panel_init(void) {
	write_cmd(ST_SWRESET);
	delay_ms(150);
	write_cmd(ST_SLPOUT);
	delay_ms(10);
	write_cmd(ST_COLMOD);
	write_data1(0x55); // 16-bit/pixel RGB565
	delay_ms(10);
	write_cmd(ST_MADCTL);
	write_data1(MADCTL_CW90);
	write_cmd(ST_INVOFF);
	delay_ms(10);
	write_cmd(ST_NORON);
	delay_ms(10);
	write_cmd(ST_DISPON);
	delay_ms(10);
}

static void set_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
	write_cmd(ST_CASET);
	spi_chunk_begin(4, 1);
	spi_push(x0 >> 8);
	spi_push(x0 & 0xFF);
	spi_push(x1 >> 8);
	spi_push(x1 & 0xFF);
	spi_chunk_end();

	write_cmd(ST_RASET);
	spi_chunk_begin(4, 1);
	spi_push(y0 >> 8);
	spi_push(y0 & 0xFF);
	spi_push(y1 >> 8);
	spi_push(y1 & 0xFF);
	spi_chunk_end();

	write_cmd(ST_RAMWR);
}

// Stream the whole 320x240 view: black, with the logo in the centered box.
// Pixels go out row-major (x fastest), matching the app's framebuffer order.
static void draw(void) {
	const uint32_t lx0 = (VIEW_W - SPLASH_LOGO_W) / 2;
	const uint32_t ly0 = (VIEW_H - SPLASH_LOGO_H) / 2;

	set_window(0, 0, VIEW_W - 1, VIEW_H - 1);

	// One CS-framed chunk per row (VIEW_W pixels = VIEW_W*2 byte-frames, well
	// under the 0xFFFF TSIZE limit). No command is sent between rows, so the
	// ST7789 keeps advancing its RAMWR write pointer across the NSS pulses.
	for (uint32_t y = 0; y < VIEW_H; y++) {
		spi_chunk_begin(VIEW_W * 2, 1);
		for (uint32_t x = 0; x < VIEW_W; x++) {
			uint16_t c = BG_COLOR;
			if (x >= lx0 && x < lx0 + SPLASH_LOGO_W && y >= ly0 && y < ly0 + SPLASH_LOGO_H)
				c = splash_logo[(y - ly0) * SPLASH_LOGO_W + (x - lx0)];
			spi_push((uint8_t)(c >> 8));
			spi_push((uint8_t)(c & 0xFF));
		}
		spi_chunk_end();
	}
}

void splash_show(void) {
	spi_gpio_init();
	panel_reset();
	panel_init();
	draw();
}
