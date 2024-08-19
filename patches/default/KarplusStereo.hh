static const char KarplusStereo_patch[] =
	R"(
PatchData:
  patch_name: Karplus Stereo
  description: Karplus sounds. Left and right knobs control each osc. Big knobs control Reverb and pitch shift
  module_slugs:
    0: HubMedium
    1: KPLS
    2: KPLS
    3: Freeverb
    4: Freeverb
    5: PitchShift
    6: PitchShift
    7: Mixer
    8: QCD
    9: MultiLFO
  int_cables:
    - out:
        module_id: 2
        jack_id: 0
      ins:
        - module_id: 3
          jack_id: 0
      color: 3125
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 4
          jack_id: 0
      color: 52641
    - out:
        module_id: 4
        jack_id: 0
      ins:
        - module_id: 5
          jack_id: 0
      color: 3170
    - out:
        module_id: 3
        jack_id: 0
      ins:
        - module_id: 6
          jack_id: 0
      color: 51400
    - out:
        module_id: 5
        jack_id: 0
      ins:
        - module_id: 7
          jack_id: 0
      color: 13501
    - out:
        module_id: 6
        jack_id: 0
      ins:
        - module_id: 7
          jack_id: 1
      color: 35419
    - out:
        module_id: 9
        jack_id: 1
      ins:
        - module_id: 8
          jack_id: 2
      color: 61865
    - out:
        module_id: 8
        jack_id: 2
      ins:
        - module_id: 2
          jack_id: 1
      color: 1453
    - out:
        module_id: 8
        jack_id: 4
      ins:
        - module_id: 1
          jack_id: 1
      color: 13501
  mapped_ins: []
  mapped_outs:
    - panel_jack_id: 0
      out:
        module_id: 7
        jack_id: 0
    - panel_jack_id: 1
      out:
        module_id: 5
        jack_id: 0
    - panel_jack_id: 2
      out:
        module_id: 6
        jack_id: 0
  static_knobs:
    - module_id: 1
      param_id: 0
      value: 0
    - module_id: 1
      param_id: 1
      value: 0
    - module_id: 1
      param_id: 2
      value: 0
    - module_id: 2
      param_id: 0
      value: 0.0433735
    - module_id: 2
      param_id: 1
      value: 0
    - module_id: 2
      param_id: 2
      value: 0
    - module_id: 3
      param_id: 0
      value: 0.342169
    - module_id: 3
      param_id: 1
      value: 0.173494
    - module_id: 3
      param_id: 2
      value: 0.303614
    - module_id: 3
      param_id: 3
      value: 0.407229
    - module_id: 4
      param_id: 0
      value: 0
    - module_id: 4
      param_id: 1
      value: 0
    - module_id: 4
      param_id: 2
      value: 0.25
    - module_id: 4
      param_id: 3
      value: 0
    - module_id: 5
      param_id: 0
      value: 0.303614
    - module_id: 5
      param_id: 1
      value: 0.5
    - module_id: 5
      param_id: 2
      value: 0.3675
    - module_id: 5
      param_id: 3
      value: 0.875
    - module_id: 6
      param_id: 0
      value: 0
    - module_id: 6
      param_id: 1
      value: 0.5
    - module_id: 6
      param_id: 2
      value: 0.351
    - module_id: 6
      param_id: 3
      value: 0.875
    - module_id: 7
      param_id: 0
      value: 0.975904
    - module_id: 7
      param_id: 1
      value: 1
    - module_id: 7
      param_id: 2
      value: 0
    - module_id: 7
      param_id: 3
      value: 0
    - module_id: 8
      param_id: 0
      value: 0.5
    - module_id: 8
      param_id: 1
      value: 0.5
    - module_id: 8
      param_id: 2
      value: 0.5
    - module_id: 8
      param_id: 3
      value: 0.407229
    - module_id: 8
      param_id: 4
      value: 0.5
    - module_id: 8
      param_id: 5
      value: 0.5
    - module_id: 8
      param_id: 6
      value: 0.5
    - module_id: 8
      param_id: 7
      value: 0.303614
    - module_id: 8
      param_id: 8
      value: 0.5
    - module_id: 8
      param_id: 9
      value: 0.5
    - module_id: 8
      param_id: 10
      value: 0.5
    - module_id: 8
      param_id: 11
      value: 0.5
    - module_id: 8
      param_id: 12
      value: 0.5
    - module_id: 8
      param_id: 13
      value: 0.5
    - module_id: 8
      param_id: 14
      value: 0.5
    - module_id: 8
      param_id: 15
      value: 0.5
    - module_id: 8
      param_id: 16
      value: 0
    - module_id: 8
      param_id: 17
      value: 0
    - module_id: 8
      param_id: 18
      value: 0
    - module_id: 8
      param_id: 19
      value: 0
    - module_id: 8
      param_id: 20
      value: 0
    - module_id: 9
      param_id: 0
      value: 0.342169
    - module_id: 9
      param_id: 1
      value: 0.5
    - module_id: 9
      param_id: 2
      value: 0.5
  mapped_knobs:
    - name: Sound
      set:
        - panel_knob_id: 0
          module_id: 3
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 1
          module_id: 3
          param_id: 3
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 2
          module_id: 3
          param_id: 2
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 2
          module_id: 5
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 3
          module_id: 4
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 4
          module_id: 4
          param_id: 3
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 5
          module_id: 6
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 6
          module_id: 2
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 7
          module_id: 2
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 8
          module_id: 2
          param_id: 2
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 9
          module_id: 1
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 10
          module_id: 1
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 11
          module_id: 1
          param_id: 2
          curve_type: 0
          min: 0
          max: 1
    - name: Rhythm
      set:
        - panel_knob_id: 0
          module_id: 9
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 1
          module_id: 8
          param_id: 3
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 2
          module_id: 8
          param_id: 7
          curve_type: 0
          min: 0
          max: 1
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
  vcvModuleStates: []

)";
