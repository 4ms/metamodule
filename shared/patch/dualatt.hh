static char dualatt_patch[] = 
R"(
PatchData:
  patch_name: 'dual-att'
  description: Patch Description
  module_slugs:
    0: PanelMedium
    1: DualAtenuverter
  int_cables: []
  mapped_ins:
    - panel_jack_id: 2
      ins:
        - module_id: 1
          jack_id: 0
    - panel_jack_id: 3
      ins:
        - module_id: 1
          jack_id: 1
  mapped_outs:
    - panel_jack_id: 0
      out:
        module_id: 1
        jack_id: 0
    - panel_jack_id: 1
      out:
        module_id: 1
        jack_id: 1
  static_knobs:
    - module_id: 1
      param_id: 0
      value: 0.0457833
    - module_id: 1
      param_id: 1
      value: -10
    - module_id: 1
      param_id: 2
      value: -1
    - module_id: 1
      param_id: 3
      value: -10
  mapped_knobs:
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

)";