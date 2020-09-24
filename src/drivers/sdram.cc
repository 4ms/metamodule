#include "sdram.hh"
#include "pin.hh"
#include "stm32f7xx_ll_fmc.h"
#include "stm32f7xx_ll_gpio.h"
#include "stm32xx.h"

SDRAMPeriph::SDRAMPeriph() noexcept
{
	init_gpio();
	status = init();
}

HAL_StatusTypeDef SDRAMPeriph::init()
{
	// hsdram1.Instance = FMC_SDRAM_DEVICE;

	// hsdram1.Init.SDBank = FMC_SDRAM_BANK1;
	// hsdram1.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_9; // 8
	// hsdram1.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_13;		 // 12
	// hsdram1.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_16;
	// hsdram1.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
	// hsdram1.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_3;
	// hsdram1.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
	// hsdram1.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2; // FMC_SDRAM_CLOCK_DISABLE;
	// hsdram1.Init.ReadBurst = FMC_SDRAM_RBURST_ENABLE;	   // DISABLE;
	// hsdram1.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_2;  //_0;

	FMC_SDRAM_TimingTypeDef SdramTiming = {0};
	SdramTiming.RowCycleDelay = 6;
	SdramTiming.RPDelay = 2;
	SdramTiming.LoadToActiveDelay = 2;
	SdramTiming.ExitSelfRefreshDelay = 6;
	SdramTiming.SelfRefreshTime = 4;
	SdramTiming.WriteRecoveryTime = 2;
	SdramTiming.RCDDelay = 2;

	// HAL_SDRAM_Init(&hsdram1, &SdramTiming);

	FMC_SDRAM_InitTypeDef init;
	init.SDBank = FMC_SDRAM_BANK1;
	init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_9; // 8
	init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_13;		 // 12
	init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_16;
	init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
	init.CASLatency = FMC_SDRAM_CAS_LATENCY_3;
	init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
	init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2; // FMC_SDRAM_CLOCK_DISABLE;
	init.ReadBurst = FMC_SDRAM_RBURST_ENABLE;	   // DISABLE;
	init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_2;  //_0;

	FMC_SDRAM_Init(FMC_SDRAM_DEVICE, &init);
	FMC_SDRAM_Timing_Init(FMC_SDRAM_DEVICE, &SdramTiming, init.SDBank);
	while (is_busy())
		;

	FMC_SDRAM_CommandTypeDef cmd;
	// PALL command (Pre-charge all banks): CLK ENABLE command?
	FMC_Bank5_6->SDCMR = 1 | FMC_SDCMR_CTB1 | (1 << 5);
	// cmd = {.CommandMode = FMC_SDRAM_CMD_CLK_ENABLE,
	// 	   .CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1,
	// 	   .AutoRefreshNumber = 2,
	// 	   .ModeRegisterDefinition = 0};
	// FMC_SDRAM_SendCommand(FMC_SDRAM_DEVICE, &cmd, 0);

	HAL_Delay(10);
	while (is_busy())
		;

	// 2 = PALL (All Bank Precharge) command
	// 1<<5 = 2 Auto-refresh cycles
	FMC_Bank5_6->SDCMR = 2 | FMC_SDCMR_CTB1 | (1 << 5);
	// cmd = {.CommandMode = FMC_SDRAM_CMD_PALL,
	// 	   .CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1,
	// 	   .AutoRefreshNumber = 2,
	// 	   .ModeRegisterDefinition = 0};
	// FMC_SDRAM_SendCommand(FMC_SDRAM_DEVICE, &cmd, 0);
	while (is_busy())
		;

	// 3 = Auto-refresh command
	// 4<<5 = 5 Auto-refresh cycles
	FMC_Bank5_6->SDCMR = 3 | FMC_SDCMR_CTB1 | (4 << 5);
	// cmd = {.CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE,
	// 	   .CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1,
	// 	   .AutoRefreshNumber = 5,
	// 	   .ModeRegisterDefinition = 0};
	// FMC_SDRAM_SendCommand(FMC_SDRAM_DEVICE, &cmd, 0);
	while (is_busy())
		;

	// 4 = Load Mode Register
	// 1<<5 = 2 Auto-refresh cycles
	// Mode Register = 0x231: burst length 2, burst type sequential, CAS latency 3 clocks, Write
	// burst mode single bit, normal operation mode.
	// Mode Register = 0x030: burst length 1, burst type sequential, CAS latency 3 clocks, Write
	// burst mode = single location access, normal operation mode
	FMC_Bank5_6->SDCMR = 4 | FMC_SDCMR_CTB1 | (1 << 5) | (0x231 << 9);
	// cmd = {.CommandMode = FMC_SDRAM_CMD_LOAD_MODE,
	// 	   .CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1,
	// 	   .AutoRefreshNumber = 2,
	// 	   .ModeRegisterDefinition = 0x231};
	// FMC_SDRAM_SendCommand(FMC_SDRAM_DEVICE, &cmd, 0);
	while (is_busy())
		;

	// refresh rate in number of SDCLK clock cycles between the refresh cycles
	// 683 = 7.6uS x 90Mhz
	// 7.6uS x 8196 rows = 62ms refresh rate
	FMC_Bank5_6->SDRTR |= (663 << 1);
	// FMC_SDRAM_ProgramRefreshRate(FMC_SDRAM_DEVICE, 633);
	while (is_busy())
		;

	return HAL_OK;
}

