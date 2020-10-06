#include "sdram.hh"
#include "pin.hh"
#include "stm32f7xx_ll_fmc.h"
#include "stm32f7xx_ll_gpio.h"
#include "stm32xx.h"

SDRAMPeriph::SDRAMPeriph(const SDRAMConfig &sdram_defs) noexcept

	: status(HAL_ERROR)
	, defs(sdram_defs)
{
	init_gpio();
	status = init();
}

HAL_StatusTypeDef SDRAMPeriph::init()
{
	__HAL_RCC_FMC_CLK_ENABLE();

	config_timing();
	start_refresh();
	return HAL_OK;
}

void SDRAMPeriph::config_timing()
{
	auto num_to_CAS = [](uint8_t cas_latency) {
		return cas_latency == 2 ? FMC_SDRAM_CAS_LATENCY_2
								: cas_latency == 1 ? FMC_SDRAM_CAS_LATENCY_1 : FMC_SDRAM_CAS_LATENCY_3;
	};
	auto freq_to_clockdiv = [HCLK = SystemCoreClock](uint8_t freq) {
		uint32_t clockdiv = HCLK / freq;
		uint32_t rounded = clockdiv + 500000U;
		clockdiv = (uint32_t)(rounded / 1000000U);
		return clockdiv;
	};
	sdram_clock_ = SystemCoreClock / freq_to_clockdiv(defs.timing.max_freq_MHz);
	auto ns_to_hclks = [sdram_clock = sdram_clock_](uint8_t ns) { return (sdram_clock / 1000000) * ns; };

	FMC_SDRAM_TimingTypeDef SdramTiming = {
		.LoadToActiveDelay = ns_to_hclks(defs.timing.tMRD_ns),
		.ExitSelfRefreshDelay = ns_to_hclks(defs.timing.tXSR_ns),
		.SelfRefreshTime = ns_to_hclks(defs.timing.tRAS_ns),
		.RowCycleDelay = ns_to_hclks(defs.timing.tRC_ns),
		.WriteRecoveryTime = ns_to_hclks(defs.timing.tWR_ns),
		.RPDelay = ns_to_hclks(defs.timing.tRP_ns),
		.RCDDelay = ns_to_hclks(defs.timing.tRCD_ns),
	};

	FMC_SDRAM_InitTypeDef init = {
		.SDBank = FMC_SDRAM_BANK1,
		.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_8,
		.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_12,
		.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_16,
		.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4,
		.CASLatency = num_to_CAS(defs.timing.CAS_latency),
		.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE,
		.SDClockPeriod =
			freq_to_clockdiv(defs.timing.max_freq_MHz) == 2 ? FMC_SDRAM_CLOCK_PERIOD_2 : FMC_SDRAM_CLOCK_PERIOD_3,
		.ReadBurst = FMC_SDRAM_RBURST_ENABLE,
		.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_2,
	};

	FMC_SDRAM_Init(FMC_SDRAM_DEVICE, &init);
	FMC_SDRAM_Timing_Init(FMC_SDRAM_DEVICE, &SdramTiming, init.SDBank);
}

void SDRAMPeriph::start_refresh()
{
	FMC_SDRAM_CommandTypeDef cmd;

	wait_until_ready();

	// CLK ENABLE command
	cmd = {.CommandMode = FMC_SDRAM_CMD_CLK_ENABLE,
		   .CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1,
		   .AutoRefreshNumber = 2,
		   .ModeRegisterDefinition = 0};
	FMC_SDRAM_SendCommand(FMC_SDRAM_DEVICE, &cmd, 0);

	HAL_Delay(10);
	wait_until_ready();

	// All Bank Precharge command
	cmd = {.CommandMode = FMC_SDRAM_CMD_PALL,
		   .CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1,
		   .AutoRefreshNumber = 2,
		   .ModeRegisterDefinition = 0};
	FMC_SDRAM_SendCommand(FMC_SDRAM_DEVICE, &cmd, 0);
	wait_until_ready();

	// Auto-refresh command
	cmd = {.CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE,
		   .CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1,
		   .AutoRefreshNumber = 5,
		   .ModeRegisterDefinition = 0};
	FMC_SDRAM_SendCommand(FMC_SDRAM_DEVICE, &cmd, 0);
	wait_until_ready();

	// Load Mode Register
	// Todo: Calculate this constant based on defs (add new config fields if needed)
	// Mode Register = 0x231: burst length 2, burst type sequential, CAS latency 3 clocks, Write
	// burst mode single bit, normal operation mode.
	// Mode Register = 0x030: burst length 1, burst type sequential, CAS latency 3 clocks, Write
	// burst mode = single location access, normal operation mode
	cmd = {.CommandMode = FMC_SDRAM_CMD_LOAD_MODE,
		   .CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1,
		   .AutoRefreshNumber = 2,
		   .ModeRegisterDefinition = 0x231};
	FMC_SDRAM_SendCommand(FMC_SDRAM_DEVICE, &cmd, 0);
	wait_until_ready();

	// Refresh rate in number of SDCLK clock cycles between the refresh cycles
	auto refresh_ms_to_rate = [sdram_clock = sdram_clock_](uint32_t refresh_ms, uint32_t num_rows) {
		return sdram_clock * refresh_ms / (num_rows * 1000);
	};
	FMC_SDRAM_ProgramRefreshRate(FMC_SDRAM_DEVICE, refresh_ms_to_rate(64, 8192));
	wait_until_ready();
}

