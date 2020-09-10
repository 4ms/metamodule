#include "pca9685_led_driver.hh"
#include "defs/led_defs.hh"
#include "interrupt.hh"

static const uint32_t LEDDRIVER_LONG_TIMEOUT = 4000;

PCA9685Driver::PCA9685Driver(i2cPeriph &i2c, uint32_t num_chips)
	: i2cp_(i2c)
	, num_chips_(num_chips)
	, cur_chip_num_(0)
	
{
	instance_ = this;
}

LEDDriverError PCA9685Driver::init_as_dma(uint8_t *led_image)
{
	LEDDriverError err;
	err = init_as_direct();
	if (err!=LEDDriverError::None) return err;

	frame_buffer_start = led_image;
	frame_buffer_cur_pos = frame_buffer_start;

	err = I2C_Init();
	if (err!=LEDDriverError::None) return err;

	err = I2C_DMA_Init();
	return err;
}

LEDDriverError PCA9685Driver::init_as_direct()
{
	uint8_t driverAddr;
	LEDDriverError err = LEDDriverError::None;

	err = I2C_Init();
	if (err!=LEDDriverError::None) return err;

	for (driverAddr=0; driverAddr<num_chips_; driverAddr++){
		err = reset_chip(driverAddr);
		if (err!=LEDDriverError::None) 
			return (err);//Todo return failed driver#: | ((driverAddr+1)<<4));
	}

	return LEDDriverError::None;
}

LEDDriverError PCA9685Driver::reset_chip(uint8_t driverAddr)
{
	LEDDriverError err;

	err = writeregister(driverAddr, LedDriverDefs::PCA9685_MODE1, 0b00000000); // clear sleep mode
	if (err!=LEDDriverError::None) return err;
	HAL_Delay(1);

	err = writeregister(driverAddr, LedDriverDefs::PCA9685_MODE1, 0b10000000); //start reset mode
	if (err!=LEDDriverError::None) return err;
	HAL_Delay(1);

	err = writeregister(driverAddr, LedDriverDefs::PCA9685_MODE1, 0b00100000);	//auto increment
	if (err!=LEDDriverError::None) return err;
	err = writeregister(driverAddr, LedDriverDefs::PCA9685_MODE2, 0b00010001);	// INVERT=1, OUTDRV=0, OUTNE=01
	if (err!=LEDDriverError::None) return err;

	return LEDDriverError::None;
}


// Sets the brightness value of a single LED
// led_element_number==0 is PWM pin 0 of PCA9685 chip with address 0
// led_element_number==1 is PWM pin 1 of PCA9685 chip with address 0
// ...
// led_element_number==15 is PWM pin 15 of PCA9685 chip with address 0
// led_element_number==16 is PWM pin 0 of PCA9685 chip with address 1
// ...
//
LEDDriverError PCA9685Driver::set_single_led(uint8_t led_element_number, uint16_t brightness)
{
	uint8_t driver_addr;
	uint8_t data[5]; //2 bytes for on time + 2 bytes for off time + 1 byte for LED address
	HAL_StatusTypeDef err;

	if (led_element_number < (num_chips_*16))
	{
		driver_addr = (led_element_number/16);
		led_element_number = led_element_number - (driver_addr * 16);

		driver_addr = LedDriverDefs::PCA9685_I2C_BASE_ADDRESS | (driver_addr << 1);

		data[0] = LedDriverDefs::PCA9685_LED0 + (led_element_number*4); 	//4 registers per LED element
		data[1] = 0; 										//on-time = 0
		data[2] = 0;
		data[3] = brightness & 0xFF; 						//off-time = brightness
		data[4] = brightness >> 8;

		while((err = HAL_I2C_Master_Transmit(&pwmleddriver_i2c, driver_addr, data, 5, LEDDRIVER_LONG_TIMEOUT)) != HAL_OK)
		{
			if (HAL_I2C_GetError(&pwmleddriver_i2c) != HAL_I2C_ERROR_AF)
				return LEDDriverError::SET_LED_ERR;
		}
	}
	else
		return LEDDriverError::BAD_LED_PARAM;

	return LEDDriverError::None;

}

// Sets color of an RGB LED
// Assumes 5 RGB LEDs per driver chip, in positions 0-14
// Example:
// led_number==0 refers to PWM pins 0,1,2 of PCA9685 chip with address 0
// led_number==1 refers to PWM pins 3,4,5 of PCA9685 chip with address 0
// ...
// led_number==5 refers to PWM pins 0,1,2 of PCA9685 chip with address 1
// ..
// led_number==9 refers to PWM pins 12,13,14 of PCA9685 chip with address 1
//
// Note: This function never changes PWM pin 15
//
LEDDriverError PCA9685Driver::set_rgb_led(uint8_t led_number, uint16_t c_red, uint16_t c_green, uint16_t c_blue){

	uint8_t driverAddr;
	uint8_t data[13]; //(3 colors * (2 bytes for on time + 2 bytes for off time)) + 1 byte for LED address

	if (led_number >= (num_chips_*5))
		return LEDDriverError::BAD_LED_PARAM;

	driverAddr = (led_number/5);
	led_number = led_number - (driverAddr * 5);

	data[0] = REG_LED0 + (led_number*12); //12 registers per LED (4 registers per LED element) = 12*16 registers per driver
	data[1] = 0; 								//on-time = 0
	data[2] = 0;
	data[3] = c_red & 0xFF; 					//off-time = brightness
	data[4] = c_red >> 8;

	data[5] = 0; 								//on-time = 0
	data[6] = 0;
	data[7] = c_green & 0xFF; 					//off-time = brightness
	data[8] = c_green >> 8;

	data[9] = 0; 								//on-time = 0
	data[10] = 0;
	data[11] = c_blue & 0xFF; 					//off-time = brightness
	data[12] = c_blue >> 8;

	driverAddr = I2C_BASE_ADDRESS | (driverAddr << 1);

	auto err = i2cp_.write(driverAddr, data, 13);

	return (err==i2cPeriph::Error::I2C_NO_ERR) 
		? LEDDriverError::None 
		: LEDDriverError::I2C_XMIT_TIMEOUT;
}

