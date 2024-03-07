#include <optional>
#include <cstdint>

class LongPressDetector
{
public:
    using Timestamp_t = uint32_t;
    LongPressDetector(Timestamp_t thres)
        : threshold(thres)
        , pressDuration(0)
    {
    }

    bool operator()(Timestamp_t now, bool val)
    {
        if (lastCall)
        {
            if (val)
            {   
                pressDuration += (now - *lastCall);
                if (pressDuration >= threshold)
                {
                    pressDuration = 0;
                    return true;
                }
            }
            else
            {
                pressDuration = 0;
            }
        }
        lastCall = now;
        return false;
    }
private:
    const Timestamp_t threshold;
    std::optional<Timestamp_t> lastCall;
    Timestamp_t pressDuration;
};