#include "ui.hh"

void Params::update(Controls& controls) {
    freq[0] = controls.freq1_cv.get() / 4095.0f;
    freq[1] = controls.freq2_cv.get() / 4095.0f;
    res[0] = controls.res1_cv.get() / 4095.0f;
    res[1] = controls.res2_cv.get() / 4095.0f;
}

void Params::read(Controls& controls) {

}
