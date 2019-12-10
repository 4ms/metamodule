#include "ui.hh"
#include "math.hh"

void Params::update() {
    freq[0] = controls.freq1_cv.get() / 4095.0f;
    freq[1] = controls.freq2_cv.get() / 4095.0f;

    res[0] = controls.res1_cv.get() / 4095.0f;
    res[1] = controls.res2_cv.get() / 4095.0f;

    if (controls.pads.just_touched(0)) {
        mode[0] = wrap<5>(mode[0]+1);
    }
    if (controls.pads.just_touched(1)) {
        mode[1] = wrap<5>(mode[1]+1);
    }
}

void Params::read() {

}
