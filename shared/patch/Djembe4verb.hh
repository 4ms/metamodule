static char Djembe4verb_patch[] = 
R"(
PatchData:
  patch_name: 'Djembe-4-verb'
  module_slugs:
    0: PanelMedium
    1: PitchShift
    2: Djembe
    3: Djembe
    4: StMix
    5: HPF
    6: MultiLFO
    7: Djembe
    8: Djembe
    9: CLKM
    10: CLKM
    11: CLKD
    12: CLKM
    13: Verb
  int_cables:
    - out:
        module_id: 3
        jack_id: 0
      ins:
        - module_id: 1
          jack_id: 0
    - out:
        module_id: 9
        jack_id: 0
      ins:
        - module_id: 3
          jack_id: 4
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 4
          jack_id: 0
    - out:
        module_id: 5
        jack_id: 0
      ins:
        - module_id: 4
          jack_id: 2
    - out:
        module_id: 7
        jack_id: 0
      ins:
        - module_id: 4
          jack_id: 4
    - out:
        module_id: 8
        jack_id: 0
      ins:
        - module_id: 4
          jack_id: 6
    - out:
        module_id: 2
        jack_id: 0
      ins:
        - module_id: 5
          jack_id: 1
    - out:
        module_id: 10
        jack_id: 0
      ins:
        - module_id: 8
          jack_id: 4
    - out:
        module_id: 6
        jack_id: 1
      ins:
        - module_id: 11
          jack_id: 1
    - out:
        module_id: 4
        jack_id: 0
      ins:
        - module_id: 13
          jack_id: 0
  mapped_ins:
    - panel_jack_id: 6
      ins:
        - module_id: 7
          jack_id: 4
        - module_id: 10
          jack_id: 1
    - panel_jack_id: 7
      ins:
        - module_id: 9
          jack_id: 1
        - module_id: 2
          jack_id: 4
  mapped_outs:
    - panel_jack_id: 0
      out:
        module_id: 2
        jack_id: 0
    - panel_jack_id: 1
      out:
        module_id: 3
        jack_id: 0
    - panel_jack_id: 2
      out:
        module_id: 1
        jack_id: 0
    - panel_jack_id: 5
      out:
        module_id: 4
        jack_id: 1
    - panel_jack_id: 3
      out:
        module_id: 5
        jack_id: 0
    - panel_jack_id: 7
      out:
        module_id: 6
        jack_id: 1
    - panel_jack_id: 6
      out:
        module_id: 11
        jack_id: 0
    - panel_jack_id: 4
      out:
        module_id: 13
        jack_id: 0
  static_knobs:
    - module_id: 1
      param_id: 0
      value: 0.7315
    - module_id: 1
      param_id: 1
      value: 0.5
    - module_id: 1
      param_id: 2
      value: 0.375
    - module_id: 1
      param_id: 3
      value: 1
    - module_id: 2
      param_id: 0
      value: 0.4435
    - module_id: 2
      param_id: 1
      value: 0.4335
    - module_id: 2
      param_id: 2
      value: 1
    - module_id: 2
      param_id: 3
      value: 0.618
    - module_id: 3
      param_id: 0
      value: 0.2835
    - module_id: 3
      param_id: 1
      value: 0.3885
    - module_id: 3
      param_id: 2
      value: 1
    - module_id: 3
      param_id: 3
      value: 0.3885
    - module_id: 4
      param_id: 0
      value: 1
    - module_id: 4
      param_id: 1
      value: 1
    - module_id: 4
      param_id: 2
      value: 1
    - module_id: 4
      param_id: 3
      value: 1
    - module_id: 4
      param_id: 4
      value: 0.3755
    - module_id: 4
      param_id: 5
      value: 0.6365
    - module_id: 4
      param_id: 6
      value: 0.356
    - module_id: 4
      param_id: 7
      value: 0.6115
    - module_id: 5
      param_id: 0
      value: 0.519
    - module_id: 5
      param_id: 1
      value: 0.3255
    - module_id: 5
      param_id: 2
      value: 0
    - module_id: 6
      param_id: 0
      value: 1
    - module_id: 6
      param_id: 1
      value: 0
    - module_id: 6
      param_id: 2
      value: 0.4965
    - module_id: 7
      param_id: 0
      value: 0.4335
    - module_id: 7
      param_id: 1
      value: 0.4575
    - module_id: 7
      param_id: 2
      value: 1
    - module_id: 7
      param_id: 3
      value: 0.4435
    - module_id: 8
      param_id: 0
      value: 0.45
    - module_id: 8
      param_id: 1
      value: 0.3885
    - module_id: 8
      param_id: 2
      value: 1
    - module_id: 8
      param_id: 3
      value: 0.4435
    - module_id: 9
      param_id: 0
      value: 0.375
    - module_id: 10
      param_id: 0
      value: 0.3255
    - module_id: 11
      param_id: 0
      value: 0.4575
    - module_id: 12
      param_id: 0
      value: 0
    - module_id: 13
      param_id: 0
      value: 0.3885
    - module_id: 13
      param_id: 1
      value: 0.618
    - module_id: 13
      param_id: 2
      value: 0.151
    - module_id: 13
      param_id: 3
      value: 0.078
    - module_id: 13
      param_id: 4
      value: 0.126
    - module_id: 13
      param_id: 5
      value: 0.872
    - module_id: 13
      param_id: 6
      value: 0
  mapped_knobs:
    - panel_knob_id: 0
      module_id: 3
      param_id: 0
      curve_type: 0
      min: 0
      max: 1
      alias_name: Pitch 1
    - panel_knob_id: 2
      module_id: 2
      param_id: 0
      curve_type: 0
      min: 0
      max: 1
      alias_name: 'Pitch-2'
    - panel_knob_id: 4
      module_id: 7
      param_id: 0
      curve_type: 0
      min: 0
      max: 1
      alias_name: Pitch3
    - panel_knob_id: 5
      module_id: 8
      param_id: 0
      curve_type: 0
      min: 0
      max: 1
      alias_name: Pitch4
    - panel_knob_id: 6
      module_id: 1
      param_id: 0
      curve_type: 0
      min: 0
      max: 1
      alias_name: 'P-shift-1'
    - panel_knob_id: 7
      module_id: 1
      param_id: 2
      curve_type: 0
      min: 0
      max: 1
    - panel_knob_id: 9
      module_id: 5
      param_id: 0
      curve_type: 0
      min: 0
      max: 1
    - panel_knob_id: 11
      module_id: 6
      param_id: 0
      curve_type: 0
      min: 0
      max: 1
    - panel_knob_id: 8
      module_id: 11
      param_id: 0
      curve_type: 0
      min: 0
      max: 1
    - panel_knob_id: 10
      module_id: 10
      param_id: 0
      curve_type: 0
      min: 0
      max: 1
    - panel_knob_id: 7
      module_id: 9
      param_id: 0
      curve_type: 0
      min: 0
      max: 1
    - panel_knob_id: 1
      module_id: 13
      param_id: 0
      curve_type: 0
      min: 0
      max: 1
    - panel_knob_id: 3
      module_id: 13
      param_id: 1
      curve_type: 0
      min: 0
      max: 1

)";