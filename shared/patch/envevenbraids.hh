static char env_even_braids[] =
	R"(
PatchData:
  patch_name: env even braids
  description: Patch Description
  module_slugs:
    0: HubMedium
    1: ENVVCA
    2: EvenVCO
    3: Braids
    4: Braids
    5: DualAtenuverter
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 2
          jack_id: 4
    - out:
        module_id: 2
        jack_id: 4
      ins:
        - module_id: 1
          jack_id: 4
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 3
          jack_id: 1
    - panel_jack_id: 6
      ins:
        - module_id: 3
          jack_id: 0
    - panel_jack_id: 1
      ins:
        - module_id: 3
          jack_id: 2
    - panel_jack_id: 2
      ins:
        - module_id: 3
          jack_id: 3
    - panel_jack_id: 3
      ins:
        - module_id: 3
          jack_id: 4
  mapped_outs:
    - panel_jack_id: 0
      out:
        module_id: 1
        jack_id: 2
    - panel_jack_id: 7
      out:
        module_id: 3
        jack_id: 0
    - panel_jack_id: 6
      out:
        module_id: 4
        jack_id: 0
    - panel_jack_id: 5
      out:
        module_id: 5
        jack_id: 0
  static_knobs:
    - module_id: 1
      param_id: 0
      value: 0
    - module_id: 1
      param_id: 1
      value: 0.13253
    - module_id: 1
      param_id: 2
      value: 1
    - module_id: 1
      param_id: 3
      value: 0.478313
    - module_id: 1
      param_id: 4
      value: 0.501205
    - module_id: 1
      param_id: 5
      value: 1
    - module_id: 1
      param_id: 6
      value: 1
    - module_id: 1
      param_id: 7
      value: 1
    - module_id: 2
      param_id: 0
      value: -0
    - module_id: 2
      param_id: 1
      value: -0.303614
    - module_id: 2
      param_id: 2
      value: -1
    - module_id: 3
      param_id: 0
      value: 0
    - module_id: 3
      param_id: 1
      value: -5
    - module_id: 3
      param_id: 2
      value: 0
    - module_id: 3
      param_id: 3
      value: 0
    - module_id: 3
      param_id: 4
      value: 0
    - module_id: 3
      param_id: 5
      value: 0
    - module_id: 3
      param_id: 6
      value: 0
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
      value: 0
    - module_id: 5
      param_id: 0
      value: 0
    - module_id: 5
      param_id: 1
      value: -1
    - module_id: 5
      param_id: 2
      value: 0
    - module_id: 5
      param_id: 3
      value: 0.5
  mapped_knobs:
    - name: 'Default'
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
        module_id: 2
        param_id: 1
        curve_type: 0
        min: 0
        max: 1
      - panel_knob_id: 3
        module_id: 2
        param_id: 0
        curve_type: 0
        min: 0
        max: 1
      - panel_knob_id: 4
        module_id: 1
        param_id: 2
        curve_type: 0
        min: 0
        max: 1
      - panel_knob_id: 5
        module_id: 3
        param_id: 3
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
      - panel_knob_id: 8
        module_id: 1
        param_id: 7
        curve_type: 0
        min: 0
        max: 1
      - panel_knob_id: 9
        module_id: 3
        param_id: 6
        curve_type: 0
        min: 0
        max: 1
      - panel_knob_id: 10
        module_id: 3
        param_id: 1
        curve_type: 0
        min: 0
        max: 1
      - panel_knob_id: 11
        module_id: 3
        param_id: 5
        curve_type: 0
        min: 0
        max: 1
)";
