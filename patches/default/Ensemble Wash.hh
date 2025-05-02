// Automatically generated, do not edit
static const char patch_Ensemble_Wash[] =
	R"(
PatchData:
  patch_name: Ensemble Wash
  description: Patch Description
  module_slugs:
    0: '4msCompany:HubMedium'
    1: '4msCompany:EnOsc'
    2: '4msCompany:EnOsc'
    3: '4msCompany:EnOsc'
    4: '4msCompany:EnOsc'
    5: '4msCompany:StMix'
    6: '4msCompany:StMix'
    7: '4msCompany:StMix'
    8: 'Valley:Plateau'
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 6
          jack_id: 0
      color: 1453
    - out:
        module_id: 2
        jack_id: 0
      ins:
        - module_id: 6
          jack_id: 2
      color: 13501
    - out:
        module_id: 3
        jack_id: 0
      ins:
        - module_id: 6
          jack_id: 4
      color: 61865
    - out:
        module_id: 4
        jack_id: 0
      ins:
        - module_id: 6
          jack_id: 6
      color: 64934
    - out:
        module_id: 1
        jack_id: 1
      ins:
        - module_id: 7
          jack_id: 0
      color: 35419
    - out:
        module_id: 2
        jack_id: 1
      ins:
        - module_id: 7
          jack_id: 2
      color: 61865
    - out:
        module_id: 3
        jack_id: 1
      ins:
        - module_id: 7
          jack_id: 4
      color: 64934
    - out:
        module_id: 4
        jack_id: 1
      ins:
        - module_id: 7
          jack_id: 6
      color: 1453
    - out:
        module_id: 6
        jack_id: 0
      ins:
        - module_id: 5
          jack_id: 0
      color: 1453
    - out:
        module_id: 6
        jack_id: 1
      ins:
        - module_id: 5
          jack_id: 1
      color: 13501
    - out:
        module_id: 7
        jack_id: 0
      ins:
        - module_id: 5
          jack_id: 2
      color: 13501
    - out:
        module_id: 7
        jack_id: 1
      ins:
        - module_id: 5
          jack_id: 3
      color: 35419
    - out:
        module_id: 5
        jack_id: 0
      ins:
        - module_id: 8
          jack_id: 0
      color: 61865
    - out:
        module_id: 5
        jack_id: 1
      ins:
        - module_id: 8
          jack_id: 1
      color: 64934
  mapped_ins: []
  mapped_outs:
    - panel_jack_id: 0
      out:
        module_id: 8
        jack_id: 0
    - panel_jack_id: 1
      out:
        module_id: 8
        jack_id: 1
  static_knobs:
    - module_id: 5
      param_id: 0
      value: 0.56747
    - module_id: 5
      param_id: 1
      value: 0.56747
    - module_id: 5
      param_id: 2
      value: 0.5
    - module_id: 5
      param_id: 3
      value: 0.5
    - module_id: 5
      param_id: 4
      value: 0.5
    - module_id: 5
      param_id: 5
      value: 0.5
    - module_id: 5
      param_id: 6
      value: 0.5
    - module_id: 5
      param_id: 7
      value: 0.5
    - module_id: 1
      param_id: 0
      value: 0.369879
    - module_id: 1
      param_id: 1
      value: 0.181672
    - module_id: 1
      param_id: 2
      value: 0.0990964
    - module_id: 1
      param_id: 3
      value: 0.5
    - module_id: 1
      param_id: 4
      value: 0.625677
    - module_id: 1
      param_id: 5
      value: 0
    - module_id: 1
      param_id: 6
      value: 0
    - module_id: 1
      param_id: 7
      value: 0.155754
    - module_id: 1
      param_id: 8
      value: 0
    - module_id: 1
      param_id: 9
      value: 1
    - module_id: 1
      param_id: 10
      value: 1
    - module_id: 1
      param_id: 11
      value: 0
    - module_id: 1
      param_id: 12
      value: 1
    - module_id: 1
      param_id: 13
      value: 0
    - module_id: 1
      param_id: 14
      value: 0
    - module_id: 1
      param_id: 15
      value: 0
    - module_id: 1
      param_id: 16
      value: 0
    - module_id: 1
      param_id: 17
      value: 0.5
    - module_id: 1
      param_id: 18
      value: 1
    - module_id: 1
      param_id: 19
      value: 0.5
    - module_id: 3
      param_id: 0
      value: 0.369879
    - module_id: 3
      param_id: 1
      value: 0.178441
    - module_id: 3
      param_id: 2
      value: 0.0990964
    - module_id: 3
      param_id: 3
      value: 0.5
    - module_id: 3
      param_id: 4
      value: 0.629899
    - module_id: 3
      param_id: 5
      value: 0
    - module_id: 3
      param_id: 6
      value: 0
    - module_id: 3
      param_id: 7
      value: 0.353862
    - module_id: 3
      param_id: 8
      value: 0.096
    - module_id: 3
      param_id: 9
      value: 1
    - module_id: 3
      param_id: 10
      value: 1
    - module_id: 3
      param_id: 11
      value: 0
    - module_id: 3
      param_id: 12
      value: 1
    - module_id: 3
      param_id: 13
      value: 0
    - module_id: 3
      param_id: 14
      value: 0
    - module_id: 3
      param_id: 15
      value: 0
    - module_id: 3
      param_id: 16
      value: 0
    - module_id: 3
      param_id: 17
      value: 0.5
    - module_id: 3
      param_id: 18
      value: 1
    - module_id: 3
      param_id: 19
      value: 0.5
    - module_id: 2
      param_id: 0
      value: 0.369879
    - module_id: 2
      param_id: 1
      value: 0.184904
    - module_id: 2
      param_id: 2
      value: 0.0990964
    - module_id: 2
      param_id: 3
      value: 0.5
    - module_id: 2
      param_id: 4
      value: 0.625677
    - module_id: 2
      param_id: 5
      value: 0
    - module_id: 2
      param_id: 6
      value: 0
    - module_id: 2
      param_id: 7
      value: 0.243195
    - module_id: 2
      param_id: 8
      value: 0.095
    - module_id: 2
      param_id: 9
      value: 1
    - module_id: 2
      param_id: 10
      value: 1
    - module_id: 2
      param_id: 11
      value: 0
    - module_id: 2
      param_id: 12
      value: 1
    - module_id: 2
      param_id: 13
      value: 0
    - module_id: 2
      param_id: 14
      value: 0
    - module_id: 2
      param_id: 15
      value: 0
    - module_id: 2
      param_id: 16
      value: 0
    - module_id: 2
      param_id: 17
      value: 0.5
    - module_id: 2
      param_id: 18
      value: 1
    - module_id: 2
      param_id: 19
      value: 0.5
    - module_id: 4
      param_id: 0
      value: 0.369879
    - module_id: 4
      param_id: 1
      value: 0.180236
    - module_id: 4
      param_id: 2
      value: 0.0990963
    - module_id: 4
      param_id: 3
      value: 0.5
    - module_id: 4
      param_id: 4
      value: 0.63201
    - module_id: 4
      param_id: 5
      value: 0
    - module_id: 4
      param_id: 6
      value: 0
    - module_id: 4
      param_id: 7
      value: 0.424225
    - module_id: 4
      param_id: 8
      value: 0
    - module_id: 4
      param_id: 9
      value: 1
    - module_id: 4
      param_id: 10
      value: 1
    - module_id: 4
      param_id: 11
      value: 0.5
    - module_id: 4
      param_id: 12
      value: 0.5
    - module_id: 4
      param_id: 13
      value: 0
    - module_id: 4
      param_id: 14
      value: 0
    - module_id: 4
      param_id: 15
      value: 0
    - module_id: 4
      param_id: 16
      value: 0
    - module_id: 4
      param_id: 17
      value: 0.5
    - module_id: 4
      param_id: 18
      value: 1
    - module_id: 4
      param_id: 19
      value: 0.5
    - module_id: 6
      param_id: 0
      value: 0.5
    - module_id: 6
      param_id: 1
      value: 0.5
    - module_id: 6
      param_id: 2
      value: 0.5
    - module_id: 6
      param_id: 3
      value: 0.5
    - module_id: 6
      param_id: 4
      value: 0.278822
    - module_id: 6
      param_id: 5
      value: 0.282154
    - module_id: 6
      param_id: 6
      value: 0.277155
    - module_id: 6
      param_id: 7
      value: 0.283265
    - module_id: 7
      param_id: 0
      value: 0.5
    - module_id: 7
      param_id: 1
      value: 0.5
    - module_id: 7
      param_id: 2
      value: 0.5
    - module_id: 7
      param_id: 3
      value: 0.5
    - module_id: 7
      param_id: 4
      value: 0.7234
    - module_id: 7
      param_id: 5
      value: 0.723955
    - module_id: 7
      param_id: 6
      value: 0.725066
    - module_id: 7
      param_id: 7
      value: 0.725622
    - module_id: 8
      param_id: 0
      value: 0.283168
    - module_id: 8
      param_id: 1
      value: 0.218428
    - module_id: 8
      param_id: 2
      value: 0
    - module_id: 8
      param_id: 3
      value: 1
    - module_id: 8
      param_id: 4
      value: 1
    - module_id: 8
      param_id: 5
      value: 0.686747
    - module_id: 8
      param_id: 6
      value: 1
    - module_id: 8
      param_id: 7
      value: 0.655421
    - module_id: 8
      param_id: 8
      value: 0.461446
    - module_id: 8
      param_id: 9
      value: 1
    - module_id: 8
      param_id: 10
      value: 0.0337662
    - module_id: 8
      param_id: 11
      value: 0.5
    - module_id: 8
      param_id: 12
      value: 0.225974
    - module_id: 8
      param_id: 13
      value: 0
    - module_id: 8
      param_id: 14
      value: 0
    - module_id: 8
      param_id: 15
      value: 0
    - module_id: 8
      param_id: 16
      value: 0
    - module_id: 8
      param_id: 17
      value: 0.5
    - module_id: 8
      param_id: 18
      value: 0.5
    - module_id: 8
      param_id: 19
      value: 0.5
    - module_id: 8
      param_id: 20
      value: 0.5
    - module_id: 8
      param_id: 21
      value: 0.5
    - module_id: 8
      param_id: 22
      value: 0.5
    - module_id: 8
      param_id: 23
      value: 0.5
    - module_id: 8
      param_id: 24
      value: 0.5
    - module_id: 8
      param_id: 25
      value: 0.5
    - module_id: 8
      param_id: 26
      value: 0.5
    - module_id: 8
      param_id: 27
      value: 0.5
    - module_id: 8
      param_id: 28
      value: 0.5
    - module_id: 8
      param_id: 29
      value: 0
    - module_id: 8
      param_id: 30
      value: 1
  mapped_knobs:
    - name: Main
      set:
        - panel_knob_id: 0
          module_id: 1
          param_id: 4
          curve_type: 0
          min: 0.468
          max: 1
          alias_name: Scale Degree
        - panel_knob_id: 0
          module_id: 3
          param_id: 4
          curve_type: 0
          min: 0.474
          max: 1
          alias_name: Scale Degree
        - panel_knob_id: 0
          module_id: 2
          param_id: 4
          curve_type: 0
          min: 0.468
          max: 1
          alias_name: Scale Degree
        - panel_knob_id: 0
          module_id: 4
          param_id: 4
          curve_type: 0
          min: 0.477
          max: 1
          alias_name: Scale Degree
        - panel_knob_id: 1
          module_id: 1
          param_id: 7
          curve_type: 0
          min: 0
          max: 0.228
          alias_name: Detune
        - panel_knob_id: 1
          module_id: 3
          param_id: 7
          curve_type: 0
          min: 0
          max: 0.518
          alias_name: Detune
        - panel_knob_id: 1
          module_id: 2
          param_id: 7
          curve_type: 0
          min: 0
          max: 0.356
          alias_name: Detune
        - panel_knob_id: 1
          module_id: 4
          param_id: 7
          curve_type: 0
          min: 0
          max: 0.621
          alias_name: Detune
        - panel_knob_id: 2
          module_id: 1
          param_id: 1
          curve_type: 0
          min: 0
          max: 0.506
          alias_name: Note Spread
        - panel_knob_id: 2
          module_id: 3
          param_id: 1
          curve_type: 0
          min: 0
          max: 0.497
          alias_name: Note Spread
        - panel_knob_id: 2
          module_id: 2
          param_id: 1
          curve_type: 0
          min: 0
          max: 0.515
          alias_name: Note Spread
        - panel_knob_id: 2
          module_id: 4
          param_id: 1
          curve_type: 0
          min: 0
          max: 0.502
          alias_name: Note Spread
        - panel_knob_id: 3
          module_id: 6
          param_id: 4
          curve_type: 0
          min: 0.502
          max: 0
          alias_name: Stereo Spread
        - panel_knob_id: 3
          module_id: 6
          param_id: 5
          curve_type: 0
          min: 0.508
          max: 0
          alias_name: Stereo Spread
        - panel_knob_id: 3
          module_id: 6
          param_id: 6
          curve_type: 0
          min: 0.499
          max: 0
          alias_name: Stereo Spread
        - panel_knob_id: 3
          module_id: 6
          param_id: 7
          curve_type: 0
          min: 0.51
          max: 0
          alias_name: Stereo Spread
        - panel_knob_id: 3
          module_id: 7
          param_id: 4
          curve_type: 0
          min: 0.502
          max: 1
          alias_name: Stereo Spread
        - panel_knob_id: 3
          module_id: 7
          param_id: 5
          curve_type: 0
          min: 0.503
          max: 1
          alias_name: Stereo Spread
        - panel_knob_id: 3
          module_id: 7
          param_id: 6
          curve_type: 0
          min: 0.505
          max: 1
          alias_name: Stereo Spread
        - panel_knob_id: 3
          module_id: 7
          param_id: 7
          curve_type: 0
          min: 0.506
          max: 1
          alias_name: Stereo Spread
        - panel_knob_id: 4
          module_id: 4
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
          alias_name: Scale
        - panel_knob_id: 4
          module_id: 3
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
          alias_name: Scale
        - panel_knob_id: 4
          module_id: 2
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
          alias_name: Scale
        - panel_knob_id: 4
          module_id: 1
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
          alias_name: Scale
        - panel_knob_id: 5
          module_id: 5
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
          alias_name: Master Volume
        - panel_knob_id: 5
          module_id: 5
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
          alias_name: Master Volume
        - panel_knob_id: 6
          module_id: 8
          param_id: 5
          curve_type: 0
          min: 0
          max: 1
          alias_name: Reverb Size
        - panel_knob_id: 7
          module_id: 8
          param_id: 7
          curve_type: 0
          min: 0
          max: 1
          alias_name: Reverb Decay
        - panel_knob_id: 8
          module_id: 8
          param_id: 8
          curve_type: 0
          min: 1
          max: 0
          alias_name: Reverb Damping
        - panel_knob_id: 9
          module_id: 8
          param_id: 0
          curve_type: 0
          min: 0.499001
          max: 0
          alias_name: Reverb Dry/Wet
        - panel_knob_id: 9
          module_id: 8
          param_id: 1
          curve_type: 0
          min: 0
          max: 0.505
          alias_name: Reverb Dry/Wet
        - panel_knob_id: 10
          module_id: 1
          param_id: 2
          curve_type: 0
          min: 0
          max: 0.35
          alias_name: Transpose
        - panel_knob_id: 10
          module_id: 2
          param_id: 2
          curve_type: 0
          min: 0
          max: 0.35
          alias_name: Transpose
        - panel_knob_id: 10
          module_id: 3
          param_id: 2
          curve_type: 0
          min: 0
          max: 0.35
          alias_name: Transpose
        - panel_knob_id: 10
          module_id: 4
          param_id: 2
          curve_type: 0
          min: 0
          max: 0.35
          alias_name: Transpose
        - panel_knob_id: 11
          module_id: 4
          param_id: 8
          curve_type: 0
          min: 0
          max: 1
          alias_name: Warp
        - panel_knob_id: 11
          module_id: 3
          param_id: 8
          curve_type: 0
          min: 0.096
          max: 1
          alias_name: Warp
        - panel_knob_id: 11
          module_id: 2
          param_id: 8
          curve_type: 0
          min: 0.095
          max: 1
          alias_name: Warp
        - panel_knob_id: 11
          module_id: 1
          param_id: 8
          curve_type: 0
          min: 0
          max: 1
          alias_name: Warp
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
    - module_id: 8
      data: |-
        {"frozen":false,"freezeToggle":false,"panelStyle":0,"tuned":0,"diffuseInput":1,"preDelayCVSens":0,"inputSensitivity":1,"outputSaturation":0}
)";

