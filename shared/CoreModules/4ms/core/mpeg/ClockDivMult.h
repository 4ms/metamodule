#pragma once

#include <array>
#include <cmath>
#include <optional>

#include "CoreModules/4ms/core/helpers/FlipFlop.h"
#include "CoreModules/4ms/core/helpers/EdgeDetector.h"


namespace MetaModule
{

class ClockDivMult
{
private:
enum outputState_t {LOW, HIGH};

enum operation_t {MULT, DIV};

struct factorType_t
{
    operation_t operation;
    uint32_t factor;
    uint32_t index;

    inline bool operator!=(factorType_t a) {
    if (a.operation == operation && a.factor == factor)
        return false;
    else
        return true;
    }
};

public:
    ClockDivMult() : factor(clockFactor[0]), clockDivCounter{0}, clockOutState(LOW), phase(0.f), processSyncPulse(false), clockOutRisingEdgeCounter(0), factorUpdated(false)
    {
        resetClocks();
    };

    void update(auto clockInput, auto now, auto inPeriod)
    {
        if(factorUpdated) 
        {
            calculateClockOutPeriod(factor);
            factorUpdated = false;
        }

        if (triggerEdgeDetectorClock(clockInput)) {
            setClockInPeriod(now, inPeriod);
            calculateClockOutPeriod(now, factor);

            if(clockIn.lastEventInTicks && clockIn.periodInTicks) {
                for (uint32_t index = 0; index < clockDivCounter.size(); index++) {
                    
                    clockDivCounter[index]++;

                    if(clockDivCounter[index] >= clockFactor[index].factor) {
                        clockDivCounter[index] = 0;
                    }
                }

                if(factor.operation == DIV) {

                    if(clockDivCounter[factor.index] == 0)
                    {
                        processSyncPulse = true;
                    }
                } else {
                    processSyncPulse = true;
                }
            }
        }

        updateClockOut(now, factor);
    }

    void setFactor(float potValue, std::optional<float> cvValue)
    {
        auto selector = potValue;

        if(cvValue.has_value()) {
            selector += std::clamp(*cvValue, cvMinInV, cvMaxInV) / cvMaxInV;
            selector = std::clamp(selector, 0.0f, 1.0f);
        }

        auto newFactor = clockFactor[uint32_t(std::round(selector * (clockFactor.size() - 1)))];

        if(factor != newFactor)
        {
            factor = newFactor;

            factorUpdated = true;
        }
    }

    void set_samplerate(float sr) {
        timeStepInS = 1.f /sr;

        triggerLength5msInTicks = uint32_t(std::round(0.005f / timeStepInS));
        triggerLengthMinimumInTicks = 2;
	}

    float getPhase()
    {
        return phase;
    }

    bool isDividing()
    {
        return factor.operation == DIV;
    }

    void rePhase()
    {
        for (uint32_t index = 0; index < clockDivCounter.size(); index++) 
        {
            clockDivCounter[index] = clockFactor[index].factor;
        }
    }

    std::optional<uint32_t> getOutPeriod()
    {
        return clockOut.periodInTicks;
    }

private:
        void setClockInPeriod(auto timestampInTicks, auto inPeriod) {
            clockIn.periodInTicks = inPeriod;

			clockIn.lastEventInTicks = timestampInTicks;
		}

		void calculateClockOutPeriod(factorType_t factor) {
			if(clockIn.periodInTicks) {
				if(factor.operation == MULT) {
					clockOut.periodInTicks = *clockIn.periodInTicks / factor.factor;
				} else if (factor.operation == DIV){
					clockOut.periodInTicks = *clockIn.periodInTicks * factor.factor;
				} else {
					clockOut.periodInTicks.reset();
				}
			}
		}

