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
        printf("Trigger\n");
        retriggerPending = true;
    }

    void proceed(float timeInS)
    {
        if (state == State_t::IDLE and cycling)
        {
            state = State_t::RISING;
        }

        auto getSlope = [this](auto val)
        {
            switch (val)
            {
                case State_t::RISING: return slopeRising;
                case State_t::FALLING: return slopeFalling;
                case State_t::IDLE: return 0.0f;
                default: return 0.0f;
            }
        };
        
        outputInV += getSlope(state) * timeInS;

        // wrap as long as needed
        // realistically only a single wrap will occur though
        while (true)
        {
            if (state == State_t::RISING and outputInV > MaxValInV)
            {
                outputInV = MaxValInV - (outputInV - MaxValInV);
                state = State_t::FALLING;
            }
            else if (state == State_t::FALLING and outputInV < MinValInV)
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
                    break;
                }
            }
            else
            {
                break;
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