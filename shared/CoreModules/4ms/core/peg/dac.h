#pragma once
#include <stdint.h>

enum DACs {
	DAC_ENVA,
	DAC_ENVB,
};

void init_dac(uint32_t freq, void (*callbackfunc)(void));
void dac_out(enum DACs dac, uint16_t val);
void pause_dac_timer(void);
void resume_dac_timer(void);
