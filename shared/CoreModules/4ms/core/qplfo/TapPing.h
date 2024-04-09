#pragma once
#include <cstdint>
#include <optional>

class TapPing
{
public:
    TapPing() :
        lastTap(0), tapPeriod(0), lastTapOut(0), lastTapButtonState(false), outputActive(true)
    {

    }

    void inputButton(auto now, auto tapButtonState) {
		if(tapButtonState == true && lastTapButtonState == false) {
			tapPeriod = now - lastTap;
			lastTap = now;
			lastTapOut = now;
			outputActive = true;
		}

		lastTapButtonState = tapButtonState;
	}

    bool updateTapOut(auto now) {
		bool pingOut = false;

		if(tapPeriod != 0 && outputActive) {
			if(now == lastTapOut + tapPeriod) {
				pingOut = true;
				lastTapOut = now;
			}		
		}

		return pingOut;
	}

    std::optional<uint32_t> getPeriod() {
        if (tapPeriod != 0) {
            return tapPeriod;
        }

        return std::nullopt;
    }

	void deactivateOuput() {
		outputActive = false;
	}

private:
    uint32_t lastTap;
	uint32_t tapPeriod;
	uint32_t lastTapOut;
    bool lastTapButtonState;
	bool outputActive;
};