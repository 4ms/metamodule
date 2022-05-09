static char NonlinearGateSequencer_patch[] = 
R"(
PatchData:
  patch_name: 'Non-linear Gate Sequencer'
  description: Gates off the grid
  module_slugs:
    0: PanelMedium
    1: QCD
    2: QCDEXP
    3: SCM
  int_cables:
    - out:
        module_id: 1
        jack_id: 4
      ins:
        - module_id: 1
          jack_id: 1
        - module_id: 2
          jack_id: 0
    - out:
        module_id: 1
        jack_id: 1
      ins:
        - module_id: 1
          jack_id: 4
        - module_id: 2
          jack_id: 1
    - out:
        module_id: 1
        jack_id: 2
      ins:
        - module_id: 1
          jack_id: 7
        - module_id: 2
          jack_id: 2
    - out:
        module_id: 1
        jack_id: 3
      ins:
        - module_id: 1
          jack_id: 10
        - module_id: 2
          jack_id: 3
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 3
          jack_id: 0
  mapped_ins: []
  mapped_outs:
    - panel_jack_id: 1
      out:
        module_id: 2
        jack_id: 1
    - panel_jack_id: 0
      out:
        module_id: 2
        jack_id: 0
    - panel_jack_id: 2
      out:
        module_id: 2
        jack_id: 2
    - panel_jack_id: 3
      out:
        module_id: 2
        jack_id: 3
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
    - module_id: 1
      param_id: 3
      value: 0
    - module_id: 1
      param_id: 4
      value: 0
    - module_id: 2
      param_id: 0
      value: 0
    - module_id: 2
      param_id: 1
      value: 0
    - module_id: 2
      param_id: 2
      value: 0
    - module_id: 2
      param_id: 3
      value: 0
    - module_id: 2
      param_id: 4
      value: 0
    - module_id: 2
      param_id: 5
      value: 0
    - module_id: 2
      param_id: 6
      value: 0
    - module_id: 2
      param_id: 7
      value: 0.5
    - module_id: 2
      param_id: 8
      value: 0
    - module_id: 2
      param_id: 9
      value: 0.52
    - module_id: 2
      param_id: 10
      value: 0.5
    - module_id: 2
      param_id: 11
      value: 0.4945
    - module_id: 3
      param_id: 0
      value: 0
    - module_id: 3
      param_id: 1
      value: 0.5
    - module_id: 3
      param_id: 2
      value: 0.25
    - module_id: 3
      param_id: 3
      value: 0.25
    - module_id: 3
      param_id: 4
      value: 0.5
    - module_id: 3
      param_id: 5
      value: 0
    - module_id: 3
      param_id: 6
      value: 0
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
    - panel_knob_id: 4
      module_id: 2
      param_id: 1
      curve_type: 0
      min: 0
      max: 1
    - panel_knob_id: 5
      module_id: 2
      param_id: 4
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
      param_id: 3
      curve_type: 0
      min: 0
      max: 1
    - panel_knob_id: 8
      module_id: 2
      param_id: 6
      curve_type: 0
      min: 0
      max: 1
    - panel_knob_id: 9
      module_id: 2
      param_id: 2
      curve_type: 0
      min: 0
      max: 1
    - panel_knob_id: 10
      module_id: 2
      param_id: 5
      curve_type: 0
      min: 0
      max: 1
    - panel_knob_id: 11
      module_id: 2
      param_id: 8
      curve_type: 0
      min: 0
      max: 1

)";