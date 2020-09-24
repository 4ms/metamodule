#pragma GCC push_options
#pragma GCC optimize ("Os")

//Largely taken from CubeMX Example for QSPI_ReadWrite on the STM32F73xx DISCO
#include "hal.hh"
#include "qspi_flash.hh"

//IS25LQ020B
#define QSPI_FLASH_SIZE_ADDRESSBITS      24 		// 24 address bits = 2 Mbits
#define QSPI_FLASH_SIZE_BYTES            0x40000 	// 256 KBytes
#define QSPI_64KBLOCK_SIZE               0x10000  	// 64 KBytes, hence the name "64K Block" :)
#define QSPI_32KBLOCK_SIZE               0x8000   	// 32 KBytes, hence the name "32K Block" :)
#define QSPI_SECTOR_SIZE                 0x1000   	// 4 KBytes sectors
#define QSPI_PAGE_SIZE                   0x100    	// 256 Byte pages
#define QSPI_PAGE_ADDRESS_BITS           8    		// 8 bits = 256 addresses per page

#define QSPI_NUM_64KBLOCKS				(QSPI_FLASH_SIZE_BYTES/QSPI_64KBLOCK_SIZE)
#define QSPI_NUM_32KBLOCKS				(QSPI_FLASH_SIZE_BYTES/QSPI_32KBLOCK_SIZE)
#define QSPI_NUM_SECTORS				  (QSPI_FLASH_SIZE_BYTES/QSPI_SECTOR_SIZE)


#define QSPI_DUMMY_CYCLES_READ           0
#define QSPI_DUMMY_CYCLES_FAST_READ      8
#define QSPI_DUMMY_CYCLES_READ_QUAD      8
#define QSPI_DUMMY_CYCLES_READ_QUAD_IO   4

//Number of systicks (default values assume 20ms = 1 HAL systick (kUiUpdateRate = 200Hz))
//TODO: lock these to kUpdateRate
#define QSPI_CHIP_ERASE_MAX_TIME_SYSTICKS		     100 //2000ms
#define QSPI_64KBLOCK_ERASE_MAX_TIME_SYSTICKS	   50 //1000ms
#define QSPI_32KBLOCK_ERASE_MAX_TIME_SYSTICKS	   25 //500ms
#define QSPI_SECTOR_ERASE_MAX_TIME_SYSTICKS		   15 //300ms


#define QSPI_CS_PIN                GPIO_PIN_11
#define QSPI_CS_PIN_AF             GPIO_AF9_QUADSPI
#define QSPI_CS_GPIO_PORT          GPIOC

#define QSPI_CLK_PIN               GPIO_PIN_2
#define QSPI_CLK_PIN_AF            GPIO_AF9_QUADSPI
#define QSPI_CLK_GPIO_PORT         GPIOB

#define QSPI_D0_PIN                GPIO_PIN_7
#define QSPI_D0_PIN_AF             GPIO_AF10_QUADSPI
#define QSPI_D0_GPIO_PORT          GPIOE

#define QSPI_D1_PIN                GPIO_PIN_8
#define QSPI_D1_PIN_AF             GPIO_AF10_QUADSPI
#define QSPI_D1_GPIO_PORT          GPIOE

#define QSPI_D2_PIN                GPIO_PIN_9
#define QSPI_D2_PIN_AF             GPIO_AF10_QUADSPI
#define QSPI_D2_GPIO_PORT          GPIOE

#define QSPI_D3_PIN                GPIO_PIN_10
#define QSPI_D3_PIN_AF             GPIO_AF10_QUADSPI
#define QSPI_D3_GPIO_PORT          GPIOE

#define QSPI_CLK_ENABLE()          __HAL_RCC_QSPI_CLK_ENABLE()
#define QSPI_CLK_DISABLE()         __HAL_RCC_QSPI_CLK_DISABLE()

#define QSPI_CS_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOC_CLK_ENABLE()
#define QSPI_CLK_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()
#define QSPI_D0_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOE_CLK_ENABLE()
#define QSPI_D1_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOE_CLK_ENABLE()
#define QSPI_D2_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOE_CLK_ENABLE()
#define QSPI_D3_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOE_CLK_ENABLE()

