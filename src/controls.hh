#include <stm32f7xx.h>
#include "stm32f7xx_ll_gpio.h"
#include "stm32f7xx_ll_adc.h"
#include "adc_builtin_driver.hh"
#include "touch.hh"
#include <array>

// ADC_TypeDef * const CV_ADC = ADC1;
const uint32_t kNumAdcChans = 4;
const AdcChan freq1cv_adc = {ADCChan10, {ANALOG, LL_GPIO_PIN_0, GPIOC}, LL_ADC_SAMPLINGTIME_144CYCLES};
const AdcChan res1cv_adc = {ADCChan11, {ANALOG, LL_GPIO_PIN_1, GPIOC}, LL_ADC_SAMPLINGTIME_144CYCLES};
const AdcChan freq2cv_adc = {ADCChan12, {ANALOG, LL_GPIO_PIN_2, GPIOC}, LL_ADC_SAMPLINGTIME_144CYCLES};
const AdcChan res2cv_adc = {ADCChan13, {ANALOG, LL_GPIO_PIN_3, GPIOC}, LL_ADC_SAMPLINGTIME_144CYCLES};

struct CVJack {
    uint16_t rawval;
    uint32_t os_buffer;
    uint16_t os_val;
};
struct Button {
    uint32_t just_pressed;
    uint32_t just_released;
    uint32_t state;
};

template<class T, int size>
struct OverSampleBuffer {
public:
    OverSampleBuffer() : bitshift_(Log2<size>::val) {}

    void add_val(T val_)
    {
        buff_ += val_;
        if (++idx_>size)
        {
            idx_ = 0;
            val_ = buff_ >> bitshift_;
        }
    }
    T val() {return val_;}

private:
    int bitshift_;
    T buff_ = 0;
    T val_ = 0;
    int idx_ = 0;
};

class Controls {
public:
    Controls();
    static void read();

private:
    AdcPeriph<1> ADC_;
    //todo: ADcChan constructor calls add_channel():
    //how to connect to AdcPeriph?
    //AdcPeriph<ADC1, 4/*#channels*/> {freq1cv_adc, res1cv_adc, freq2cv_adc, res2cv_adc};
    //AdcChan freq1adc {ADC1, freq1cv_adc_init};
    //or
    //AdcPeriph ADC_{Adc1 /*enum for 1*/};
    //AdcChan<Adc1, AdcChan0> freq1cv {freq1cv_pin}; //or
    //AdcChan freq1cv {Adc1, AdcChan0, freq1cv_pin};
public:
    static uint16_t adc_raw[kNumAdcChans];
    static std::array<uint16_t, kNumAdcChans> adcraw;


public:
    static std::array<OverSampleBuffer<uint16_t, 4>, kNumAdcChans> CV;

    static int32_t rotary_turn[2];  //-1, 0, 1
    static Button rotary_button[2]; //0, 1
    static TouchCtl pads;
};
