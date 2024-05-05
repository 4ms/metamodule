/*
 * params.h
 */

#pragma once

#include <stdint.h>

// enum AnalogParams {
// 	DIVMULT,
// 	SHAPE,
// 	SCALE,
// 	OFFSET,

// 	NUM_ANALOG_PARAMS
// };

void update_adc_params(uint8_t force_params_update);
void init_params(void);