#define QSPI_FORCE_RESET()         __HAL_RCC_QSPI_FORCE_RESET()
#define QSPI_RELEASE_RESET()       __HAL_RCC_QSPI_RELEASE_RESET()



/** 
  * @brief  QSPI Commands  
  */  
/* Reset Operations */
#define RESET_ENABLE_CMD                     0x66
#define RESET_CMD       		                 0x99
#define DEEP_POWER_DOWN_CMD					         0xB9

/* Identification Operations */
#define READ_ID_CMD                          0x9F
#define READ_MANUF_RELEASE_DP 				       0xAB
#define READ_UID 							               0x4B
#define READ_SERIAL_FLASH_DISCO_PARAM_CMD    0x5A


/* Read Operations */
#define READ_CMD                             0x03
#define FAST_READ_CMD                        0x0B
#define DUAL_OUT_FAST_READ_CMD               0x3B
#define DUAL_INOUT_FAST_READ_CMD             0xBB
#define QUAD_OUT_FAST_READ_CMD               0x6B
#define QUAD_INOUT_FAST_READ_CMD             0xEB

/* Register Operations */
#define READ_STATUS_REG_CMD                  0x05
#define WRITE_STATUS_REG_CMD         	       0x01
#define READ_FUNCTION_REG_CMD                0x48
#define WRITE_FUNCTION_REG_CMD         	     0x42
#define READ_INFO_ROW						             0x62
#define PROG_INFO_ROW					               0x68
#define SECTOR_UNLOCK					               0x26
#define SECTOR_LOCK						               0x24
#define WRITE_ENABLE_CMD				             0x06

/* Program Operations */
#define PAGE_PROG_CMD                        0x02
#define QUAD_IN_FAST_PROG_CMD                0x38

/* Erase Operations */
#define SECTOR_ERASE_CMD                     0x20
	   
#define BLOCK_ERASE_32K_CMD                  0x52
#define BLOCK_ERASE_64K_CMD                  0xD8
#define BULK_ERASE_CMD                       0xC7
#define PROG_ERASE_RESUME_CMD                0x30
#define PROG_ERASE_SUSPEND_CMD               0xB0
   
/* Status Register */
#define QSPI_SR_WIP                      ((uint8_t)0x01)    /*!< Write in progress */
#define QSPI_SR_WREN                     ((uint8_t)0x02)    /*!< Write enable latch */
#define QSPI_SR_BLOCKPR                  ((uint8_t)0x5C)    /*!< Block protected against program and erase operations */
#define QSPI_SR_PRBOTTOM                 ((uint8_t)0x20)    /*!< Protected memory area defined by BLOCKPR starts from top or bottom */
#define QSPI_SR_QUADEN                   ((uint8_t)0x40)    /*!< Quad IO mode enabled if =1 */
#define QSPI_SR_SRWREN                   ((uint8_t)0x80)    /*!< Status register write enable/disable */


//
// Tests one sector
// Returns true if passed, false if failed
bool QSpiFlash::Test_Sector(uint8_t sector_num)
{
	uint32_t i;
	uint8_t test_buffer[QSPI_SECTOR_SIZE];
	uint32_t test_addr = get_sector_addr(sector_num);

	for (i=0; i<QSPI_SECTOR_SIZE; i++)
		test_buffer[i] = (test_encode_num(i) + sector_num) & 0xFF;
	
	while (!is_ready()) {;}

	//Benchmark: ~38ms/sector
	if (!Erase(SECTOR, test_addr, EXECUTE_BACKGROUND))
		return false;

	while (!is_ready()) {;}

	for (i=0; i<(QSPI_SECTOR_SIZE/QSPI_PAGE_SIZE); i++)
	{
		//Benchmark: ~380us/page
		if (!Write_Page(&(test_buffer[i*QSPI_PAGE_SIZE]),
                    test_addr+i*QSPI_PAGE_SIZE,
                    QSPI_PAGE_SIZE, EXECUTE_BACKGROUND))
			return false;

		while (!is_ready()) {;}
	}

	for (i=0; i<QSPI_SECTOR_SIZE; i++)
		test_buffer[i] = 0;

	//Benchmark: ~680-850us/sector
	if (!Read(test_buffer, test_addr, QSPI_SECTOR_SIZE, EXECUTE_BACKGROUND))
		return false;

	while (!is_ready()) {;}

	for (i=0; i<(QSPI_SECTOR_SIZE-1); i++) {
		if (test_buffer[i] != ((test_encode_num(i) + sector_num) & 0xFF))
			return false;
	}

	return true;
}

