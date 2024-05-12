static const char DualEnvEnOsc_patch[] =
	R"(
PatchData:
  patch_name: Dual Env EnOsc
  description: Patch Description
  module_slugs:
    0: HubMedium
    1: EnOsc
    2: EnOsc
    3: SHEV
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 3
          jack_id: 8
      color: 64934
    - out:
        module_id: 2
        jack_id: 0
      ins:
        - module_id: 3
          jack_id: 9
      color: 1453
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 1
          jack_id: 0
    - panel_jack_id: 1
      ins:
        - module_id: 2
          jack_id: 0
    - panel_jack_id: 6
      ins:
        - module_id: 3
          jack_id: 0
    - panel_jack_id: 7
      ins:
        - module_id: 3
          jack_id: 1
  mapped_outs:
    - panel_jack_id: 1
      out:
        module_id: 3
        jack_id: 4
    - panel_jack_id: 0
      out:
        module_id: 1
        jack_id: 0
    - panel_jack_id: 2
      out:
        module_id: 2
        jack_id: 0
    - panel_jack_id: 3
      out:
        module_id: 3
        jack_id: 8
  static_knobs:
    - module_id: 1
      param_id: 0
      value: 0.351807
    - module_id: 1
      param_id: 1
      value: 0.304819
    - module_id: 1
      param_id: 2
      value: 0.5
    - module_id: 1
      param_id: 3
      value: 0.43494
    - module_id: 1
      param_id: 4
      value: 0.5
    - module_id: 1
      param_id: 5
      value: 0
    - module_id: 1
      param_id: 6
      value: 0
    - module_id: 1
      param_id: 7
      value: 0
    - module_id: 1
      param_id: 8
      value: 0
    - module_id: 1
      param_id: 9
      value: 1
    - module_id: 1
      param_id: 10
      value: 0.5
    - module_id: 1
      param_id: 11
      value: 0.5
    - module_id: 1
      param_id: 12
      value: 0.5
    - module_id: 1
      param_id: 13
      value: 0
    - module_id: 1
      param_id: 14
      value: 0
    - module_id: 1
      param_id: 15
      value: 0.5
    - module_id: 1
      param_id: 16
      value: 1
    - module_id: 1
      param_id: 17
      value: 0.5
    - module_id: 1
      param_id: 18
      value: 0
    - module_id: 1
      param_id: 19
      value: 0
    - module_id: 2
      param_id: 0
      value: 0.33735
    - module_id: 2
      param_id: 1
      value: 0.304819
    - module_id: 2
      param_id: 2
      value: 0.5
    - module_id: 2
      param_id: 3
      value: 0.43494
    - module_id: 2
      param_id: 4
      value: 0.5
    - module_id: 2
      param_id: 5
      value: 0
    - module_id: 2
      param_id: 6
      value: 0
    - module_id: 2
      param_id: 7
      value: 0
    - module_id: 2
      param_id: 8
      value: 0
    - module_id: 2
      param_id: 9
      value: 1
    - module_id: 2
      param_id: 10
      value: 0.5
    - module_id: 2
      param_id: 11
      value: 0.5
    - module_id: 2
      param_id: 12
      value: 0.5
    - module_id: 2
      param_id: 13
      value: 0
    - module_id: 2
      param_id: 14
      value: 0
    - module_id: 2
      param_id: 15
      value: 0.5
    - module_id: 2
      param_id: 16
      value: 1
    - module_id: 2
      param_id: 17
      value: 0.5
    - module_id: 2
      param_id: 18
      value: 0
    - module_id: 2
      param_id: 19
      value: 0
    - module_id: 3
      param_id: 0
      value: 0
    - module_id: 3
      param_id: 1
      value: 0.240964
    - module_id: 3
      param_id: 2
      value: 0
    - module_id: 3
      param_id: 3
      value: 0.301205
    - module_id: 3
      param_id: 4
      value: 0.5
    - module_id: 3
      param_id: 5
      value: 0.5
    - module_id: 3
      param_id: 6
      value: 0.5
    - module_id: 3
      param_id: 7
      value: 0.5
    - module_id: 3
      param_id: 8
      value: 0.5
    - module_id: 3
      param_id: 9
      value: 0.5
    - module_id: 3
      param_id: 10
      value: 0.5
    - module_id: 3
      param_id: 11
      value: 0.5
    - module_id: 3
      param_id: 12
      value: 0.5
    - module_id: 3
      param_id: 13
      value: 0.5
    - module_id: 3
      param_id: 14
      value: 0.5
    - module_id: 3
      param_id: 15
      value: 0.5
    - module_id: 3
      param_id: 16
      value: 0.5
    - module_id: 3
      param_id: 17
      value: 0.5
    - module_id: 3
      param_id: 18
      value: 0.5
    - module_id: 3
      param_id: 19
      value: 0.5
    - module_id: 3
      param_id: 20
      value: 0
    - module_id: 3
      param_id: 21
      value: 0
    - module_id: 3
      param_id: 22
      value: 0
    - module_id: 3
      param_id: 23
      value: 0
  mapped_knobs:
    - name: EnOsc 1
      set:
        - panel_knob_id: 0
          module_id: 1
          param_id: 3
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 1
          module_id: 1
          param_id: 6
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 2
          module_id: 1
          param_id: 7
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 3
          module_id: 1
          param_id: 5
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 4
          module_id: 1
          param_id: 8
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 5
          module_id: 1
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 6
          module_id: 1
          param_id: 4
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 7
          module_id: 1
          param_id: 11
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 9
          module_id: 1
          param_id: 10
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 10
          module_id: 1
          param_id: 12
          curve_type: 0
          min: 0
          max: 1
    - name: EnOsc 2
      set:
        - panel_knob_id: 0
          module_id: 2
          param_id: 3
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 1
          module_id: 2
          param_id: 6
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 2
          module_id: 2
          param_id: 7
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 3
          module_id: 2
          param_id: 8
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 4
          module_id: 2
          param_id: 5
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 5
          module_id: 2
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 6
          module_id: 2
          param_id: 4
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 7
          module_id: 2
          param_id: 11
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 9
          module_id: 2
          param_id: 12
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 10
          module_id: 2
          param_id: 10
          curve_type: 0
          min: 0
          max: 1
    - name: ''
      set:
        - panel_knob_id: 0
          module_id: 3
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 1
          module_id: 3
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 2
          module_id: 3
          param_id: 2
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 3
          module_id: 3
          param_id: 3
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
  midi_maps:
    name: ''
    set: []
  midi_poly_num: 0
  vcvModuleStates: []
)";
