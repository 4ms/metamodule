static char braidslfo_patch[] = 
R"(
PatchData:
  patch_name: braidslfo
  description: Patch Description
  module_slugs:
    0: PanelMedium
    1: Braids
    2: MultiLFO
  int_cables:
    - out:
        module_id: 1
        jack_id: 3
      ins:
        - module_id: 2
          jack_id: 3
    - out:
        module_id: 1
        jack_id: 4
      ins:
        - module_id: 2
          jack_id: 2
  mapped_ins: []
  mapped_outs:
    - panel_jack_id: 0
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
      value: -0.395181
    - module_id: 1
      param_id: 1
      value: -2.18554
    - module_id: 1
      param_id: 2
      value: 0.0120482
    - module_id: 1
      param_id: 3
      value: 0.473494
    - module_id: 1
      param_id: 4
      value: 0.180723
    - module_id: 1
      param_id: 5
      value: 0.555422
    - module_id: 1
      param_id: 6
      value: 0.5
    - module_id: 2
      param_id: 0
      value: 0.483133
    - module_id: 2
      param_id: 1
      value: 0.557831
    - module_id: 2
      param_id: 2
      value: 0.454217
  mapped_knobs:
    - panel_knob_id: 6
      module_id: 1
      param_id: 2
      curve_type: 0
      min: 0
      max: 1
    - panel_knob_id: 0
      module_id: 2
      param_id: 0
      curve_type: 0
      min: 0
      max: 1
    - panel_knob_id: 2
      module_id: 1
      param_id: 1
      curve_type: 0
      min: 0
      max: 1
    - panel_knob_id: 1
      module_id: 1
      param_id: 3
      curve_type: 0
      min: 0
      max: 1

)";