// Tests entire chip sector-by-sector
// Returns 1 if passed, 0 if failed
bool QSpiFlash::Test()
{
	uint8_t sector;
	for (sector=0; sector<QSPI_NUM_SECTORS; sector++) {
		if (!Test_Sector(sector))
			return false; //fail
	}
	return true; //pass
}


uint32_t QSpiFlash::get_64kblock_addr(uint8_t block64k_num)
{
	if (block64k_num>=QSPI_NUM_64KBLOCKS)
		return 0;

	return block64k_num * QSPI_64KBLOCK_SIZE;
}

uint32_t QSpiFlash::get_32kblock_addr(uint8_t block32k_num)
{
	if (block32k_num>=QSPI_NUM_32KBLOCKS)
		return 0;

	return block32k_num * QSPI_32KBLOCK_SIZE;
}

uint32_t QSpiFlash::get_sector_addr(uint8_t sector_num)
{
	if (sector_num>=QSPI_NUM_SECTORS)
		return 0;

	return sector_num * QSPI_SECTOR_SIZE;
}

QSpiFlash::QSpiFlash()
{
	instance_ = this;

	handle.Instance = QUADSPI;

	hal_assert(HAL_QSPI_DeInit(&handle));

	QSPI_CLK_ENABLE();

	QSPI_FORCE_RESET();
	QSPI_RELEASE_RESET();

	//Initialize chip pins in single IO mode
	GPIO_Init_1IO();

	HAL_NVIC_SetPriority(QUADSPI_IRQn, 2, 2);
	HAL_NVIC_EnableIRQ(QUADSPI_IRQn);

	/* QSPI initialization */
	/* QSPI freq = SYSCLK /(1 + ClockPrescaler) = 216 MHz/(1+1) = 108 Mhz */
	handle.Init.ClockPrescaler     = 1; 
	handle.Init.FifoThreshold      = 16;
	handle.Init.SampleShifting     = QSPI_SAMPLE_SHIFTING_HALFCYCLE;
	handle.Init.FlashSize          = QSPI_FLASH_SIZE_ADDRESSBITS - 1;
	handle.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_8_CYCLE; //was 1
	handle.Init.ClockMode          = QSPI_CLOCK_MODE_0;
	handle.Init.FlashID            = QSPI_FLASH_ID_2;
	handle.Init.DualFlash          = QSPI_DUALFLASH_DISABLE;

	hal_assert(HAL_QSPI_Init(&handle));

	init_command(&s_command);

	QSPI_status = STATUS_READY;

	hal_assert(Reset());
	hal_assert(EnterMemory_QPI());

	// Now that chip is in QSPI mode, IO2 and IO3 can be initialized
	GPIO_Init_IO2_IO3_AF();

	// Erase(ENTIRE_CHIP, 0, EXECUTE_FOREGROUND);
	// if (!Test()) {
	// 	while (1) {
	// 		asm("nop");
	// 	}
	// }
}

