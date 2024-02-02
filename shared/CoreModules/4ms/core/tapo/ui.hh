// Copyright 2016 Matthias Puech.
//
// Author: Matthias Puech <matthias.puech@gmail.com>
// Based on code by: Olivier Gillet <ol.gillet@gmail.com>
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
// User interface

#ifndef UI_H_
#define UI_H_

#include "stmlib/stmlib.h"
#include "stmlib/ui/event_queue.h"

#include "drivers/leds.hh"
#include "drivers/buttons.hh"
#include "drivers/switches.hh"
#include "parameters.hh"
#include "multitap_delay.hh"
#include "control.hh"
#include "persistent.hh"

enum UiMode {
  UI_MODE_SPLASH,
  UI_MODE_NORMAL,
  UI_MODE_SETTINGS,
  UI_MODE_PANIC,
  UI_MODE_CONFIRM_SAVE,
  UI_MODE_CONFIRM_RESET_TO_FACTORY_DEFAULT,
  UI_MODE_CONFIRM_CALIBRATION,
  UI_MODE_LAST
};

enum SettingsPages {
  PAGE_VELOCITY_PARAMETER = 0,
  PAGE_BANK = 1,
  PAGE_PANNING_MODE = 2,
  PAGE_SEQUENCER = 3,
};

class Ui {
 public:
  void Init(MultitapDelay* delay, Parameters* parameters);
  void Poll();
  void DoEvents();
  void Panic();

  void ReadParameters() {
    control_.Read(parameters_, sequencer_mode_);

    // this function also counts the blocks processed, so:
    if (sample_counter_to_next_slot_ > 0.0f) {
      // decrement counter
      sample_counter_to_next_slot_ -= kBlockSize;

      // if it reaches 0, switch to current slot
      if (sample_counter_to_next_slot_ <= 0.0f) {
        current_slot_ = next_slot_;
        next_slot_ = -1;
      }
    }
  }

  void PingSaveLed();
  void PingGateLed();
  void PingResetLed();
  void PingMeter(TapType tap_type, float velocity);
  void SlotModified();

  void SequencerStep(float morph_time);

  static Ui* instance_;

 private:
  void OnButtonPressed(const stmlib::Event& e);
  void OnButtonReleased(const stmlib::Event& e);
  void OnSwitchSwitched(const stmlib::Event& e);
  void ParseSettings();
  void ParseSettingsCurrentPage();
  void SaveSettings();
  void PaintLeds();
  void LoadSlot(uint8_t slot);

  stmlib::EventQueue<16> queue_;

  Persistent persistent_;
  Control control_;
  MultitapDelay* delay_;
  Parameters* parameters_;
  
  Leds leds_;

  Buttons buttons_;
  Switches switches_;
  uint32_t press_time_[kNumButtons];
  uint32_t long_press_time_[kNumButtons];
  UiMode mode_;
  int settings_page_;           // 0..4
  int settings_item_[4];
  uint16_t animation_counter_;
  uint16_t ignore_releases_;
  uint8_t bank_;
  int8_t current_slot_;
  int8_t next_slot_;
  float sample_counter_to_next_slot_;
  int8_t save_candidate_slot_;

  uint16_t ping_gate_led_counter_;
  uint16_t ping_save_led_counter_;
  uint16_t ping_reset_counter_;

  float velocity_meter_;
  LedColor velocity_meter_color_;

  bool sequencer_mode_;
  bool settings_changed_;
};

#endif
