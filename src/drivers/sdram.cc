#include "stm32xx.h"
#include "sdram.hh"

SDRAMPeriph::SDRAMPeriph() noexcept
{
	init_gpio();
	status = init();
}

HAL_StatusTypeDef SDRAMPeriph::init()
{
	hsdram1.Instance = FMC_SDRAM_DEVICE;

	hsdram1.Init.SDBank = FMC_SDRAM_BANK1;
	hsdram1.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_9; //8
	hsdram1.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_13; //12
	hsdram1.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_16;
	hsdram1.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
	hsdram1.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_3;
	hsdram1.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
	hsdram1.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2;//FMC_SDRAM_CLOCK_DISABLE;
	hsdram1.Init.ReadBurst = FMC_SDRAM_RBURST_ENABLE;//DISABLE;
	hsdram1.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_2;//_0;

	FMC_SDRAM_TimingTypeDef SdramTiming = {0};

	SdramTiming.LoadToActiveDelay = 16;
	SdramTiming.ExitSelfRefreshDelay = 16;
	SdramTiming.SelfRefreshTime = 16;
	SdramTiming.RowCycleDelay = 16;
	SdramTiming.WriteRecoveryTime = 16;
	SdramTiming.RPDelay = 16;
	SdramTiming.RCDDelay = 16;

	return HAL_SDRAM_Init(&hsdram1, &SdramTiming);
}

void SDRAMPeriph::init_gpio()
{
	/** FMC GPIO Configuration
	PF0   ------> FMC_A0
	PF1   ------> FMC_A1
	PF2   ------> FMC_A2
	PF3   ------> FMC_A3
	PF4   ------> FMC_A4
	PF5   ------> FMC_A5
	PC0   ------> FMC_SDNWE
	PC2   ------> FMC_SDNE0
	PC3   ------> FMC_SDCKE0
	PF11   ------> FMC_SDNRAS
	PF12   ------> FMC_A6
	PF13   ------> FMC_A7
	PF14   ------> FMC_A8
	PF15   ------> FMC_A9
	PG0   ------> FMC_A10
	PG1   ------> FMC_A11
	PE7   ------> FMC_D4
	PE8   ------> FMC_D5
	PE9   ------> FMC_D6
	PE10   ------> FMC_D7
	PE11   ------> FMC_D8
	PE12   ------> FMC_D9
	PE13   ------> FMC_D10
	PE14   ------> FMC_D11
	PE15   ------> FMC_D12
	PD8   ------> FMC_D13
	PD9   ------> FMC_D14
	PD10   ------> FMC_D15
	PD14   ------> FMC_D0
	PD15   ------> FMC_D1
	PG4   ------> FMC_BA0
	PG5   ------> FMC_BA1
	PG8   ------> FMC_SDCLK
	PD0   ------> FMC_D2
	PD1   ------> FMC_D3
	PG15   ------> FMC_SDNCAS
	PE0   ------> FMC_NBL0
	PE1   ------> FMC_NBL1
	*/
	__HAL_RCC_FMC_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStruct ={0};

	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
						  |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_11|GPIO_PIN_12
						  |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5
						  |GPIO_PIN_8|GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10
						  |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
						  |GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_14
						  |GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

bool SDRAMPeriph::is_busy() {
	return __FMC_SDRAM_GET_FLAG(FMC_SDRAM_DEVICE, FMC_SDRAM_FLAG_BUSY);
	//return (FMC_Bank5_6->SDSR & FMC_SDRAM_FLAG_BUSY) == FMC_SDRAM_FLAG_BUSY;
}

bool SDRAMPeriph::test()
{
	uint32_t addr;
	uint32_t i;
	uint16_t rd0;
	uint16_t rd1;
	volatile uint32_t fail=0;

	addr=SDRAM_BASE;
	for (i=0;i<(SDRAM_SIZE/2);i++) {

		while(is_busy()){;}

		rd1 = (uint16_t)((i) & 0x0000FFFF);

		auto err = HAL_SDRAM_Write_16b(&hsdram1, &addr, &rd1, 1); 
		//*((uint16_t *)addr) = rd1;

		addr+=2;
	}

	addr=SDRAM_BASE;
	for (i=0;i<(SDRAM_SIZE/2);i++) {

		// if (i & 0x80000) 	PLAYLED2_ON;
		// else 				BUSYLED_ON;

		while(is_busy()){;}

		// if (i & 0x80000) 	PLAYLED2_OFF;
		// else BUSYLED_OFF;

		rd1 = *((uint16_t *)addr);

		rd0=(uint16_t)((i) & 0x0000FFFF);
		if (rd1 != rd0)
			fail++;

		addr+=2;
	}

	return(fail);
}