void SDRAMPeriph::init_gpio()
{
	for (auto &pind : defs.pin_list.pin_array) {
		Pin{pind.gpio, pind.pin, PinMode::Alt, pind.af, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	}
	// Todo: remove below once above is tested on hardware
	// clang-format off
	// Pin _A0    {GPIO::F, 0, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _A1    {GPIO::F, 1, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _A2    {GPIO::F, 2, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _A3    {GPIO::F, 3, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _A4    {GPIO::F, 4, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _A5    {GPIO::F, 5, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _SDNWE {GPIO::C, 0, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _SDNE0 {GPIO::C, 2, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _SDCKE0{GPIO::C, 3, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _SDNRAS{GPIO::F, 11, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _A6    {GPIO::F, 12, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _A7    {GPIO::F, 13, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _A8    {GPIO::F, 14, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _A9    {GPIO::F, 15, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _A10   {GPIO::G, 0, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _A11   {GPIO::G, 1, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _D4    {GPIO::E, 7, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _D5    {GPIO::E, 8, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _D6    {GPIO::E, 9, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _D7    {GPIO::E, 10, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _D8    {GPIO::E, 11, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _D9    {GPIO::E, 12, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _D10   {GPIO::E, 13, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _D11   {GPIO::E, 14, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _D12   {GPIO::E, 15, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _D13   {GPIO::D, 8, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _D14   {GPIO::D, 9, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _D15   {GPIO::D, 10, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _D0    {GPIO::D, 14, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _D1    {GPIO::D, 15, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _BA0   {GPIO::G, 4, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _BA1   {GPIO::G, 5, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _SDCLK {GPIO::G, 8, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _D2    {GPIO::D, 0, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _D3    {GPIO::D, 1, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _SDNCAS{GPIO::G, 15, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _NBL0  {GPIO::E, 0, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// Pin _NBL1  {GPIO::E, 1, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// not connected on p2 PCB:
	//Pin _A12   {GPIO::G, 2, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// clang-format on
}

bool SDRAMPeriph::is_busy()
{
	return __FMC_SDRAM_GET_FLAG(FMC_SDRAM_DEVICE, FMC_SDRAM_FLAG_BUSY);
}

void SDRAMPeriph::wait_until_ready()
{
	while (is_busy())
		;
}

uint32_t SDRAMPeriph::test(const uint32_t ram_start, const uint32_t ram_size)
{
	uint32_t num_fails = 0;

	auto countup_func = [](uint32_t x) { return x; };
	num_fails += do_sdram_test(countup_func, ram_start, ram_size);

	auto bitinvert_countdown_func = [](uint32_t x) { return 0xFFFFFFFFU - x; };
	num_fails += do_sdram_test(bitinvert_countdown_func, ram_start, ram_size);

	return num_fails;
}

uint32_t SDRAMPeriph::do_sdram_test(uint32_t (*mapfunc)(uint32_t), const uint32_t ram_start, const uint32_t ram_size)
{
	uint32_t num_fails = 0;
	const size_t test_val_size = sizeof(uint32_t);

	uint32_t addr = ram_start;
	for (uint32_t i = 0; i < (ram_size / test_val_size); i++) {
		wait_until_ready();
		uint32_t testval = mapfunc(i);
		*((uint32_t *)addr) = testval;

		addr += test_val_size;
	}

	addr = ram_start;
	for (uint32_t i = 0; i < (ram_size / test_val_size); i++) {
		wait_until_ready();
		uint32_t readval = *((uint32_t *)addr);
		uint32_t expectedval = mapfunc(i);
		if (readval != expectedval)
			num_fails++;

		addr += test_val_size;
	}
	return num_fails;
}

