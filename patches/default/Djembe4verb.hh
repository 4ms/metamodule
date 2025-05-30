static const char Djembe4verb_patch[] =
	R"(
PatchData:
  patch_name: 'Djembe-4-verb'
  description: Patch Description
  module_slugs:
    0: HubMedium
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
    14: CLKD
    15: Freeverb
  int_cables:
    - out:
        module_id: 3
        jack_id: 0
      ins:
        - module_id: 1
          jack_id: 0
    - out:
        module_id: 2
        jack_id: 0
      ins:
        - module_id: 5
          jack_id: 1
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
        module_id: 9
        jack_id: 0
      ins:
        - module_id: 3
          jack_id: 4
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
        - module_id: 9
          jack_id: 1
        - module_id: 14
          jack_id: 1
    - out:
        module_id: 4
        jack_id: 0
      ins:
        - module_id: 13
          jack_id: 0
    - out:
        module_id: 11
        jack_id: 0
      ins:
        - module_id: 10
          jack_id: 1
        - module_id: 12
          jack_id: 1
    - out:
        module_id: 12
        jack_id: 0
      ins:
        - module_id: 2
          jack_id: 4
    - out:
        module_id: 14
        jack_id: 0
      ins:
        - module_id: 7
          jack_id: 4
    - out:
        module_id: 4
        jack_id: 1
      ins:
        - module_id: 15
          jack_id: 0
  mapped_ins: []
  mapped_outs:
    - panel_jack_id: 7
      out:
        module_id: 11
        jack_id: 0
    - panel_jack_id: 0
      out:
        module_id: 15
        jack_id: 0
    - panel_jack_id: 1
      out:
        module_id: 13
        jack_id: 0
    - panel_jack_id: 2
      out:
        module_id: 4
        jack_id: 0
    - panel_jack_id: 3
      out:
        module_id: 4
        jack_id: 1
  static_knobs:
    - module_id: 1
      param_id: 0
      value: 0.513554
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
      value: 0.365608
    - module_id: 2
      param_id: 1
      value: 0.4335
    - module_id: 2
      param_id: 2
      value: 1
    - module_id: 2
      param_id: 3
      value: 0.223018
    - module_id: 3
      param_id: 0
      value: 0.299162
    - module_id: 3
      param_id: 1
      value: 0.806024
    - module_id: 3
      param_id: 2
      value: 0.648193
    - module_id: 3
      param_id: 3
      value: 0.43109
    - module_id: 4
      param_id: 0
      value: 0.308608
    - module_id: 4
      param_id: 1
      value: 0.297891
    - module_id: 4
      param_id: 2
      value: 0.619476
    - module_id: 4
      param_id: 3
      value: 0.519
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
      value: 0.299162
    - module_id: 6
      param_id: 1
      value: 0
    - module_id: 6
      param_id: 2
      value: 0.4965
    - module_id: 7
      param_id: 0
      value: 0.446916
    - module_id: 7
      param_id: 1
      value: 0.673494
    - module_id: 7
      param_id: 2
      value: 1
    - module_id: 7
      param_id: 3
      value: 0.43109
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
      value: 0.96506
    - module_id: 9
      param_id: 0
      value: 0.223018
    - module_id: 10
      param_id: 0
      value: 0.45
    - module_id: 11
      param_id: 0
      value: 0.365608
    - module_id: 12
      param_id: 0
      value: 0.446916
    - module_id: 13
      param_id: 0
      value: 0.308608
    - module_id: 13
      param_id: 1
      value: 0.299162
    - module_id: 13
      param_id: 2
      value: 0.365608
    - module_id: 13
      param_id: 3
      value: 0.297891
    - module_id: 13
      param_id: 4
      value: 0.223018
    - module_id: 13
      param_id: 5
      value: 0.96506
    - module_id: 13
      param_id: 6
      value: 0
    - module_id: 14
      param_id: 0
      value: 0.508199
    - module_id: 15
      param_id: 0
      value: 0.446916
    - module_id: 15
      param_id: 1
      value: 0.508199
    - module_id: 15
      param_id: 2
      value: 0.45
    - module_id: 15
      param_id: 3
      value: 0.806024
  mapped_knobs:
    - name: Clocks
      set:
        - panel_knob_id: 0
          module_id: 6
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 1
          module_id: 11
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 2
          module_id: 9
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 3
          module_id: 12
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 4
          module_id: 14
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 5
          module_id: 10
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 6
          module_id: 4
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 7
          module_id: 4
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 8
          module_id: 15
          param_id: 3
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 9
          module_id: 4
          param_id: 3
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 10
          module_id: 4
          param_id: 2
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 11
          module_id: 13
          param_id: 5
          curve_type: 0
          min: 0
          max: 1
    - name: Djembes
      set:
        - panel_knob_id: 0
          module_id: 3
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 1
          module_id: 2
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 2
          module_id: 2
          param_id: 3
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 3
          module_id: 7
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 4
          module_id: 7
          param_id: 3
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 5
          module_id: 8
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 6
          module_id: 4
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 7
          module_id: 4
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 8
          module_id: 3
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 9
          module_id: 4
          param_id: 3
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 10
          module_id: 4
          param_id: 2
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 11
          module_id: 8
          param_id: 3
          curve_type: 0
          min: 0
          max: 1
    - name: Reverbs
      set:
        - panel_knob_id: 0
          module_id: 13
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 2
          module_id: 13
          param_id: 4
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 3
          module_id: 15
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 4
          module_id: 15
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 5
          module_id: 15
          param_id: 2
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 6
          module_id: 13
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 7
          module_id: 13
          param_id: 2
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 7
          module_id: 13
          param_id: 3
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 8
          module_id: 13
          param_id: 5
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 11
          module_id: 15
          param_id: 3
          curve_type: 0
          min: 0
          max: 1

)";
