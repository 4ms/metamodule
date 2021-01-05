#include "sdram.hh"
#include "pin.hh"
#include "stm32f7xx_ll_fmc.h"
#include "stm32f7xx_ll_gpio.h"
#include "stm32xx.h"

//#define SDRAM_DO_TEST

SDRAMPeriph::SDRAMPeriph(const SDRAMConfig &sdram_defs) noexcept

	: status(HAL_ERROR)
	, defs(sdram_defs)
{
	init_gpio();
	status = init();

#ifdef SDRAM_DO_TEST
	{
		// 434ms
		// vs SRAM1/2: 128ms
		// vs DTCM: 111ms
		uint32_t start = HAL_GetTick();
		uint32_t sdram_fails = SDRAMPeriph::test(0xC0000000, 0x00800000);
		volatile uint32_t elapsed = HAL_GetTick() - start;
		if (elapsed > 540) {
			while (1)
				;
		}
		while (sdram_fails)
			;
	}
#endif
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
	auto ns_to_hclks = [sdram_clock = sdram_clock_](uint32_t ns) { return 1 + ((ns * 10000000U) / sdram_clock); };

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
	auto bank = defs.connected_bank == 1 ? FMC_SDRAM_CMD_TARGET_BANK1 : FMC_SDRAM_CMD_TARGET_BANK2;

	// CLK ENABLE command
	cmd = {.CommandMode = FMC_SDRAM_CMD_CLK_ENABLE,
		   .CommandTarget = bank,
		   .AutoRefreshNumber = 2,
		   .ModeRegisterDefinition = 0};
	FMC_SDRAM_SendCommand(FMC_SDRAM_DEVICE, &cmd, 0);

	HAL_Delay(10);
	wait_until_ready();

	// All Bank Precharge command
	cmd = {
		.CommandMode = FMC_SDRAM_CMD_PALL, .CommandTarget = bank, .AutoRefreshNumber = 2, .ModeRegisterDefinition = 0};
	FMC_SDRAM_SendCommand(FMC_SDRAM_DEVICE, &cmd, 0);
	wait_until_ready();

	// Auto-refresh command
	cmd = {.CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE,
		   .CommandTarget = bank,
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
		   .CommandTarget = bank,
		   .AutoRefreshNumber = 2,
		   .ModeRegisterDefinition = 0x231};
	FMC_SDRAM_SendCommand(FMC_SDRAM_DEVICE, &cmd, 0);
	wait_until_ready();

	// Refresh rate in number of SDCLK clock cycles between the refresh cycles
	auto refresh_ms_to_refcount = [sdram_clock = sdram_clock_](uint32_t refresh_ms, uint32_t num_rows) -> uint32_t {
		uint32_t rate_us = (refresh_ms * 10000) / num_rows;
		uint32_t count = (sdram_clock / 1000000U) * rate_us;
		return (count / 10) - 20; // Safe margin, as per STM32F74x datasheet
	};
	FMC_SDRAM_ProgramRefreshRate(FMC_SDRAM_DEVICE, refresh_ms_to_refcount(defs.timing.refresh_ms, defs.arch.num_rows));
	wait_until_ready();
}

void SDRAMPeriph::init_gpio()
{
	for (auto &pind : defs.pin_list.pin_array) {
		Pin{pind.gpio, pind.pin, PinMode::Alt, pind.af, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	}
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
		// wait_until_ready();
		uint32_t testval = mapfunc(i);
		*((uint32_t *)addr) = testval;

		addr += test_val_size;
	}

	addr = ram_start;
	for (uint32_t i = 0; i < (ram_size / test_val_size); i++) {
		// wait_until_ready();
		uint32_t readval = *((uint32_t *)addr);
		uint32_t expectedval = mapfunc(i);
		if (readval != expectedval)
			num_fails++;

		addr += test_val_size;
	}
	return num_fails;
}

