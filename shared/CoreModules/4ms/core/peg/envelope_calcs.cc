#include "envelope_calcs.hh"
#include <algorithm>

namespace MetaModule::PEG
{


int8_t PEGEnvelopeCalcs::get_clk_div_nominal(uint16_t adc_val) {
    for (uint8_t i = 0; i < NUM_DIVMULTS; i++) {
        if (adc_val <= midpt_array[i])
            return (P_array[i]);
    }
    return (P_array[NUM_DIVMULTS - 1]);
}

void PEGEnvelopeCalcs::calc_skew_and_curves(uint16_t skewadc, uint16_t shapeadc, uint8_t *skew, uint8_t *next_curve_rise, uint8_t *next_curve_fall) {
		//TODO
		*skew = std::clamp(skewadc / 16, 0, 255); //0..4095 => 0..255

		//TODO: select curve from shapeadc
		*next_curve_rise = PureCurves::LIN;
		*next_curve_fall = PureCurves::LIN;
	}


}