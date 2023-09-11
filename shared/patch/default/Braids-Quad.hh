static char BraidsQuad_patch[] =
	R"(
PatchData:
  patch_name: Braids Quad
  description: Patch Description
  module_slugs:
    0: HubMedium
    1: Braids
    2: Braids
    3: Braids
    4: Braids
  int_cables: []
  mapped_ins: []
  mapped_outs:
    - panel_jack_id: 1
      out:
        module_id: 2
        jack_id: 0
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
  static_knobs:
    - module_id: 1
      param_id: 0
      value: 0
    - module_id: 1
      param_id: 1
      value: -1
    - module_id: 1
      param_id: 2
      value: 0
    - module_id: 1
      param_id: 3
      value: 0.5
    - module_id: 1
      param_id: 4
      value: 0
    - module_id: 1
      param_id: 5
      value: 0.5
    - module_id: 1
      param_id: 6
      value: 0.5
    - module_id: 2
      param_id: 0
      value: 0
    - module_id: 2
      param_id: 1
      value: -1
    - module_id: 2
      param_id: 2
      value: 0
    - module_id: 2
      param_id: 3
      value: 0.5
    - module_id: 2
      param_id: 4
      value: 0
    - module_id: 2
      param_id: 5
      value: 0.5
    - module_id: 2
      param_id: 6
      value: 0.5
    - module_id: 3
      param_id: 0
      value: 0
    - module_id: 3
      param_id: 1
      value: -1
    - module_id: 3
      param_id: 2
      value: 0
    - module_id: 3
      param_id: 3
      value: 0.5
    - module_id: 3
      param_id: 4
      value: 0
    - module_id: 3
      param_id: 5
      value: 0.5
    - module_id: 3
      param_id: 6
      value: 0.5
    - module_id: 4
      param_id: 0
      value: 0
    - module_id: 4
      param_id: 1
      value: -1
    - module_id: 4
      param_id: 2
      value: 0
    - module_id: 4
      param_id: 3
      value: 0.5
    - module_id: 4
      param_id: 4
      value: 0
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
          max : 1

)";
