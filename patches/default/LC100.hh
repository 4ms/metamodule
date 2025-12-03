static const char LC100_patch[] =
	R"(
PatchData:
  patch_name: Listen Closely
  description: MetaModule patch for Listen Closely Hardware Module
  module_slugs:
    0: '4msCompany:HubMedium'
    1: 'listenclosely:ListenClosely'
  int_cables: []
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 1
          jack_id: 0
      alias_name: In Left
    - panel_jack_id: 1
      ins:
        - module_id: 1
          jack_id: 1
      alias_name: In Right
    - panel_jack_id: 2
      ins:
        - module_id: 1
          jack_id: 2
      alias_name: Width CV In
  mapped_outs:
    - panel_jack_id: 0
      out:
        module_id: 1
        jack_id: 0
      alias_name: Audio Out Left
    - panel_jack_id: 1
      out:
        module_id: 1
        jack_id: 1
      alias_name: Audio Out Left
  static_knobs:
    - module_id: 1
      param_id: 0
      value: 0.5
    - module_id: 1
      param_id: 1
      value: 0.5
    - module_id: 1
      param_id: 2
      value: 1
    - module_id: 1
      param_id: 3
      value: 0.25
    - module_id: 1
      param_id: 4
      value: 0.5
    - module_id: 1
      param_id: 5
      value: 0.5
    - module_id: 1
      param_id: 6
      value: 0.5
    - module_id: 1
      param_id: 7
      value: 0
    - module_id: 1
      param_id: 8
      value: 0
    - module_id: 1
      param_id: 9
      value: 0
    - module_id: 1
      param_id: 10
      value: 0.5
    - module_id: 1
      param_id: 11
      value: 0.25
    - module_id: 1
      param_id: 12
      value: 0.5
  mapped_knobs:
    - name: ''
      set:
        - panel_knob_id: 0
          module_id: 1
          param_id: 10
          curve_type: 0
          min: 0
          max: 1
          alias_name: Stereo Width
        - panel_knob_id: 1
          module_id: 1
          param_id: 4
          curve_type: 0
          min: 0
          max: 1
          alias_name: Low Shelf
        - panel_knob_id: 2
          module_id: 1
          param_id: 6
          curve_type: 0
          min: 0
          max: 1
          alias_name: Mid
        - panel_knob_id: 3
          module_id: 1
          param_id: 5
          curve_type: 0
          min: 0
          max: 1
          alias_name: High Shelf
        - panel_knob_id: 4
          module_id: 1
          param_id: 12
          curve_type: 0
          min: 0
          max: 1
          alias_name: EQ Routing
        - panel_knob_id: 5
          module_id: 1
          param_id: 11
          curve_type: 0
          min: 0
          max: 1
          alias_name: EQ Level
        - panel_knob_id: 6
          module_id: 1
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
          alias_name: Amount
        - panel_knob_id: 7
          module_id: 1
          param_id: 3
          curve_type: 0
          min: 0
          max: 1
          alias_name: Makeup Gain
        - panel_knob_id: 8
          module_id: 1
          param_id: 2
          curve_type: 0
          min: 0
          max: 1
          alias_name: Dry/Wet
        - panel_knob_id: 9
          module_id: 1
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
          alias_name: Compressor Routing
        - panel_knob_id: 10
          module_id: 1
          param_id: 7
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 11
          module_id: 1
          param_id: 9
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 12
          module_id: 1
          param_id: 8
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
    - name: ''
      set: []
  midi_maps:
    name: ''
    set: []
  midi_poly_num: 1
  midi_poly_mode: 0
  midi_pitchwheel_range: -1
  mapped_lights: []
  vcvModuleStates: []
)";
