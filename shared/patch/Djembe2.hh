static char Djembe2_patch[] =
	R"(
PatchData:
  patch_name: 'Djembe-2'
  description: "Dual Djembes, with FX. 
  Gate Ins trigger the djembes.
  Djembe #1 pans left, with PitchShifting.
  Djembe #2 pans right, with HPF.
  module_slugs:
    0: PanelMedium
    1: PitchShift
    2: Djembe
    3: Djembe
    4: StMix
    5: HPF
    6: MultiLFO
  int_cables:
    - out:
        module_id: 3
        jack_id: 0
      ins:
        - module_id: 1
          jack_id: 0
        - module_id: 4
          jack_id: 0
    - out:
        module_id: 2
        jack_id: 0
      ins:
        - module_id: 4
          jack_id: 2
        - module_id: 5
          jack_id: 1
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 4
          jack_id: 4
    - out:
        module_id: 5
        jack_id: 0
      ins:
        - module_id: 4
          jack_id: 6
  mapped_ins:
    - panel_jack_id: 6
      ins:
        - module_id: 3
          jack_id: 4
    - panel_jack_id: 7
      ins:
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
    - panel_jack_id: 4
      out:
        module_id: 4
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
        module_id: 6
        jack_id: 3
  static_knobs:
    - module_id: 1
      param_id: 0
      value: 0.8035
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
      value: 0.618
    - module_id: 2
      param_id: 1
      value: 0.4335
    - module_id: 2
      param_id: 2
      value: 1
    - module_id: 2
      param_id: 3
      value: 0.45
    - module_id: 3
      param_id: 0
      value: 0.2835
    - module_id: 3
      param_id: 1
      value: 0.3885
    - module_id: 3
      param_id: 2
      value: 0.2835
    - module_id: 3
      param_id: 3
      value: 0.4435
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
      value: 0.333829
    - module_id: 4
      param_id: 5
      value: 0.3615
    - module_id: 4
      param_id: 6
      value: 0.699142
    - module_id: 4
      param_id: 7
      value: 0.603457
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
      value: 0.1605
    - module_id: 6
      param_id: 1
      value: 0
    - module_id: 6
      param_id: 2
      value: 0.4965
  mapped_knobs:
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
      alias_name: 'Sharp-1'
    - panel_knob_id: 2
      module_id: 3
      param_id: 3
      curve_type: 0
      min: 0
      max: 1
      alias_name: Strike 1
    - panel_knob_id: 3
      module_id: 2
      param_id: 0
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
      param_id: 3
      curve_type: 0
      min: 0
      max: 1
    - panel_knob_id: 6
      module_id: 1
      param_id: 0
      curve_type: 0
      min: 0
      max: 1
    - panel_knob_id: 7
      module_id: 1
      param_id: 2
      curve_type: 0
      min: 0
      max: 1
      alias_name: Wndw
    - panel_knob_id: 8
      module_id: 4
      param_id: 4
      curve_type: 0
      min: 0.025
      max: 0.936
    - panel_knob_id: 8
      module_id: 4
      param_id: 6
      curve_type: 0
      min: 0.91
      max: 0.288
    - panel_knob_id: 10
      module_id: 4
      param_id: 5
      curve_type: 0
      min: 0
      max: 1
    - panel_knob_id: 10
      module_id: 4
      param_id: 7
      curve_type: 0
      min: 0.85
      max: 0.168
)";
