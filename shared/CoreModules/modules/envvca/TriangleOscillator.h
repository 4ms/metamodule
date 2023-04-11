#pragma once

#include <cstdio>

class TriangleOscillator
{
public:
    enum State_t {RISING, FALLING, IDLE};

public:
    TriangleOscillator() : outputInV(0.0f), state(State_t::IDLE), cycling(false), retriggerPending(false)
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

    void proceed(float timeInS)
    {
        if (state == State_t::IDLE)
        {
            if (cycling)
            {
                state = State_t::RISING;
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
                    state = State_t::IDLE;
                }
            }
            else if (retriggerPending)
            {
                state = State_t::RISING;
                retriggerPending = false;
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

private:
    float outputInV;
    State_t state;
    bool cycling;
    bool retriggerPending;

    float slopeFalling;
    float slopeRising;

    //TODO: make configurable
    static constexpr float MaxValInV = 5.0f;
    static constexpr float MinValInV = 0.0f;
};