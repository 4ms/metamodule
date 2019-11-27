#include <stm32f7xx.h>
#include "stm32f7xx_ll_gpio.h"
#include "stm32f7xx_ll_adc.h"
#include "adc_builtin_driver.hh"
#include "touch.hh"
#include "filter.hh"
#include "pin.hh"

#include <array>

const uint32_t kNumAdcChans = 4;
const int kOverSampleAmt = 4;

//Todo: put Button and CVJack in their own files
struct Button {
    uint32_t just_pressed;
    uint32_t just_released;
    uint32_t state;
};


struct CVJack {
    CVJack(uint16_t &raw_input) : raw_input_(raw_input) {}

    CVJack();
    void set_input_source(uint16_t &raw_input) {raw_input_ = raw_input;}

    void read() {oversampler_.add_val(raw_input_);}
    uint16_t get() {return oversampler_.val();}

private:
    uint16_t &raw_input_;
    Oversampler<uint16_t, kOverSampleAmt> oversampler_;
};

struct JackSense {
    JackSense(Pin pin) : pin_(pin) {}
    bool is_plugged() {return plugged_;}

private:
    Pin pin_;
    bool plugged_ = false;
};

struct Hardware {
    //Note: These are created on the stack, then Pin() ctor and add_channel are called, copying the values to/from stack.
    //      It's not clear, but there might be several copies happening (all are destroyed, but it makes initialization slower than necessary.
    //Todo: Compare to using rvalue references to move, and compare timing when optimized

    AdcChan<ADC_1> freq1cv_adc {ADCChan10, {LL_GPIO_PIN_0, GPIOC, ANALOG}, LL_ADC_SAMPLINGTIME_144CYCLES};
    AdcChan<ADC_1> res1cv_adc {ADCChan11, {LL_GPIO_PIN_1, GPIOC, ANALOG}, LL_ADC_SAMPLINGTIME_144CYCLES};
    AdcChan<ADC_1> freq2cv_adc {ADCChan12, {LL_GPIO_PIN_2, GPIOC, ANALOG}, LL_ADC_SAMPLINGTIME_144CYCLES};
    AdcChan<ADC_1> res2cv_adc {ADCChan13, {LL_GPIO_PIN_3, GPIOC, ANALOG}, LL_ADC_SAMPLINGTIME_144CYCLES};

    Pin freq2_sense_pin {LL_GPIO_PIN_14, GPIOC, INPUT, UP};
    Pin res2_sense_pin {LL_GPIO_PIN_4, GPIOC, INPUT, UP};
    Pin in1_sense_pin {LL_GPIO_PIN_13, GPIOC, INPUT, UP};
    Pin in2_sense_pin {LL_GPIO_PIN_15, GPIOC, INPUT, UP};
};


//Controls class reads raw hardware, does fast conditioning (oversampling/debouncing)
//and stores values into objects representing each hardware object
struct Controls : public Hardware
{
    static inline std::array<uint16_t, kNumAdcChans> adc_raw;

    static inline CVJack freq1CV { adc_raw[0] };
    static inline CVJack res1CV { adc_raw[1] };
    static inline CVJack freq2CV { adc_raw[2] };
    static inline CVJack res2CV { adc_raw[3] };

    //Todo: either allocate 16 uint16_t's per AdcPeriph<>, or dynamically allocate using std::vector<>... but somehow keep the DMA destination as part of AdcPeriph<>
    //And make an accessor in AdcChan to grab the appropriate value: AdcPeriph<>.get(uint8_t adc_rank_num)  {return dma_buffer(adc_rank_num);}
    //static inline CVJack freq1CV { Hardware::freq1cv_adc };
    //ctor sets CVJack.adc_num_ to Hardware::freq1cv_adc.rank_num, and CVJack.adc_periph_num_ to ::.adc_num_
    //get() calls AdcPeriph<adc_periph_num_>::get(adc_rank_num)

    JackSense freq2_sense {freq2_sense_pin};
    JackSense res2_sense {res2_sense_pin};
    JackSense in1_sense {in1_sense_pin};
    JackSense in2_sense {in2_sense_pin};

    static int32_t rotary_turn[2];  //-1, 0, 1
    static Button rotary_button[2]; //0, 1
    static TouchCtl pads;

    Controls();
    static void read(); //Note: must be static so it can be called from IRQHandler
};
