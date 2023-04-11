#pragma once

#include <cstdio>

class TriangleOscillator
{
public:
    enum State_t {RISING, FALLING};

public:
    TriangleOscillator() : outputInV(0.0f), state(State_t::RISING), running(false), cycling(false)
    {
        running = true;
    }

    void setRiseTimeInS(float val)
    {
        slopeRising = (MaxValInV - MinValInV) / val;
    }

    void setFallTimeInS(float val)
    {
        slopeFalling = (MinValInV - MaxValInV) / val;
    }

    void proceed(float timeInS)
    {
        if (running)
        {
            auto slope = state == State_t::RISING ? slopeRising : slopeFalling;
            auto increment = slope * timeInS;

            outputInV += increment;

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
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }
    }

    State_t getState() const
    {
        return state;
    }

    bool isRunning() const
    {
        return running;
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
    bool running;
    bool cycling;

    float slopeFalling;
    float slopeRising;

    //TODO: make configurable
    static constexpr float MaxValInV = 5.0f;
    static constexpr float MinValInV = -5.0f;
};