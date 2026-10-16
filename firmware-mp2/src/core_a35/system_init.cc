#include "conf/rcc_conf.hh"
#include "drivers/pwr_vdd.hh"
#include "drivers/rcc_pll.hh"

extern "C" {
uint32_t SystemCoreClock = 1'500'000'000; // PLL1 is set by TF-A
}

// Called by startup_ca35.s just before main()
extern "C" void system_init() {
	using namespace MetaModule;
	using namespace mdrivlib;

	// I/O supply isolation (RM0457 19.4.9). All four rails are always-on on the mp2-devboard:
	PowerControl::enable_vddio1(PowerControl::Present::Always); // PE[5:0]: SDMMC1 (PMIC LDO8)
	PowerControl::enable_vddio2(PowerControl::Present::Always); // PE[15:6]: SAI1, FUSB_INT (+1V8!)
	PowerControl::enable_vddio3(PowerControl::Present::Always); // PD[11:0]: I2C4, codec reset
	PowerControl::enable_vddio4(PowerControl::Present::Always); // PB[11:0]: I2C2, expander INTs, console

	RCC_Clocks::set_pll<RCC_Clocks::PLL8>(RccConf::AudioPLL8);

	auto sai1 = RccConf::SAI1_KernelClock;
	sai1.init(RccConf::SAI1_FlexgenChan);

	auto i2c = RccConf::I2C_KernelClock;
	i2c.init(RccConf::I2C1_2_FlexgenChan);
	i2c.init(RccConf::I2C3_5_FlexgenChan);
	i2c.init(RccConf::I2C4_6_FlexgenChan);
}
