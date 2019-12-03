#include "ui.hh"

void Params::update(Controls& controls) {
    freq[0] = controls.freq1CV.get() / 4095.0f;
    freq[1] = controls.freq2CV.get() / 4095.0f;
    res[0] = controls.res1CV.get() / 4095.0f;
    res[1] = controls.res2CV.get() / 4095.0f;
}

void Params::read(Controls& controls) {

}