void QSpiFlash::GPIO_Init_1IO(void)
{
	GPIO_InitTypeDef gpio;

	QSPI_CS_GPIO_CLK_ENABLE();
	QSPI_CLK_GPIO_CLK_ENABLE();
	QSPI_D0_GPIO_CLK_ENABLE();
	QSPI_D1_GPIO_CLK_ENABLE();
	QSPI_D2_GPIO_CLK_ENABLE();
	QSPI_D3_GPIO_CLK_ENABLE();

	gpio.Mode      = GPIO_MODE_AF_PP;
	gpio.Speed     = GPIO_SPEED_FREQ_HIGH;
	gpio.Pull      = GPIO_PULLUP;

	gpio.Pin       = QSPI_CS_PIN;
	gpio.Alternate = QSPI_CS_PIN_AF;
	HAL_GPIO_Init(QSPI_CS_GPIO_PORT, &gpio);

	gpio.Pin       = QSPI_CLK_PIN;
	gpio.Alternate = QSPI_CLK_PIN_AF;
	gpio.Pull      = GPIO_NOPULL;
	HAL_GPIO_Init(QSPI_CLK_GPIO_PORT, &gpio);

	gpio.Pin       = QSPI_D0_PIN;
	gpio.Alternate = QSPI_D0_PIN_AF;
	HAL_GPIO_Init(QSPI_D0_GPIO_PORT, &gpio);

	gpio.Pin       = QSPI_D1_PIN;
	gpio.Alternate = QSPI_D1_PIN_AF;
	HAL_GPIO_Init(QSPI_D1_GPIO_PORT, &gpio);

	//IO2 and IO3 are pulled high to disable HOLD and WP
	gpio.Mode      = GPIO_MODE_OUTPUT_PP;
	gpio.Pin       = QSPI_D2_PIN;
	HAL_GPIO_Init(QSPI_D2_GPIO_PORT, &gpio);
	QSPI_D2_GPIO_PORT->BSRR = QSPI_D2_PIN;

	gpio.Mode      = GPIO_MODE_OUTPUT_PP;
	gpio.Pin       = QSPI_D3_PIN;
	HAL_GPIO_Init(QSPI_D3_GPIO_PORT, &gpio);
	QSPI_D3_GPIO_PORT->BSRR = QSPI_D3_PIN;
}

void QSpiFlash::GPIO_Init_IO2_IO3_AF(void)
{
	GPIO_InitTypeDef gpio;

	gpio.Mode      = GPIO_MODE_AF_PP;
	gpio.Speed     = GPIO_SPEED_FREQ_HIGH;
	gpio.Pull      = GPIO_NOPULL;

	gpio.Pin       = QSPI_D2_PIN;
	gpio.Alternate = QSPI_D2_PIN_AF;
	HAL_GPIO_Init(QSPI_D2_GPIO_PORT, &gpio);

	gpio.Pin       = QSPI_D3_PIN;
	gpio.Alternate = QSPI_D3_PIN_AF;
	HAL_GPIO_Init(QSPI_D3_GPIO_PORT, &gpio);
}

void QSpiFlash::init_command(QSPI_CommandTypeDef *s_command)
{
	s_command->InstructionMode   = QSPI_INSTRUCTION_1_LINE;
	s_command->AddressSize       = QSPI_ADDRESS_24_BITS;
	s_command->DdrMode           = QSPI_DDR_MODE_DISABLE;
	s_command->DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
	s_command->SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
}

