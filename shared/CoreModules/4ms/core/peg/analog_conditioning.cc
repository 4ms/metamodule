#include "analog_conditioning.h"
#include "adc.h"
#include "adc_pins.h"
#include "drivers/stm32xx.h"
// #include "globals.h"

uint16_t adc_dma_buffer[NUM_ADCS];
uint16_t *adc_cv_dma_buffer = &(adc_dma_buffer[0]);
uint16_t *adc_pot_dma_buffer = &(adc_dma_buffer[NUM_CV_ADCS]);

analog_t analog[NUM_ADCS];

//Private:
void setup_fir_lpf(void);

void init_analog_conditioning(void) {
	builtinAdcSetup adc_setup[NUM_ADCS];
	builtinAdcSetup *adc_cv_setup = &(adc_setup[0]);
	builtinAdcSetup *adc_pot_setup = &(adc_setup[NUM_CV_ADCS]);

	adc_cv_setup[ADC_CV_SHAPE].gpio = CV_SHAPE_GPIO_Port;
	adc_cv_setup[ADC_CV_SHAPE].pin = CV_SHAPE_Pin;
	adc_cv_setup[ADC_CV_SHAPE].channel = CV_SHAPE_Channel;
	adc_cv_setup[ADC_CV_SHAPE].sample_time = FAST_SAMPLE;

	adc_cv_setup[ADC_CV_DIVMULT].gpio = CV_DIVMULT_GPIO_Port;
	adc_cv_setup[ADC_CV_DIVMULT].pin = CV_DIVMULT_Pin;
	adc_cv_setup[ADC_CV_DIVMULT].channel = CV_DIVMULT_Channel;
	adc_cv_setup[ADC_CV_DIVMULT].sample_time = FAST_SAMPLE;

	adc_pot_setup[ADC_POT_SCALE].gpio = POT_SCALE_GPIO_Port;
	adc_pot_setup[ADC_POT_SCALE].pin = POT_SCALE_Pin;
	adc_pot_setup[ADC_POT_SCALE].channel = POT_SCALE_Channel;
	adc_pot_setup[ADC_POT_SCALE].sample_time = SLOW_SAMPLE;

	adc_pot_setup[ADC_POT_OFFSET].gpio = POT_OFFSET_GPIO_Port;
	adc_pot_setup[ADC_POT_OFFSET].pin = POT_OFFSET_Pin;
	adc_pot_setup[ADC_POT_OFFSET].channel = POT_OFFSET_Channel;
	adc_pot_setup[ADC_POT_OFFSET].sample_time = SLOW_SAMPLE;

	adc_pot_setup[ADC_POT_SHAPE].gpio = POT_SHAPE_GPIO_Port;
	adc_pot_setup[ADC_POT_SHAPE].pin = POT_SHAPE_Pin;
	adc_pot_setup[ADC_POT_SHAPE].channel = POT_SHAPE_Channel;
	adc_pot_setup[ADC_POT_SHAPE].sample_time = SLOW_SAMPLE;

	adc_pot_setup[ADC_POT_DIVMULT].gpio = POT_DIVMULT_GPIO_Port;
	adc_pot_setup[ADC_POT_DIVMULT].pin = POT_DIVMULT_Pin;
	adc_pot_setup[ADC_POT_DIVMULT].channel = POT_DIVMULT_Channel;
	adc_pot_setup[ADC_POT_DIVMULT].sample_time = SLOW_SAMPLE;

	if (ADC2 == nullptr) {
		// F423 and units with 1 ADC
		ADC_Init(ADC1, adc_dma_buffer, NUM_ADCS, adc_setup, OVERSAMPLE_RATIO); //16
	} else {
		// F746, G431 and units with 2 ADC
		ADC_Init(ADC1, adc_cv_dma_buffer, NUM_CV_ADCS, adc_cv_setup, OVERSAMPLE_RATIO); //16
		ADC_Init(ADC2, adc_pot_dma_buffer, NUM_POT_ADCS, adc_pot_setup, OVERSAMPLE_RATIO);
	}

	analog[POT_DIVMULT].polarity = AP_UNIPOLAR;
	analog[POT_SHAPE].polarity = AP_UNIPOLAR;
	analog[POT_OFFSET].polarity = AP_UNIPOLAR;
	analog[POT_SCALE].polarity = AP_UNIPOLAR;

	analog[CV_SHAPE].polarity = AP_BIPOLAR;
	analog[CV_DIVMULT].polarity = AP_BIPOLAR;

	setup_fir_lpf();
}

void setup_fir_lpf(void) {
	uint8_t analog_id;
	uint16_t initial_value;

	for (analog_id = 0; analog_id < NUM_ADCS; analog_id++) {
		if (analog[analog_id].polarity == AP_BIPOLAR)
			initial_value = 2048;
		else
			initial_value = 0;

		analog[analog_id].lpf_sum = initial_value * MAX_LPF_SIZE;
		analog[analog_id].lpf_val = initial_value;
	}
}

//todo: make this a system calibration
const int16_t adc_cal_offset[NUM_ADCS] = {0, 48, 48, 0, 0, 0};

//todo: try: new_value += (new_value - old_value) * abs(new_value - old_value) * COEF
//where COEF might be 0.1

void condition_analog(void) {
	uint8_t i, pot_i;
	int32_t t;
	static uint8_t oversample_ctr = 0;

	for (i = 0; i < NUM_CV_ADCS; i++) {
		analog[i].lpf_sum += adc_cv_dma_buffer[i];
	}
	for (pot_i = 0; pot_i < NUM_POT_ADCS; pot_i++) {
		analog[i++].lpf_sum += adc_pot_dma_buffer[pot_i];
	}

	if (++oversample_ctr >= 16) {
		oversample_ctr = 0;
		for (i = 0; i < NUM_ADCS; i++) {
			t = (analog[i].lpf_sum >> 4) + adc_cal_offset[i];
			if (t > 4095)
				analog[i].lpf_val = 4095;
			else if (t < 0)
				analog[i].lpf_val = 0;
			else
				analog[i].lpf_val = t;

			analog[i].lpf_sum = 0;
		}
	}
}
