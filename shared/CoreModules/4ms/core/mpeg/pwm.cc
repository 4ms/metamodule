#include "main.hh"

namespace MetaModule::PEG
{

void MiniPEG::update_pwm(uint32_t pwmval, enum PwmOutputs pwmnum) {
	if (pwmnum >= NUM_PWMS)
		return;

    pwm_vals[pwmnum] = pwmval;
}

void MiniPEG::init_pwm(void) {

}

}