HAL_StatusTypeDef QSpiFlash::Reset(void)
{
	// Enable Reset
	s_command.Instruction       = RESET_ENABLE_CMD;
	s_command.AddressMode       = QSPI_ADDRESS_NONE;
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	s_command.DataMode          = QSPI_DATA_NONE;
	s_command.DummyCycles       = 0;

	if (HAL_QSPI_Command(&handle, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
		return HAL_ERROR;

	// Perform Reset
	s_command.Instruction = RESET_CMD;

	if (HAL_QSPI_Command(&handle, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
		return HAL_ERROR;

	return HAL_OK;
}

bool QSpiFlash::Erase(ErasableSizes size, uint32_t BaseAddress, UseInterruptFlags use_interrupt)
{
	uint8_t status;
	uint32_t timeout;

	if (WriteEnable() != HAL_OK)
		return false;

	if (size==SECTOR) {
		s_command.Instruction 	= SECTOR_ERASE_CMD;
		s_command.Address 		= BaseAddress;
		s_command.AddressMode   = QSPI_ADDRESS_1_LINE;
		timeout 				= QSPI_SECTOR_ERASE_MAX_TIME_SYSTICKS;
	}
	else if (size==BLOCK_32K) {
		s_command.Instruction 	= BLOCK_ERASE_32K_CMD;
		s_command.Address 		= BaseAddress;
		s_command.AddressMode   = QSPI_ADDRESS_1_LINE;
		timeout 				= QSPI_32KBLOCK_ERASE_MAX_TIME_SYSTICKS;
	}
	else if (size==BLOCK_64K) {
		s_command.Instruction 	= BLOCK_ERASE_64K_CMD;
		s_command.Address 		= BaseAddress;
		s_command.AddressMode   = QSPI_ADDRESS_1_LINE;
		timeout 				= QSPI_64KBLOCK_ERASE_MAX_TIME_SYSTICKS;
	}
	else if (size==ENTIRE_CHIP) {
		s_command.Instruction 	= BULK_ERASE_CMD;
		s_command.Address 		= QSPI_ADDRESS_NONE;
		s_command.AddressMode   = QSPI_ADDRESS_NONE;
		timeout 				= QSPI_CHIP_ERASE_MAX_TIME_SYSTICKS;
	}
	else  
		return false; //invalid size

	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	s_command.DataMode          = QSPI_DATA_NONE;
	s_command.DummyCycles       = 0;

	if (HAL_QSPI_Command(&handle, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
		return false;

	if (use_interrupt==EXECUTE_BACKGROUND)
		status = AutoPollingMemReady_IT();
	else 
		status = AutoPollingMemReady(timeout);
	
	if (status!=HAL_OK)
		return false;

	return true;
}

bool QSpiFlash::Write(uint8_t* pData, uint32_t write_addr, uint32_t num_bytes)
{
	uint32_t end_addr, current_size, current_addr;

	if (write_addr >= QSPI_FLASH_SIZE_BYTES)
		return false;

	if (write_addr+num_bytes >= QSPI_FLASH_SIZE_BYTES)
		return false;

	// Calculation of the size between the write address and the end of the page
	current_addr = 0;

	while (current_addr <= write_addr)
		current_addr += QSPI_PAGE_SIZE;

	current_size = current_addr - write_addr;

	// Check if the size of the data is less than the remaining in the page
	if (current_size > num_bytes)
		current_size = num_bytes;

	current_addr = write_addr;
	end_addr = write_addr + num_bytes;


	// Perform the write page by page
	do
	{
		if (WriteEnable() != HAL_OK)
			return false;

		s_command.Instruction       = QUAD_IN_FAST_PROG_CMD;
		s_command.AddressMode       = QSPI_ADDRESS_1_LINE;
		s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
		s_command.DataMode          = QSPI_DATA_4_LINES;
		s_command.DummyCycles       = 0;
		s_command.Address 			= current_addr;
		s_command.NbData  			= current_size;

		if (HAL_QSPI_Command(&handle, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
			return false;

		if (HAL_QSPI_Transmit(&handle, pData, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
			return false;

		if (AutoPollingMemReady(HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
			return false;

		current_addr += current_size;
		pData += current_size;
		current_size = ((current_addr + QSPI_PAGE_SIZE) > end_addr) ? (end_addr - current_addr) : QSPI_PAGE_SIZE;
	} while (current_addr < end_addr);

	return true;
}

// Writes within a page (256 Bytes)
// Data to be written must not cross page boundaries.
// Setting use_interrupt to 1 means HAL_QSPI_TxCpltCallback() interrupt will be called when TX is done,
// but you must still check the chip status before accessing it again.
//
  bool QSpiFlash::Write_Page(uint8_t* pData, uint32_t write_addr, uint32_t num_bytes, UseInterruptFlags use_interrupt)
{
	//Cannot write more than a page
	if (num_bytes > QSPI_PAGE_SIZE)
		return false;

	uint32_t start_page = write_addr >> QSPI_PAGE_ADDRESS_BITS;
	uint32_t end_page = (write_addr + num_bytes - 1) >> QSPI_PAGE_ADDRESS_BITS;

	//Cannot cross page boundaries
	if (start_page != end_page)
		return false;

	if (WriteEnable() != HAL_OK)
		return false;

	// Initialize the program command
	s_command.Instruction       = QUAD_IN_FAST_PROG_CMD;
	s_command.AddressMode       = QSPI_ADDRESS_1_LINE;
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	s_command.DataMode          = QSPI_DATA_4_LINES;
	s_command.DummyCycles       = 0;
	s_command.Address 			= write_addr;
	s_command.NbData  			= num_bytes;

	if (HAL_QSPI_Command(&handle, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
		return false;

	if (use_interrupt==EXECUTE_BACKGROUND)
	{
		QSPI_status = STATUS_TXING;

		if (HAL_QSPI_Transmit_IT(&handle, pData) != HAL_OK)
			return false;

		while (!done_TXing()) {;}

		// Set-up auto polling, which periodically queries the chip in the background
		AutoPollingMemReady_IT();
	}
	else
	{
		if (HAL_QSPI_Transmit(&handle, pData, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
			return false;

		if (AutoPollingMemReady_IT() != HAL_OK)
			return false;
	}

	return true;
}

bool QSpiFlash::Read(uint8_t* pData, uint32_t read_addr, uint32_t num_bytes, UseInterruptFlags use_interrupt)
{
	uint8_t status;

	//Todo: take advantage of AX Read mode (see datasheet) 
	//by setting:
	//s_command.SIOOMode			= QSPI_SIOO_INST_ONLY_FIRST_CMD;
	//s_command.AlternateByteMode 	= QSPI_ALTERNATE_BYTES_4_LINES;
	//s_command.AlternateBytesSize 	= QSPI_ALTERNATE_BYTES_8_BITS;
	//s_command.AlternateBytes 		= 0xA0;

	s_command.Instruction       = QUAD_INOUT_FAST_READ_CMD;
	s_command.AddressMode       = QSPI_ADDRESS_4_LINES;
	s_command.Address           = read_addr;
	s_command.AlternateBytesSize= QSPI_ALTERNATE_BYTES_8_BITS;
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_4_LINES;
	s_command.AlternateBytes	= 0x00;
	s_command.DataMode          = QSPI_DATA_4_LINES;
	s_command.DummyCycles       = QSPI_DUMMY_CYCLES_READ_QUAD_IO;
	s_command.NbData            = num_bytes;

	if (HAL_QSPI_Command(&handle, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
		return HAL_ERROR;

	if (use_interrupt==EXECUTE_BACKGROUND) {
		QSPI_status = STATUS_RXING;

		status = HAL_QSPI_Receive_IT(&handle, pData);
	} else 
		status = HAL_QSPI_Receive(&handle, pData, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
			
	if (status!=HAL_OK)
		return false;

	return true;
}

HAL_StatusTypeDef QSpiFlash::WriteEnable(void)
{
	QSPI_AutoPollingTypeDef s_config;

	/* Enable write operations */
	s_command.Instruction       = WRITE_ENABLE_CMD;
	s_command.AddressMode       = QSPI_ADDRESS_NONE;
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	s_command.DataMode          = QSPI_DATA_NONE;
	s_command.DummyCycles       = 0;

	if (HAL_QSPI_Command(&handle, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
		return HAL_ERROR;

	/* Configure automatic polling mode to wait for write enabling */
	s_config.Match           = QSPI_SR_WREN;
	s_config.Mask            = QSPI_SR_WREN;
	s_config.MatchMode       = QSPI_MATCH_MODE_AND;
	s_config.StatusBytesSize = 1;
	s_config.Interval        = 0x10;
	s_config.AutomaticStop   = QSPI_AUTOMATIC_STOP_ENABLE;

	s_command.Instruction    = READ_STATUS_REG_CMD;
	s_command.DataMode       = QSPI_DATA_1_LINE;

	if (HAL_QSPI_AutoPolling(&handle, &s_command, &s_config, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
		return HAL_ERROR;

	return HAL_OK;
}

/**
  * @brief  Repeatedly reads the status register of the chip and waits until it indicates Write In Progress is complete.
  * @param  Timeout
  * @retval None
  */
HAL_StatusTypeDef QSpiFlash::AutoPollingMemReady(uint32_t Timeout)
{
	QSPI_AutoPollingTypeDef s_config;

	/* Configure automatic polling mode to wait for memory ready */
	s_command.Instruction       = READ_STATUS_REG_CMD;
	s_command.AddressMode       = QSPI_ADDRESS_NONE;
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	s_command.DataMode          = QSPI_DATA_1_LINE;
	s_command.DummyCycles       = 0;

	s_config.Match           = 0;
	s_config.Mask            = QSPI_SR_WIP;
	s_config.MatchMode       = QSPI_MATCH_MODE_AND;
	s_config.StatusBytesSize = 1;
	s_config.Interval        = 0x10;
	s_config.AutomaticStop   = QSPI_AUTOMATIC_STOP_ENABLE;

	if (HAL_QSPI_AutoPolling(&handle, &s_command, &s_config, Timeout) != HAL_OK)
		return HAL_ERROR;

	return HAL_OK;
}

/**
  * @brief  Sets up auto-polling to call the HAL_QSPI_StatusMatchCallback() when the status register indicates Write In Progress is cleared.
  * @param  None
  * @retval None
  */

HAL_StatusTypeDef QSpiFlash::AutoPollingMemReady_IT(void)
{
	QSPI_AutoPollingTypeDef s_config;

	/* Configure automatic polling mode to wait for memory ready */
	s_command.Instruction       = READ_STATUS_REG_CMD;
	s_command.AddressMode       = QSPI_ADDRESS_NONE;
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	s_command.DataMode          = QSPI_DATA_1_LINE;
	s_command.DummyCycles       = 0;

	s_config.Match           = 0;
	s_config.Mask            = QSPI_SR_WIP;
	s_config.MatchMode       = QSPI_MATCH_MODE_AND;
	s_config.StatusBytesSize = 1;
	s_config.Interval        = 0x10;
	s_config.AutomaticStop   = QSPI_AUTOMATIC_STOP_ENABLE;

	QSPI_status = STATUS_WIP;

	if (HAL_QSPI_AutoPolling_IT(&handle, &s_command, &s_config) != HAL_OK)
		return HAL_ERROR;

	return HAL_OK;
}


/**
  * @brief  This function put QSPI memory in QPI mode (quad I/O).
  * @retval None
  */
HAL_StatusTypeDef QSpiFlash::EnterMemory_QPI(void)
{
	QSPI_AutoPollingTypeDef  s_config;
	uint8_t	reg;

	reg = QSPI_SR_QUADEN;

	s_command.Instruction       = WRITE_ENABLE_CMD;
	s_command.AddressMode       = QSPI_ADDRESS_NONE;
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	s_command.DataMode          = QSPI_DATA_NONE;
	s_command.DummyCycles       = 0;

	if (HAL_QSPI_Command(&handle, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
		return HAL_ERROR;


	s_command.Instruction       = WRITE_STATUS_REG_CMD;
	s_command.AddressMode       = QSPI_ADDRESS_NONE;
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	s_command.DataMode          = QSPI_DATA_1_LINE;
	s_command.DummyCycles       = 0;
	s_command.NbData            = 1;

	if (HAL_QSPI_Command(&handle, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
		return HAL_ERROR;

	if (HAL_QSPI_Transmit(&handle, &reg, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
		return HAL_ERROR;

	/* 40ms  Write Status/Configuration Register Cycle Time */
	HAL_Delay(8);

	/* Configure automatic polling mode to wait the QUADEN bit=1 and WIP bit=0 */
	s_config.Match           = QSPI_SR_QUADEN;
	s_config.Mask            = QSPI_SR_QUADEN /*|QSPI_SR_WIP*/;
	s_config.MatchMode       = QSPI_MATCH_MODE_AND;
	s_config.StatusBytesSize = 1;
	s_config.Interval        = 0x10;
	s_config.AutomaticStop   = QSPI_AUTOMATIC_STOP_ENABLE;

	s_command.Instruction    = READ_STATUS_REG_CMD;
	s_command.DataMode       = QSPI_DATA_1_LINE;

	if (HAL_QSPI_AutoPolling(&handle, &s_command, &s_config, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
		return HAL_ERROR;

	return HAL_OK;
}

QSpiFlash *QSpiFlash::instance_;

// Callbacks & IRQ handlers

void HAL_QSPI_StatusMatchCallback(QSPI_HandleTypeDef *hqspi)
{
  QSpiFlash::instance_->QSPI_status = QSpiFlash::STATUS_READY;
}

void HAL_QSPI_RxCpltCallback(QSPI_HandleTypeDef *hqspi)
{
	if (QSpiFlash::instance_->QSPI_status == QSpiFlash::STATUS_RXING)
		QSpiFlash::instance_->QSPI_status = QSpiFlash::STATUS_READY;
}

void HAL_QSPI_TxCpltCallback(QSPI_HandleTypeDef *hqspi)
{
	if (QSpiFlash::instance_->QSPI_status == QSpiFlash::STATUS_TXING)
		QSpiFlash::instance_->QSPI_status = QSpiFlash::STATUS_TX_COMPLETE;
}
extern "C" void QUADSPI_IRQHandler(void)
{
	HAL_QSPI_IRQHandler(&QSpiFlash::instance_->handle);
}

#pragma GCC pop_options