void SDRAMPeriph::init_gpio()
{
	// clang-format off
	Pin _A0    {GPIO::F, 0, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _A1    {GPIO::F, 1, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _A2    {GPIO::F, 2, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _A3    {GPIO::F, 3, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _A4    {GPIO::F, 4, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _A5    {GPIO::F, 5, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _SDNWE {GPIO::C, 0, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _SDNE0 {GPIO::C, 2, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _SDCKE0{GPIO::C, 3, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _SDNRAS{GPIO::F, 11, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _A6    {GPIO::F, 12, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _A7    {GPIO::F, 13, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _A8    {GPIO::F, 14, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _A9    {GPIO::F, 15, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _A10   {GPIO::G, 0, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _A11   {GPIO::G, 1, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _D4    {GPIO::E, 7, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _D5    {GPIO::E, 8, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _D6    {GPIO::E, 9, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _D7    {GPIO::E, 10, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _D8    {GPIO::E, 11, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _D9    {GPIO::E, 12, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _D10   {GPIO::E, 13, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _D11   {GPIO::E, 14, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _D12   {GPIO::E, 15, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _D13   {GPIO::D, 8, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _D14   {GPIO::D, 9, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _D15   {GPIO::D, 10, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _D0    {GPIO::D, 14, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _D1    {GPIO::D, 15, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _BA0   {GPIO::G, 4, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _BA1   {GPIO::G, 5, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _SDCLK {GPIO::G, 8, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _D2    {GPIO::D, 0, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _D3    {GPIO::D, 1, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _SDNCAS{GPIO::G, 15, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _NBL0  {GPIO::E, 0, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	Pin _NBL1  {GPIO::E, 1, PinMode::Alt, LL_GPIO_AF_12, PinPull::None, PinPolarity::Normal, PinSpeed::VeryHigh};
	// clang-format on

	__HAL_RCC_FMC_CLK_ENABLE();

	// __HAL_RCC_GPIOF_CLK_ENABLE();
	// __HAL_RCC_GPIOC_CLK_ENABLE();
	// __HAL_RCC_GPIOG_CLK_ENABLE();
	// __HAL_RCC_GPIOE_CLK_ENABLE();
	// __HAL_RCC_GPIOD_CLK_ENABLE();
	// GPIO_InitTypeDef GPIO_InitStruct = {0};

	// GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 |
	// 					  GPIO_PIN_5 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 |
	// 					  GPIO_PIN_15;
	// GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	// GPIO_InitStruct.Pull = GPIO_NOPULL;
	// GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	// GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
	// HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

	// GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_2 | GPIO_PIN_3;
	// GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	// GPIO_InitStruct.Pull = GPIO_NOPULL;
	// GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	// GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
	// HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	// GPIO_InitStruct.Pin =
	// 	GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_8 | GPIO_PIN_15;
	// GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	// GPIO_InitStruct.Pull = GPIO_NOPULL;
	// GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	// GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
	// HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	// GPIO_InitStruct.Pin = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 |
	// 					  GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15 | GPIO_PIN_0 |
	// 					  GPIO_PIN_1;
	// GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	// GPIO_InitStruct.Pull = GPIO_NOPULL;
	// GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	// GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
	// HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	// GPIO_InitStruct.Pin =
	// 	GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_14 | GPIO_PIN_15 | GPIO_PIN_0 | GPIO_PIN_1;
	// GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	// GPIO_InitStruct.Pull = GPIO_NOPULL;
	// GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	// GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
	// HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

bool SDRAMPeriph::is_busy()
{
	return __FMC_SDRAM_GET_FLAG(FMC_SDRAM_DEVICE, FMC_SDRAM_FLAG_BUSY);
}

bool SDRAMPeriph::test()
{
	uint32_t addr;
	uint32_t i;
	uint32_t fail = 0;

	addr = SDRAM_BASE;
	for (i = 0; i < (SDRAM_SIZE / 2); i++) {
		while (is_busy())
			;

		uint16_t testval = (uint16_t)((i)&0x0000FFFF);

		*((uint16_t *)addr) = testval;

		addr += 2;
	}

	addr = SDRAM_BASE;
	for (i = 0; i < (SDRAM_SIZE / 2); i++) {
		while (is_busy())
			;

		uint16_t readval = *((uint16_t *)addr);

		uint16_t expectedval = (uint16_t)((i)&0x0000FFFF);
		if (readval != expectedval)
			fail++;

		addr += 2;
	}

	return (fail != 0);
}
