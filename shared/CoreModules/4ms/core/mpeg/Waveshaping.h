#pragma once

#include <algorithm>
#include "util/math.hh"

#include "log4096.h"

class Waveshaping
{
public:
    Waveshaping() : shapeType(0), skew(0), next_curve_rise(0), next_curve_fall(0), relativeFallTime(0.5), limit_skew(false), state(NONE)
    {
        relativeRiseTime = 1.f - relativeFallTime;
    };

    float shape(float phase)
    {
        float segmentPhase = 0.f;
        uint8_t segmentShape = 0;
		auto previousState = state;

        if (phase <= relativeRiseTime)
        {
			state = RISE;
			if (state != previousState)
			{
				updateShape();
			}

            segmentPhase = phase / relativeRiseTime;
            segmentShape = curve_rise;
        }
        else
        {
			state = FALL;
			if (state != previousState)
			{
				updateShape();
			}
            segmentPhase = 1- ((phase - relativeRiseTime) / relativeFallTime);
            segmentShape = curve_fall;
        }

        auto curve = calc_curve(int16_t(segmentPhase*4095), segmentShape);

        return float(curve) / 4095.f;
    }


    void setNextShape(float val)
    {
        shapeType = uint16_t(std::clamp(val, 0.f, 1.f) * 4095.f);

        calc_skew_and_curves(shapeType, &skew, &next_curve_rise, &next_curve_fall);
        auto absoluteFallTime = get_fall_time(skew, std::numeric_limits<uint32_t>::max());
        relativeFallTime = float(absoluteFallTime) / float(std::numeric_limits<uint32_t>::max());
        relativeRiseTime = 1.f - relativeFallTime;

        // printf("Absolute fall time: %u Relative fall time: %.8f\n", absoluteFallTime, float(absoluteFallTime) / float(std::numeric_limits<uint32_t>::max()));
    }

	void updateShape()
	{
		curve_rise = next_curve_rise;
		curve_fall = next_curve_fall;
	}

private:
    uint16_t shapeType;
    float relativeFallTime;
    float relativeRiseTime;

private:
	enum State_t {RISE, FALL, NONE};
	State_t state;

private:
    uint8_t skew;
    uint8_t next_curve_rise;
    uint8_t next_curve_fall;
    uint8_t curve_rise;
    uint8_t curve_fall;
    bool limit_skew;

private:
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

    static constexpr std::array region_starts = {0, 900, 1450, 2645, 3195, 4096};
    static constexpr std::array region_sizes = MathTools::array_adj_diff(region_starts);

    #define LIMIT_SKEW_TIME 150	 //100 = 2.25ms, 200 = 5ms, 500=12ms

    //skew: 0..255, 0 means fall=min
    // TODO: use division, check it uses SDIV
    uint32_t get_fall_time(uint8_t skew, uint32_t div_clk_time) {
    	// return div_clk_time/2;

    	uint32_t skew_portion, u;
    	uint8_t rev_skew;

    	if (div_clk_time > 0xFFFFFF)
    		skew_portion = (div_clk_time >> 8) * skew;
    	else
    		skew_portion = (skew * div_clk_time) >> 8;

    	if (!limit_skew || (div_clk_time < (LIMIT_SKEW_TIME * 2))) {
    		if (skew == 0)
    			return 30;

    		else if (skew == 1)
    			return 40;

    		else if (skew == 2)
    			return 50;

    		else if (skew <= 25) {
    			//return smaller of skew_portion and squared link funcion, but at least 50
    			if (skew_portion < 50)
    				skew_portion = 50;
    			u = skew * skew * 2;
    			return (skew_portion < u) ? skew_portion : u;

    		} else if (skew >= 255)
    			return (div_clk_time - 20);

    		else if (skew > 200) {
    			if (skew_portion > (div_clk_time - 20))
    				skew_portion = div_clk_time - 20;

    			rev_skew = 255 - skew;
    			u = rev_skew * rev_skew * 2;

    			if (u > (div_clk_time - 20)) {
    				return skew_portion;
    			} else {
    				u = div_clk_time - u;
    				return (skew_portion > u) ? skew_portion : u;
    			}
    		}

    		else if ((skew > 125) && (skew <= 129))
    			return (div_clk_time >> 1);

    		else
    			return (skew * (div_clk_time >> 8));
    	}

    	else
    	{ //LIMIT_SKEW

    		if ((skew > 125) && (skew <= 129))
    			return (div_clk_time >> 1);
    		else {
    			if (skew_portion < LIMIT_SKEW_TIME)
    				skew_portion = LIMIT_SKEW_TIME;
    			if (skew_portion > (div_clk_time - LIMIT_SKEW_TIME))
    				skew_portion = div_clk_time - LIMIT_SKEW_TIME;

    			return skew_portion;
    		}
    	}
    }