LEDDriverError PCA9685Driver::writeregister(uint8_t driverAddr, uint8_t registerAddr, uint8_t registerValue)
{
	uint8_t data[2] = { registerAddr, registerValue };

	driverAddr = I2C_BASE_ADDRESS | (driverAddr << 1);

	auto err = i2cp_.write(driverAddr, data, 2);

	return (err==i2cPeriph::Error::I2C_NO_ERR) 
		? LEDDriverError::None 
		: LEDDriverError::I2C_XMIT_TIMEOUT;
}

//returns led element number of the red element of the given RGB LED id (green is red + 1, blue = red + 2)
uint8_t get_red_led_element_id(uint8_t rgb_led_id) {
	return (rgb_led_id*3) + (rgb_led_id/5);
}

uint8_t get_chip_num(uint8_t rgb_led_id){
	return (rgb_led_id/5);
}

uint8_t PCA9685Driver::get_cur_chip() {
	return cur_chip_num_;
}


LEDDriverError PCA9685Driver::I2C_Init()
{
	i2cp_.enable_IT(2, 2);
	return LEDDriverError::None;
}

LEDDriverError PCA9685Driver::I2C_DMA_Init()
{
	HAL_StatusTypeDef hal_err;

	System::enable_dma_rcc(LedDriverDefs::DMAx);

	pwmleddriver_dmatx.Instance                 = LedDriverDefs::DMAx_stream;
	pwmleddriver_dmatx.Init.Channel             = LedDriverDefs::DMAx_channel;
	pwmleddriver_dmatx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
	pwmleddriver_dmatx.Init.PeriphInc           = DMA_PINC_DISABLE;
	pwmleddriver_dmatx.Init.MemInc              = DMA_MINC_ENABLE;
	pwmleddriver_dmatx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	pwmleddriver_dmatx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	pwmleddriver_dmatx.Init.Mode                = DMA_NORMAL; //DMA_CIRCULAR
	pwmleddriver_dmatx.Init.Priority            = DMA_PRIORITY_LOW;
	pwmleddriver_dmatx.Init.FIFOMode 			= DMA_FIFOMODE_DISABLE;
	pwmleddriver_dmatx.Init.FIFOThreshold 		= DMA_FIFO_THRESHOLD_FULL;
	pwmleddriver_dmatx.Init.MemBurst 			= DMA_MBURST_SINGLE;
	pwmleddriver_dmatx.Init.PeriphBurst 		= DMA_PBURST_SINGLE;

	HAL_DMA_DeInit(&pwmleddriver_dmatx);
	hal_err = HAL_DMA_Init(&pwmleddriver_dmatx);
	if (hal_err != HAL_OK)
		return LEDDriverError::DMA_XMIT_ERR;
		
	i2cp_.link_DMA_RX(&pwmleddriver_dmatx);

	if (LedDriverDefs::DMAx_stream == DMA1_Stream0)
		Interrupts::DMA::DMA1_S0_handle = &pwmleddriver_dmatx;

	HAL_NVIC_SetPriority(LedDriverDefs::DMA_TX_IRQn, 3, 1);
	HAL_NVIC_EnableIRQ(LedDriverDefs::DMA_TX_IRQn);

	auto err = i2cp_.mem_write(
			I2C_BASE_ADDRESS, 
			REG_LED0,
			REGISTER_ADDR_SIZE,
			frame_buffer_cur_pos, 
			kNumRGBLEDsPerChip*4);

	if (err != i2cPeriph::Error::I2C_NO_ERR)
		return LEDDriverError::DMA_XMIT_ERR;

    return LEDDriverError::None;
}

void LEDDRIVER_I2C_DMA_TX_IRQHandler()
{
	HAL_DMA_IRQHandler(PCA9685Driver::instance_->pwmleddriver_i2c.hdmatx);
}

void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *hi2c) {
	//PCA9685Driver::instance_->
	HAL_StatusTypeDef err;
	uint16_t driver_addr;

	if (++cur_chip_num_ >= num_chips_)
	{
		cur_chip_num_ = 0;
		//leddriver_cur_buf = 1-leddriver_cur_buf;
	}

	leddriver_buffer = leddriver_buffer_start + cur_chip_num_*(kNumRGBLEDsPerChip*4);

	driver_addr = PCA9685_I2C_BASE_ADDRESS | (cur_chip_num_ << 1);

	err = HAL_I2C_Mem_Write_DMA(&pwmleddriver_i2c, driver_addr, PCA9685_LED0, I2C_MEMADD_SIZE_8BIT, leddriver_buffer, NUM_LEDS_PER_CHIP*4);
	if (err != HAL_OK)
  		g_led_error = LEDDRIVER_DMA_XMIT_ERR;

}
