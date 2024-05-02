static const char EnvVCA_knobsets_patch[] =
	R"(
PatchData:
  patch_name: EnvVCA_knobsets
  description: Patch Description
  module_slugs:
    0: HubMedium
    1: ENVVCA
  int_cables: []
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 1
          jack_id: 4
    - panel_jack_id: 1
      ins:
        - module_id: 1
          jack_id: 3
    - panel_jack_id: 6
      ins:
        - module_id: 1
          jack_id: 1
    - panel_jack_id: 2
      ins:
        - module_id: 1
          jack_id: 0
    - panel_jack_id: 7
      ins:
        - module_id: 1
          jack_id: 2
  mapped_outs:
    - panel_jack_id: 1
      out:
        module_id: 1
        jack_id: 0
    - panel_jack_id: 0
      out:
        module_id: 1
        jack_id: 2
    - panel_jack_id: 2
      out:
        module_id: 1
        jack_id: 1
  static_knobs:
    - module_id: 1
      param_id: 0
      value: 0.642169
    - module_id: 1
      param_id: 1
      value: 0.351807
    - module_id: 1
      param_id: 2
      value: 0.5
    - module_id: 1
      param_id: 3
      value: 0.589157
    - module_id: 1
      param_id: 4
      value: 0.5
    - module_id: 1
      param_id: 5
      value: 1
    - module_id: 1
      param_id: 6
      value: 1
    - module_id: 1
      param_id: 7
      value: 1
  mapped_knobs:
    - name: Rise
      set:
        - panel_knob_id: 0
          module_id: 1
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 1
          module_id: 1
          param_id: 5
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 2
          module_id: 1
          param_id: 2
          curve_type: 0
          min: 0
          max: 1
    - name: Fall
      set:
        - panel_knob_id: 0
          module_id: 1
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 1
          module_id: 1
          param_id: 6
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 3
          module_id: 1
          param_id: 2
          curve_type: 0
          min: 0
          max: 1
    - name: All
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
        - panel_knob_id: 6
          module_id: 1
          param_id: 5
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 7
          module_id: 1
          param_id: 6
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 9
          module_id: 1
          param_id: 7
          curve_type: 0
          min: 0
          max: 1
    - name: ''
      set: []

)";
