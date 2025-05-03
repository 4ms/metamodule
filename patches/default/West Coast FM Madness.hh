// Automatically generated, do not edit
static const char patch_West_Coast_FM_Madness[] =
	R"(
PatchData:
  patch_name: West Coast FM Madness
  description: 'FM oscillators, lowpass gates, random voltages, and cooky delay + reverb. '
  module_slugs:
    0: '4msCompany:HubMedium'
    1: '4msCompany:MultiLFO'
    2: '4msCompany:MultiLFO'
    3: '4msCompany:FM'
    4: '4msCompany:LPG'
    5: '4msCompany:Noise'
    6: '4msCompany:SH'
    7: 'AudibleInstruments:Clouds'
    8: '4msCompany:Freeverb'
    9: '4msCompany:Freeverb'
    10: '4msCompany:Atvert2'
    11: '4msCompany:FM'
    12: '4msCompany:LPG'
    13: '4msCompany:DLD'
    14: '4msCompany:StMix'
  int_cables:
    - out:
        module_id: 6
        jack_id: 0
      ins:
        - module_id: 7
          jack_id: 2
        - module_id: 7
          jack_id: 3
        - module_id: 7
          jack_id: 5
        - module_id: 13
          jack_id: 9
        - module_id: 13
          jack_id: 10
        - module_id: 13
          jack_id: 11
        - module_id: 8
          jack_id: 1
        - module_id: 9
          jack_id: 1
        - module_id: 10
          jack_id: 0
      color: 61865
    - out:
        module_id: 6
        jack_id: 1
      ins:
        - module_id: 7
          jack_id: 8
        - module_id: 7
          jack_id: 9
        - module_id: 13
          jack_id: 12
        - module_id: 13
          jack_id: 13
        - module_id: 13
          jack_id: 14
        - module_id: 8
          jack_id: 2
        - module_id: 8
          jack_id: 3
        - module_id: 9
          jack_id: 2
        - module_id: 9
          jack_id: 3
        - module_id: 10
          jack_id: 1
      color: 1453
    - out:
        module_id: 7
        jack_id: 0
      ins:
        - module_id: 13
          jack_id: 1
      color: 61865
    - out:
        module_id: 7
        jack_id: 1
      ins:
        - module_id: 13
          jack_id: 6
      color: 64934
    - out:
        module_id: 8
        jack_id: 0
      ins:
        - module_id: 14
          jack_id: 2
      color: 13501
    - out:
        module_id: 9
        jack_id: 0
      ins:
        - module_id: 14
          jack_id: 5
      color: 35419
    - out:
        module_id: 3
        jack_id: 0
      ins:
        - module_id: 4
          jack_id: 0
      color: 64934
    - out:
        module_id: 10
        jack_id: 0
      ins:
        - module_id: 3
          jack_id: 0
        - module_id: 3
          jack_id: 1
        - module_id: 3
          jack_id: 2
        - module_id: 3
          jack_id: 3
        - module_id: 3
          jack_id: 4
      color: 13501
    - out:
        module_id: 5
        jack_id: 0
      ins:
        - module_id: 6
          jack_id: 1
        - module_id: 6
          jack_id: 3
      color: 61865
    - out:
        module_id: 13
        jack_id: 3
      ins:
        - module_id: 8
          jack_id: 0
      color: 13501
    - out:
        module_id: 13
        jack_id: 6
      ins:
        - module_id: 9
          jack_id: 0
      color: 35419
    - out:
        module_id: 11
        jack_id: 0
      ins:
        - module_id: 12
          jack_id: 0
      color: 64934
    - out:
        module_id: 10
        jack_id: 1
      ins:
        - module_id: 11
          jack_id: 0
        - module_id: 11
          jack_id: 1
        - module_id: 11
          jack_id: 2
        - module_id: 11
          jack_id: 3
        - module_id: 11
          jack_id: 4
      color: 13501
    - out:
        module_id: 4
        jack_id: 0
      ins:
        - module_id: 14
          jack_id: 6
        - module_id: 14
          jack_id: 0
        - module_id: 7
          jack_id: 6
      color: 61865
    - out:
        module_id: 12
        jack_id: 0
      ins:
        - module_id: 14
          jack_id: 7
        - module_id: 14
          jack_id: 1
        - module_id: 7
          jack_id: 7
      color: 35419
    - out:
        module_id: 1
        jack_id: 1
      ins:
        - module_id: 13
          jack_id: 4
        - module_id: 4
          jack_id: 1
        - module_id: 6
          jack_id: 0
      color: 61865
    - out:
        module_id: 2
        jack_id: 1
      ins:
        - module_id: 7
          jack_id: 0
        - module_id: 13
          jack_id: 3
        - module_id: 13
          jack_id: 7
        - module_id: 13
          jack_id: 8
        - module_id: 6
          jack_id: 2
        - module_id: 12
          jack_id: 1
      color: 61865
  mapped_ins: []
  mapped_outs:
    - panel_jack_id: 0
      out:
        module_id: 14
        jack_id: 0
    - panel_jack_id: 1
      out:
        module_id: 14
        jack_id: 1
  static_knobs:
    - module_id: 4
      param_id: 0
      value: 0.875
    - module_id: 4
      param_id: 1
      value: 0.124096
    - module_id: 4
      param_id: 2
      value: 0.359036
    - module_id: 3
      param_id: 0
      value: 0.595181
    - module_id: 3
      param_id: 1
      value: 0.5
    - module_id: 3
      param_id: 2
      value: 1
    - module_id: 3
      param_id: 3
      value: 0.5
    - module_id: 3
      param_id: 4
      value: 0.524096
    - module_id: 3
      param_id: 5
      value: 0
    - module_id: 3
      param_id: 6
      value: 0
    - module_id: 3
      param_id: 7
      value: 0.5
    - module_id: 12
      param_id: 0
      value: 0.876205
    - module_id: 12
      param_id: 1
      value: 0.124096
    - module_id: 12
      param_id: 2
      value: 0.161446
    - module_id: 11
      param_id: 0
      value: 0.595181
    - module_id: 11
      param_id: 1
      value: 0.5
    - module_id: 11
      param_id: 2
      value: 1
    - module_id: 11
      param_id: 3
      value: 0.5
    - module_id: 11
      param_id: 4
      value: 0.524096
    - module_id: 11
      param_id: 5
      value: 0
    - module_id: 11
      param_id: 6
      value: 0
    - module_id: 11
      param_id: 7
      value: 0.5
    - module_id: 10
      param_id: 0
      value: 0.659036
    - module_id: 10
      param_id: 1
      value: 0.750602
    - module_id: 8
      param_id: 0
      value: 0.5
    - module_id: 8
      param_id: 1
      value: 0.5
    - module_id: 8
      param_id: 2
      value: 0.25
    - module_id: 8
      param_id: 3
      value: 0.494277
    - module_id: 9
      param_id: 0
      value: 0.5
    - module_id: 9
      param_id: 1
      value: 0.5
    - module_id: 9
      param_id: 2
      value: 0.25
    - module_id: 9
      param_id: 3
      value: 0.489157
    - module_id: 7
      param_id: 0
      value: 0
    - module_id: 7
      param_id: 1
      value: 0
    - module_id: 7
      param_id: 2
      value: 0
    - module_id: 7
      param_id: 3
      value: 0.5
    - module_id: 7
      param_id: 4
      value: 0.5
    - module_id: 7
      param_id: 5
      value: 0.5
    - module_id: 7
      param_id: 6
      value: 0.5
    - module_id: 7
      param_id: 7
      value: 0.5
    - module_id: 7
      param_id: 8
      value: 0.5
    - module_id: 7
      param_id: 9
      value: 0.5
    - module_id: 7
      param_id: 10
      value: 0.340964
    - module_id: 7
      param_id: 11
      value: 0
    - module_id: 7
      param_id: 12
      value: 0
    - module_id: 13
      param_id: 0
      value: 0.5
    - module_id: 13
      param_id: 1
      value: 0.5
    - module_id: 13
      param_id: 2
      value: 0
    - module_id: 13
      param_id: 3
      value: 0.5
    - module_id: 13
      param_id: 4
      value: 0.5
    - module_id: 13
      param_id: 5
      value: 0.375
    - module_id: 13
      param_id: 6
      value: 0
    - module_id: 13
      param_id: 7
      value: 0
    - module_id: 13
      param_id: 8
      value: 0
    - module_id: 13
      param_id: 9
      value: 0
    - module_id: 13
      param_id: 10
      value: 0.375
    - module_id: 13
      param_id: 11
      value: 1
    - module_id: 13
      param_id: 12
      value: 0.5
    - module_id: 13
      param_id: 13
      value: 0.5
    - module_id: 13
      param_id: 14
      value: 1
    - module_id: 13
      param_id: 15
      value: 0
    - module_id: 13
      param_id: 16
      value: 0
    - module_id: 13
      param_id: 17
      value: 0
    - module_id: 13
      param_id: 18
      value: 0
    - module_id: 13
      param_id: 19
      value: 0
    - module_id: 13
      param_id: 20
      value: 0
    - module_id: 13
      param_id: 21
      value: 0
    - module_id: 13
      param_id: 22
      value: 0
    - module_id: 13
      param_id: 23
      value: 0
    - module_id: 13
      param_id: 24
      value: 0
    - module_id: 13
      param_id: 25
      value: 0
    - module_id: 13
      param_id: 26
      value: 0
    - module_id: 13
      param_id: 27
      value: 0
    - module_id: 13
      param_id: 28
      value: 0
    - module_id: 13
      param_id: 29
      value: 0
    - module_id: 13
      param_id: 30
      value: 0.5
    - module_id: 13
      param_id: 31
      value: 0.5
    - module_id: 14
      param_id: 0
      value: 0.490662
    - module_id: 14
      param_id: 1
      value: 0.345783
    - module_id: 14
      param_id: 2
      value: 0.345783
    - module_id: 14
      param_id: 3
      value: 0.503093
    - module_id: 14
      param_id: 4
      value: 0.5
    - module_id: 14
      param_id: 5
      value: 0.150602
    - module_id: 14
      param_id: 6
      value: 0.849398
    - module_id: 14
      param_id: 7
      value: 0.5
    - module_id: 1
      param_id: 0
      value: 0
    - module_id: 1
      param_id: 1
      value: 0
    - module_id: 1
      param_id: 2
      value: 0.5
    - module_id: 1
      param_id: 3
      value: 0
    - module_id: 2
      param_id: 0
      value: 0
    - module_id: 2
      param_id: 1
      value: 0
    - module_id: 2
      param_id: 2
      value: 0.5
    - module_id: 2
      param_id: 3
      value: 0
  mapped_knobs:
    - name: ''
      set:
        - panel_knob_id: 0
          module_id: 1
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
          alias_name: Speed 1
        - panel_knob_id: 1
          module_id: 2
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
          alias_name: Speed 2
        - panel_knob_id: 2
          module_id: 11
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
          alias_name: Pitch
        - panel_knob_id: 2
          module_id: 3
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
          alias_name: Pitch
        - panel_knob_id: 3
          module_id: 11
          param_id: 2
          curve_type: 0
          min: 0
          max: 1
          alias_name: Index
        - panel_knob_id: 3
          module_id: 3
          param_id: 2
          curve_type: 0
          min: 0
          max: 1
          alias_name: Index
        - panel_knob_id: 4
          module_id: 4
          param_id: 2
          curve_type: 0
          min: 0
          max: 1
          alias_name: LPG Decay 1
        - panel_knob_id: 5
          module_id: 12
          param_id: 2
          curve_type: 0
          min: 0
          max: 1
          alias_name: LPG Decay 2
        - panel_knob_id: 6
          module_id: 4
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
          alias_name: LPG Color
        - panel_knob_id: 6
          module_id: 12
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
          alias_name: LPG Color
        - panel_knob_id: 7
          module_id: 10
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
          alias_name: Random Timbre 1
        - panel_knob_id: 8
          module_id: 10
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
          alias_name: Random Timbre 2
        - panel_knob_id: 10
          module_id: 14
          param_id: 5
          curve_type: 0
          min: 0.5
          max: 0
          alias_name: Stereo Spread Wet
        - panel_knob_id: 10
          module_id: 14
          param_id: 6
          curve_type: 0
          min: 0.5
          max: 1
          alias_name: Stereo Spread Wet
        - panel_knob_id: 11
          module_id: 14
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
          alias_name: FX Dry/Wet
        - panel_knob_id: 11
          module_id: 14
          param_id: 2
          curve_type: 0
          min: 0
          max: 1
          alias_name: FX Dry/Wet
        - panel_knob_id: 11
          module_id: 14
          param_id: 0
          curve_type: 0
          min: 0.75
          max: 0
          alias_name: FX Dry/Wet
        - panel_knob_id: 11
          module_id: 14
          param_id: 3
          curve_type: 0
          min: 0.769
          max: 0
          alias_name: FX Dry/Wet
    - name: ''
      set: []
    - name: ''
      set: []
    - name: ''
      set: []
    - name: ''
      set: []
    - name: ''
      set: []
    - name: ''
      set: []
    - name: ''
      set: []
  midi_maps:
    name: ''
    set: []
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates:
    - module_id: 7
      data: |-
        {"playback":0,"quality":0,"blendMode":0}
    - module_id: 13
      data: |-
        aLIm+9wL
)";

