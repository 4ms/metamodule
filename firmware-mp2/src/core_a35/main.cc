// MetaModule MP2 ("pro") A35 firmware -- skeleton.
//
// Boot path (all from mdrivlib target/stm32mp2_ca35): TF-A BL2 loads this image
// at 0x88000040 in EL3 secure -> boot/startup_ca35.s (stack, .bss, vectors, FPU,
// MMU+caches via system/mmu_ca35.cc, RISAB RAM grants, GIC init) -> main().
//
// Bring-up milestones (see docs/MP2-Port-Plan.md):
//  1. console + clocks (system_clocks / PLL + flexgen XBAR)
//  2. audio: PCM3168 + SAI TDM + HPDMA into StaticBuffers; patch_play headless
//  3. SD + filesystem, then the AArch64 plugin dynloader
//  4. M33 AMP + core_intercom port
//  5. LTDC + LVGL at the pro screen size + aux-core player

#include "drivers/secondary_core_control.hh"
#include "drivers/system_reg.hh"

// Early console (uart_print.c)
extern "C" void early_puts(const char *s);

// Weak hook called by startup_ca35.s just before main(): clock setup goes here
extern "C" void system_init() {
}

int main() {
	early_puts("MetaModule MP2\r\n");

	// Placeholder main loop. The generic timer runs at boot; use it as a liveness signal.
	volatile uint64_t last = mdrivlib::read_cntpct();

	while (true) {
		auto now = mdrivlib::read_cntpct();
		if (now - last > mdrivlib::read_cntfreq()) {
			last = now;
			early_puts("tick\r\n"); // once per second, proves we're alive during bring-up
		}
	}
}