		void calculateClockOutPeriod(uint32_t timestampInTicks, factorType_t factor) {
			if(clockIn.periodInTicks) {
				if(factor.operation == MULT) {
					clockOut.periodInTicks = *clockIn.periodInTicks / factor.factor;
				} else if (factor.operation == DIV){
					clockOut.periodInTicks = *clockIn.periodInTicks * factor.factor;
				} else {
					clockOut.periodInTicks.reset();
				}

				if (!clockOut.lastEventInTicks) {
					clockOut.lastEventInTicks = timestampInTicks;
				}
			}
		}

		void updateClockOut(uint32_t timestampInTicks, factorType_t factor) {
			if(clockOut.periodInTicks) {
				if(clockOutIsLow()) {
					if (processSyncPulse == true) {
						clockOutRisingEdgeCounter = 0;

						setClockOutRisingEdge(timestampInTicks);

						processSyncPulse = false;
					} else if (factor.operation == MULT) {
						if(timestampInTicks >= (*clockOut.lastEventInTicks + *clockOut.periodInTicks) && clockOutRisingEdgeCounter < factor.factor) {
                            setClockOutRisingEdge(timestampInTicks);
						}
					}
				} else {
                    if (timestampInTicks >= (*clockOut.lastEventInTicks + triggerLengthMinimumInTicks)) {
						setClockOutFallingEdge();
					}
				}

                if (clockOut.lastEventInTicks)
                {
                    phase = float(timestampInTicks - *clockOut.lastEventInTicks) / float(*clockOut.periodInTicks);
                }
			}
		}

		bool clockOutIsLow() {
			return clockOutState == LOW;
		}

		void setClockOutRisingEdge(uint32_t timestampInTicks) {
			if(clockOutState == LOW) {
				clockOut.lastEventInTicks = timestampInTicks;
				clockOutRisingEdgeCounter++;
				clockOutState = HIGH;
			}
		}

		void setClockOutFallingEdge() {
			if(clockOutState == HIGH) {
				clockOutState = LOW;
			}
		}

		void resetClocks() {
			clockIn.lastEventInTicks.reset();
			clockIn.periodInTicks.reset();

			clockOut.lastEventInTicks.reset();
			clockOut.periodInTicks.reset();

			if(clockOutState == HIGH) {
				clockOutState = LOW;
			}
		}


private:
    static constexpr float cvMinInV = -5.f;
    static constexpr float cvMaxInV = 5.f;

private:
    static constexpr uint32_t maxIndexDivisions = 9;
    static constexpr std::array<factorType_t,21> clockFactor = {{
        {DIV, 32, 0},
        {DIV, 32, 1},
        {DIV, 16, 2},
        {DIV, 8, 3},
        {DIV, 7, 4},
        {DIV, 6, 5},
        {DIV, 5, 6},
        {DIV, 4, 7},
        {DIV, 3, 8},
        {DIV, 2, 9},
        {MULT, 1, 10},
        {MULT, 2, 11},
        {MULT, 3, 12},
        {MULT, 4, 13},
        {MULT, 5, 14},
        {MULT, 6, 15},
        {MULT, 7, 16},
        {MULT, 8, 17},
        {MULT, 12, 18},
        {MULT, 16, 19},
        {MULT, 16, 20}
    }};

private:
    float timeStepInS;
    uint32_t triggerLengthMinimumInTicks;
    uint32_t triggerLength5msInTicks;
    uint32_t triggerLengthInTicks;
    uint32_t ticks;
    std::array<uint32_t, maxIndexDivisions + 1> clockDivCounter;
    factorType_t factor;
    outputState_t clockOutState;
    float phase;
    bool processSyncPulse;
    uint32_t clockOutRisingEdgeCounter;
    bool factorUpdated;

    struct clockMeasures
    {
        std::optional<uint32_t> lastEventInTicks;
        std::optional<uint32_t> periodInTicks;
    };

    clockMeasures clockIn;
    clockMeasures clockOut;

private:
    EdgeDetector triggerEdgeDetectorClock;
};

} // namespace MetaModule