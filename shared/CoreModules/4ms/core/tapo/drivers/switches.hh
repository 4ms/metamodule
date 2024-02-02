// Copyright 2016 Matthias Puech.
//
// Author: Matthias Puech <matthias.puech@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
// 
// See http://creativecommons.org/licenses/MIT/ for more information.
//
// -----------------------------------------------------------------------------
//
// Driver for the front panel switches.

#ifndef SWITCHES_H_
#define SWITCHES_H_

#include "drivers/buttons.hh"
#include "stmlib/stmlib.h"

#include <algorithm>

using namespace std;

const uint8_t kNumSwitches = 2;
const uint8_t kNumBitPerSwitch = 2;

enum SwitchNames {
  SWITCH_EDIT,
  SWITCH_VELO,
};


class Switches {
 public:
  void Init() {}

  void Read() {
    // for (int i=0; i<kNumSwitches; i++) {
    //   previous_switch_state_[i] = switch_state_[i];
    //   switch_state_[i] = 0;
    //   for (int j=0; j<kNumBitPerSwitch; j++) {
    //     int idx = j + kNumBitPerSwitch * i;
    //     switch_state_[i] = switch_state_[i] << 1
    //       | !GPIO_ReadInputDataBit(switch_pins[idx].gpio,
    //                               switch_pins[idx].pin);
    //   }
    // }
  }

  void set(uint8_t channel, uint8_t val)
  {
    previous_switch_state_[channel] = switch_state_[channel];
    switch_state_[channel] = val;
  }

  inline uint8_t state(int i) { return switch_state_[i]; }
  inline uint8_t switched(int i) {
    return switch_state_[i] != previous_switch_state_[i];
  }

private:
  uint8_t switch_state_[kNumSwitches];
  uint8_t previous_switch_state_[kNumSwitches];
};

#endif
