#pragma once

#include <cstdio>

class TriangleOscillator
{
public:
	// FIXME: FOLLOW state is orthagonal to [RISE or FALL] state
    enum State_t {RISING, FALLING, FOLLOW};

public:
    TriangleOscillator() : outputInV(0.0f), state(State_t::FOLLOW), cycling(false), retriggerPending(false), targetVoltage(0.0f)
    {
    }

    void setRiseTimeInS(float val)
    {
        slopeRising = (MaxValInV - MinValInV) / val;
    }

    void setFallTimeInS(float val)
    {
        slopeFalling = (MinValInV - MaxValInV) / val;
    }

    void doRetrigger()
    {
        retriggerPending = true;
    }

    void setTargetVoltage(float val)
    {
        targetVoltage = val;
    }

    void proceed(float timeInS)
    {
		if (retriggerPending)
		{
			state = State_t::RISING;
			retriggerPending = false;
		}

        if (state == State_t::FOLLOW)
        {
            if (cycling)
            {
                state = State_t::RISING;
            }
            else
            {
                if (outputInV < targetVoltage)
                {
                    outputInV += slopeRising * timeInS;
                    outputInV = std::min(targetVoltage, outputInV);
                }
                else
                {
                    outputInV += slopeFalling * timeInS;
                    outputInV = std::max(targetVoltage, outputInV);
                }
            }
        }
        else if (state == State_t::RISING)
        {
            outputInV += slopeRising * timeInS;

            if (outputInV > MaxValInV)
            {
                outputInV = MaxValInV - (outputInV - MaxValInV);
                state = State_t::FALLING;
            }
        }
        else
        {
            outputInV += slopeFalling * timeInS;

            if (outputInV < MinValInV)
            {
                if (cycling)
                {
                    outputInV = MinValInV + (MinValInV - outputInV);
                    state = State_t::RISING;
                }
                else
                {
                    outputInV = MinValInV;
                    state = State_t::FOLLOW;
                }
            }
        }
    }

    State_t getState() const
    {
        return state;
    }

    void setCycling(bool val)
    {
        cycling = val;
    }

    float getOutput() const
    {
        return outputInV;
    }

// private:
    float outputInV;
    State_t state;
    bool cycling;
    bool retriggerPending;
    float targetVoltage;

    float slopeFalling = 0.5f;
    float slopeRising = 0.5f;

    static constexpr float MaxValInV = 5.0f;
    static constexpr float MinValInV = 0.0f;
};
