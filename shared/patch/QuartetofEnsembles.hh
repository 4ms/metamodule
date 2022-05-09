static char QuartetofEnsembles_patch[] = 
R"(
PatchData:
  patch_name: Quartet of Ensembles
  description: 'Four EnOsc and a matrix mixer, what more do you need?'
  module_slugs:
    0: PanelMedium
    1: EnOsc
    2: EnOsc
    3: EnOsc
    4: EnOsc
    5: VCAM
  int_cables:
    - out:
        module_id: 2
        jack_id: 0
      ins:
        - module_id: 5
          jack_id: 0
    - out:
        module_id: 3
        jack_id: 0
      ins:
        - module_id: 5
          jack_id: 5
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 5
          jack_id: 10
    - out:
        module_id: 4
        jack_id: 0
      ins:
        - module_id: 5
          jack_id: 15
  mapped_ins: []
  mapped_outs:
    - panel_jack_id: 0
      out:
        module_id: 5
        jack_id: 0
    - panel_jack_id: 1
      out:
        module_id: 5
        jack_id: 1
    - panel_jack_id: 2
      out:
        module_id: 5
        jack_id: 2
    - panel_jack_id: 3
      out:
        module_id: 5
        jack_id: 3
  static_knobs:
    - module_id: 5
      param_id: 0
      value: 1
    - module_id: 5
      param_id: 1
      value: 1
    - module_id: 5
      param_id: 2
      value: 1
    - module_id: 5
      param_id: 3
      value: 1
    - module_id: 5
      param_id: 4
      value: 1
    - module_id: 5
      param_id: 5
      value: 1
    - module_id: 5
      param_id: 6
      value: 1
    - module_id: 5
      param_id: 7
      value: 1
    - module_id: 5
      param_id: 8
      value: 1
    - module_id: 5
      param_id: 9
      value: 1
    - module_id: 5
      param_id: 10
      value: 1
    - module_id: 5
      param_id: 11
      value: 1
    - module_id: 5
      param_id: 12
      value: 1
    - module_id: 5
      param_id: 13
      value: 1
    - module_id: 5
      param_id: 14
      value: 1
    - module_id: 5
      param_id: 15
      value: 1
    - module_id: 5
      param_id: 16
      value: 1
    - module_id: 5
      param_id: 17
      value: 0
    - module_id: 5
      param_id: 18
      value: 0
    - module_id: 5
      param_id: 19
      value: 1
    - module_id: 5
      param_id: 20
      value: 0
    - module_id: 5
      param_id: 21
      value: 0
    - module_id: 5
      param_id: 22
      value: 0
    - module_id: 5
      param_id: 23
      value: 0
    - module_id: 5
      param_id: 24
      value: 0
    - module_id: 5
      param_id: 25
      value: 0
    - module_id: 5
      param_id: 26
      value: 0
    - module_id: 5
      param_id: 27
      value: 0
    - module_id: 5
      param_id: 28
      value: 0
    - module_id: 5
      param_id: 29
      value: 0
    - module_id: 5
      param_id: 30
      value: 0
    - module_id: 5
      param_id: 31
      value: 0
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
      value: 0.5
    - module_id: 1
      param_id: 9
      value: 0
    - module_id: 1
      param_id: 10
      value: 0
    - module_id: 1
      param_id: 11
      value: 0
    - module_id: 1
      param_id: 12
      value: 0
    - module_id: 1
      param_id: 13
      value: 0
    - module_id: 1
      param_id: 14
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
      value: 0
    - module_id: 2
      param_id: 8
      value: 0.5
    - module_id: 2
      param_id: 9
      value: 0
    - module_id: 2
      param_id: 10
      value: 0
    - module_id: 2
      param_id: 11
      value: 0
    - module_id: 2
      param_id: 12
      value: 0
    - module_id: 2
      param_id: 13
      value: 0
    - module_id: 2
      param_id: 14
      value: 0
    - module_id: 3
      param_id: 0
      value: 0
    - module_id: 3
      param_id: 1
      value: 0
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
    - module_id: 3
      param_id: 7
      value: 0
    - module_id: 3
      param_id: 8
      value: 0.5
    - module_id: 3
      param_id: 9
      value: 0
    - module_id: 3
      param_id: 10
      value: 0
    - module_id: 3
      param_id: 11
      value: 0
    - module_id: 3
      param_id: 12
      value: 0
    - module_id: 3
      param_id: 13
      value: 0
    - module_id: 3
      param_id: 14
      value: 0
    - module_id: 4
      param_id: 0
      value: 0
    - module_id: 4
      param_id: 1
      value: 0
    - module_id: 4
      param_id: 2
      value: 0
    - module_id: 4
      param_id: 3
      value: 0
    - module_id: 4
      param_id: 4
      value: 0
    - module_id: 4
      param_id: 5
      value: 0
    - module_id: 4
      param_id: 6
      value: 0
    - module_id: 4
      param_id: 7
      value: 0
    - module_id: 4
      param_id: 8
      value: 0.5
    - module_id: 4
      param_id: 9
      value: 0
    - module_id: 4
      param_id: 10
      value: 0
    - module_id: 4
      param_id: 11
      value: 0
    - module_id: 4
      param_id: 12
      value: 0
    - module_id: 4
      param_id: 13
      value: 0
    - module_id: 4
      param_id: 14
      value: 0
  mapped_knobs:
    - panel_knob_id: 0
      module_id: 2
      param_id: 4
      curve_type: 0
      min: 0
      max: 1
    - panel_knob_id: 1
      module_id: 3
      param_id: 4
      curve_type: 0
      min: 0
      max: 1
    - panel_knob_id: 2
      module_id: 1
      param_id: 4
      curve_type: 0
      min: 0
      max: 1
    - panel_knob_id: 3
      module_id: 4
      param_id: 4
      curve_type: 0
      min: 0
      max: 1

)";