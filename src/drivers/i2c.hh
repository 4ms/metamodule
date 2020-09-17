#ifndef __SRC_DRIVERS_I2C
#define __SRC_DRIVERS_I2C
#include "drivers/interrupt.hh"
#include "pin.hh"
#include <stdint.h>

class I2CPeriph {
public:
	enum Error {
		I2C_NO_ERR,
		I2C_INIT_ERR,
		I2C_ALREADY_INIT,
		I2C_XMIT_ERR
	};
	struct i2cTimingReg {
		uint8_t PRESC;		   //top 4 bits: (PRESC + 1) * tI2CCLK = tPRESC
							   //bottom 4 bits is ignored
		uint8_t SCLDEL_SDADEL; //top 4 bits: SCLDEL * tPRESC = SCL Delay between SDA edge and SCL rising edge
							   //bottom 4 bits: = SDADEL * tPRESC = SDA Delay between SCL falling edge and SDA edge
		uint8_t SCLH;		   //SCL high period = (SCLH+1) * tPRESC
		uint8_t SCLL;		   //SCL low period = (SCLL+1) * tPRESC
		constexpr uint32_t calc() const
		{
			return ((PRESC) << 24) | ((SCLDEL_SDADEL) << 16) | ((SCLH) << 8) | ((SCLL) << 0);
		}
	};

	I2CPeriph() = default;
	~I2CPeriph() = default;

	I2CPeriph(I2C_TypeDef *periph)
	{
		init(periph);
	}
	I2CPeriph(I2C_TypeDef *periph, i2cTimingReg &timing)
	{
		init(periph, timing);
	}
	Error init(I2C_TypeDef *periph);
	Error init(I2C_TypeDef *periph, const i2cTimingReg &timing);
	void deinit(I2C_TypeDef *periph);

	bool is_ready();

	Error mem_read(uint16_t dev_address, uint16_t mem_address, uint32_t memadd_size, uint8_t *data, uint16_t size);
	Error mem_write(uint16_t dev_address, uint16_t mem_address, uint32_t memadd_size, uint8_t *data, uint16_t size);
	Error mem_write_IT(uint16_t dev_address, uint16_t mem_address, uint32_t memadd_size, uint8_t *data, uint16_t size);
	Error mem_write_dma(uint16_t dev_address, uint16_t mem_address, uint32_t memadd_size, uint8_t *data, uint16_t size);
	Error read(uint16_t dev_address, uint8_t *data, uint16_t size);
	Error write(uint16_t address, uint8_t *data, uint16_t size);
	void enable_IT(uint8_t pri1 = 2, uint8_t pri2 = 2);
	void disable_IT();
	void link_DMA_TX(DMA_HandleTypeDef *dmatx);
	void link_DMA_RX(DMA_HandleTypeDef *dmarx);

private:
	bool already_init = false;
	I2C_HandleTypeDef hal_i2c_;
	IRQn_Type i2c_irq_num_;
	IRQn_Type i2c_err_irq_num_;
	void i2c_error_handler();
	void isr();
};
#endif