    // shape: 0..4095 (adc value)
    // returns skew: 0..255
    // returns next_curve_rise and _fall: 0..255: expo/linear/log
    void calc_skew_and_curves(uint16_t shape, uint8_t *skew, uint8_t *next_curve_rise, uint8_t *next_curve_fall) {
    	if (shape > region_starts.back())
    		shape = region_starts.back();
    	int i = 1;
    	while (shape >= region_starts[i])
    		i++;
    	uint16_t shape_region = i - 1;

    	uint16_t shape_variation = shape - region_starts[shape_region];
    	uint32_t var_127 = (shape_variation << 7) / region_sizes[shape_region];

    	switch (shape_region) {
    		case RAMPUP_EXP2LIN:
    			*skew = RAMPUP;
    			*next_curve_rise = morph_exp2lin(var_127);
    			*next_curve_fall = LIN;
    			break;

    		case RAMPUP2SYM_LIN2EXP:
    			*skew = var_127;
    			*next_curve_rise = morph_lin2exp(var_127);
    			*next_curve_fall = morph_lin2exp(var_127); //was EXPO
    			break;

    		case SYM_EXP2LOG:
    			*skew = SYM;
    			*next_curve_rise = morph_exp2log(var_127);
    			*next_curve_fall = morph_exp2log(var_127);
    			break;

    		case SYM2RAMPDOWN_LOG2LIN:
    			*skew = var_127 + 128;
    			*next_curve_rise = morph_log2lin(var_127); //255 - var_127 * 2;
    			*next_curve_fall = morph_log2lin(var_127);
    			break;

    		default:
    		case RAMPDOWN_EXP2LIN:
    			*skew = RAMPDOWN;
    			*next_curve_rise = LIN;
    			*next_curve_fall = morph_lin2exp(var_127);
    			break;
    	}
    }

    private:
    //phase: 0..4095
    //cur_curve: 0..255, curve to use: 0=expo, 127/128=linear, 255=log (interpolates)
    //returns: 0..4095 dac value
    int16_t calc_curve(int16_t phase, uint8_t cur_curve) {
    	if (phase > 4095)
    		phase = 4095;

    	if (cur_curve > 119 && cur_curve < 139)
    		return phase;

    	else if (cur_curve <= 119) {
    		uint16_t t_inv_loga = 4095 - log4096[4095 - phase];
    		return MathTools::interpolate<119>(t_inv_loga, phase, cur_curve);
    	}

    	else
    	{ //cur_curve>=139
    		uint16_t t_loga = log4096[phase];
    		return MathTools::interpolate<139>(phase, t_loga, cur_curve - 139);
    	}
    }

    constexpr uint32_t morph_exp2lin(uint32_t x) {
    	//0..127 => 0..127
    	return x;
    }
    constexpr uint32_t morph_lin2exp(uint32_t x) {
    	//0..127 => 127..0
    	return 127 - x;
    }
    constexpr uint32_t morph_exp2log(uint32_t x) {
    	//0..127 => 0..255
    	return x * 2;
    }
    constexpr uint32_t morph_log2exp(uint32_t x) {
    	//0..127 => 255..0
    	return 255 - x * 2;
    }
    constexpr uint32_t morph_log2lin(uint32_t x) {
    	//0..127 => 255..128
    	return 255 - x;
    }
};