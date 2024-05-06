#include <optional>
#include <cstdint>

class LongPressDetector
{
public:
    LongPressDetector(float thresInS)
        : thresholdInS(thresInS)
        , pressDurationInS(0.f)
    {
    }

    bool operator()(bool val)
    {
        if (val)
        {   
            pressDurationInS += timeStepInS;
            if (pressDurationInS >= thresholdInS)
            {
                pressDurationInS = 0.f;
                return true;
            }
        }
        else
        {
            pressDurationInS = 0.f;
        }

        return false;
    }

    void set_samplerate(float sr) {
        timeStepInS = 1.f / sr;
    }
    
private:
    const float thresholdInS;
    float pressDurationInS;

private:
    float timeStepInS = 1.f / 48000.f;
};