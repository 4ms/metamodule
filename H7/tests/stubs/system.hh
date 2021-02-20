#pragma once

class System {

	void SetVectorTable(uint32_t reset_address)
	{
	}

public:
	System()
	{
	}

	template<typename X>
	static void fake_enable(X x)
	{
	}

	template<typename X, typename Y>
	static uint32_t fake_read(X x, Y y)
	{
		return 0;
	}

	static void _ll_enable_gpio_rcc(uint32_t periph) { fake_enable(periph); }
	static bool _ll_is_enabled_gpio_rcc(uint32_t periph) { return false; }

	static void enable_gpio_rcc(GPIO_TypeDef *port)
	{
	}

	static constexpr void enable_adc_rcc(ADC_TypeDef *ADCx)
	{
	}

	static constexpr void enable_dma_rcc(DMA_TypeDef *DMAx)
	{
	}

	static constexpr void enable_i2c_rcc(I2C_TypeDef *I2Cx)
	{
	}
	static constexpr void disable_i2c_rcc(I2C_TypeDef *I2Cx)
	{
	}
	static constexpr void enable_sai_rcc(SAI_TypeDef *SAIx)
	{
	}
	static constexpr void disable_sai_rcc(SAI_TypeDef *SAIx)
	{
	}

	static void enable_tim_rcc(TIM_TypeDef *TIM)
	{
	}

	static inline constexpr uint8_t kTimPeriphMax = 17;

	static uint8_t tim_periph_to_num(TIM_TypeDef *TIM)
	{
		return 0;
	}
};
