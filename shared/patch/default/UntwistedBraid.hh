static const char UntwistedBraid_patch[] =
	R"(
PatchData:
  patch_name: Untwisted Braid
  description: 'Four parallel Algorithm Oscs'
  module_slugs:
    0: '4msCompany:HubMedium'
    1: 'AudibleInstruments:Braids'
    2: 'AudibleInstruments:Braids'
    3: 'AudibleInstruments:Braids'
    4: 'AudibleInstruments:Braids'
  int_cables: []
  mapped_ins:
    - panel_jack_id: 1
      ins:
        - module_id: 2
          jack_id: 1
    - panel_jack_id: 2
      ins:
        - module_id: 1
          jack_id: 1
    - panel_jack_id: 3
      ins:
        - module_id: 4
          jack_id: 1
    - panel_jack_id: 0
      ins:
        - module_id: 3
          jack_id: 1
    - panel_jack_id: 6
      ins:
        - module_id: 3
          jack_id: 0
    - panel_jack_id: 7
      ins:
        - module_id: 2
          jack_id: 0
    - panel_jack_id: 4
      ins:
        - module_id: 1
          jack_id: 0
    - panel_jack_id: 5
      ins:
        - module_id: 4
          jack_id: 0
  mapped_outs:
    - panel_jack_id: 3
      out:
        module_id: 4
        jack_id: 0
    - panel_jack_id: 0
      out:
        module_id: 3
        jack_id: 0
    - panel_jack_id: 2
      out:
        module_id: 1
        jack_id: 0
    - panel_jack_id: 1
      out:
        module_id: 2
        jack_id: 0
  static_knobs:
    - module_id: 1
      param_id: 0
      value: 0.5
    - module_id: 1
      param_id: 1
      value: 0.5
    - module_id: 1
      param_id: 2
      value: 0.5
    - module_id: 1
      param_id: 3
      value: 0.5
    - module_id: 1
      param_id: 4
      value: 0.5
    - module_id: 1
      param_id: 5
      value: 0.5
    - module_id: 1
      param_id: 6
      value: 0.5
    - module_id: 2
      param_id: 0
      value: 0.5
    - module_id: 2
      param_id: 1
      value: 0.5
    - module_id: 2
      param_id: 2
      value: 0.5
    - module_id: 2
      param_id: 3
      value: 0.5
    - module_id: 2
      param_id: 4
      value: 0.5
    - module_id: 2
      param_id: 5
      value: 0.5
    - module_id: 2
      param_id: 6
      value: 0.5
    - module_id: 3
      param_id: 0
      value: 0.5
    - module_id: 3
      param_id: 1
      value: 0.5
    - module_id: 3
      param_id: 2
      value: 0.5
    - module_id: 3
      param_id: 3
      value: 0.5
    - module_id: 3
      param_id: 4
      value: 0.5
    - module_id: 3
      param_id: 5
      value: 0.5
    - module_id: 3
      param_id: 6
      value: 0.5
    - module_id: 4
      param_id: 0
      value: 0.5
    - module_id: 4
      param_id: 1
      value: 0.5
    - module_id: 4
      param_id: 2
      value: 0.5
    - module_id: 4
      param_id: 3
      value: 0.5
    - module_id: 4
      param_id: 4
      value: 0.5
    - module_id: 4
      param_id: 5
      value: 0.5
    - module_id: 4
      param_id: 6
      value: 0.5
  mapped_knobs:
    - name: Braids 1
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
        - panel_knob_id: 4
          module_id: 3
          param_id: 4
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 5
          module_id: 3
          param_id: 5
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 9
          module_id: 3
          param_id: 6
          curve_type: 0
          min: 0
          max: 1
    - name: Braids 2
      set:
        - panel_knob_id: 0
          module_id: 2
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 1
          module_id: 2
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 2
          module_id: 2
          param_id: 2
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 3
          module_id: 2
          param_id: 3
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 4
          module_id: 2
          param_id: 4
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 5
          module_id: 2
          param_id: 5
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 9
          module_id: 2
          param_id: 6
          curve_type: 0
          min: 0
          max: 1
    - name: Braids 3
      set:
        - panel_knob_id: 0
          module_id: 1
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 1
          module_id: 1
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 2
          module_id: 1
          param_id: 2
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 3
          module_id: 1
          param_id: 3
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 4
          module_id: 1
          param_id: 4
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 5
          module_id: 1
          param_id: 5
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 9
          module_id: 1
          param_id: 6
          curve_type: 0
          min: 0
          max: 1
    - name: Braids 4
      set:
        - panel_knob_id: 0
          module_id: 4
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 1
          module_id: 4
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 2
          module_id: 4
          param_id: 2
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 3
          module_id: 4
          param_id: 3
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 4
          module_id: 4
          param_id: 4
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 5
          module_id: 4
          param_id: 5
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 9
          module_id: 4
          param_id: 6
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
  midi_maps:
    name: ''
    set: []
  midi_poly_num: 0
  vcvModuleStates:
    - module_id: 1
      data: |-
        {"settings":[23,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],"lowCpu":false}
    - module_id: 2
      data: |-
        {"settings":[23,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],"lowCpu":false}
    - module_id: 3
      data: |-
        {"settings":[23,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],"lowCpu":false}
    - module_id: 4
      data: |-
        {"settings":[23,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],"lowCpu":false}
)";
