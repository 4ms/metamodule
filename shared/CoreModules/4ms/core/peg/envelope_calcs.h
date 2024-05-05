/*
 * envelope_calcs.h
 */

#pragma once

#include "pingable_env.h"
#include <stdint.h>

#define NUM_DIVMULTS 19

enum ShapeRegions {
	RAMPUP_EXP2LIN,
	RAMPUP2SYM_LIN2EXP,
	SYM_EXP2LOG,
	SYM2RAMPDOWN_LOG2LIN,
	RAMPDOWN_EXP2LIN,

	NUM_SHAPE_REGIONS
};
enum PureSkews { RAMPUP = 0, SYM = 127, RAMPDOWN = 255 };
enum PureCurves { EXPO = 0, LIN = 127, LOG = 255 };

int8_t get_clk_div_nominal(uint16_t adc_val);
uint32_t get_clk_div_time(int8_t clock_divide_amount, uint32_t clk_time);
uint32_t get_fall_time(uint8_t skew, uint32_t div_clk_time);
int16_t calc_curve(int16_t t_dacout, uint8_t cur_curve);
void calc_skew_and_curves(uint16_t shape, uint8_t *skew, uint8_t *next_curve_rise, uint8_t *next_curve_fall);
void calc_rise_fall_incs(struct PingableEnvelope *e);
void calc_div_clk_time(struct PingableEnvelope *e, uint32_t new_clk_time);
