static char Djembe4verb_patch[] =
	R"(
PatchData:
  patch_name: 'Djembe-4-verb'
  description: Four Djembes with clock divders and multipliers, and stereo reverb
  module_slugs:
    0: HubMedium
    1: Djembe
    2: Djembe
    3: StMix
    4: MultiLFO
    5: Djembe
    6: Djembe
    7: CLKM
    8: CLKM
    9: CLKD
    10: Freeverb
    11: Freeverb
  int_cables:
    - out:
        module_id: 4
        jack_id: 1
      ins:
        - module_id: 2
          jack_id: 4
        - module_id: 9
          jack_id: 1
    - out:
        module_id: 2
        jack_id: 0
      ins:
        - module_id: 3
          jack_id: 0
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 3
          jack_id: 2
    - out:
        module_id: 5
        jack_id: 0
      ins:
        - module_id: 3
          jack_id: 4
    - out:
        module_id: 6
        jack_id: 0
      ins:
        - module_id: 3
          jack_id: 6
    - out:
        module_id: 7
        jack_id: 0
      ins:
        - module_id: 5
          jack_id: 4
    - out:
        module_id: 8
        jack_id: 0
      ins:
        - module_id: 6
          jack_id: 4
    - out:
        module_id: 9
        jack_id: 0
      ins:
        - module_id: 7
          jack_id: 1
        - module_id: 8
          jack_id: 1
    - out:
        module_id: 3
        jack_id: 0
      ins:
        - module_id: 10
          jack_id: 0
    - out:
        module_id: 3
        jack_id: 1
      ins:
        - module_id: 11
          jack_id: 0
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 4
          jack_id: 2
  mapped_outs:
    - panel_jack_id: 7
      out:
        module_id: 4
        jack_id: 1
    - panel_jack_id: 0
      out:
        module_id: 10
        jack_id: 0
    - panel_jack_id: 1
      out:
        module_id: 11
        jack_id: 0
    - panel_jack_id: 3
      out:
        module_id: 1
        jack_id: 0
    - panel_jack_id: 4
      out:
        module_id: 5
        jack_id: 0
    - panel_jack_id: 5
      out:
        module_id: 6
        jack_id: 0
  static_knobs:
    - module_id: 1
      param_id: 0
      value: 0.3885
    - module_id: 1
      param_id: 1
      value: 0.4335
    - module_id: 1
      param_id: 2
      value: 1
    - module_id: 1
      param_id: 3
      value: 0.618
    - module_id: 2
      param_id: 0
      value: 0.69
    - module_id: 2
      param_id: 1
      value: 0.3885
    - module_id: 2
      param_id: 2
      value: 1
    - module_id: 2
      param_id: 3
      value: 0.3885
    - module_id: 3
      param_id: 0
      value: 1
    - module_id: 3
      param_id: 1
      value: 1
    - module_id: 3
      param_id: 2
      value: 1
    - module_id: 3
      param_id: 3
      value: 1
    - module_id: 3
      param_id: 4
      value: 0.3755
    - module_id: 3
      param_id: 5
      value: 0.6365
    - module_id: 3
      param_id: 6
      value: 0.356
    - module_id: 3
      param_id: 7
      value: 0.6115
    - module_id: 4
      param_id: 0
      value: 0.459
    - module_id: 4
      param_id: 1
      value: 0
    - module_id: 4
      param_id: 2
      value: 0.4965
    - module_id: 5
      param_id: 0
      value: 0.4435
    - module_id: 5
      param_id: 1
      value: 0.4575
    - module_id: 5
      param_id: 2
      value: 1
    - module_id: 5
      param_id: 3
      value: 0.4435
    - module_id: 6
      param_id: 0
      value: 0.3855
    - module_id: 6
      param_id: 1
      value: 0.3885
    - module_id: 6
      param_id: 2
      value: 1
    - module_id: 6
      param_id: 3
      value: 0.4435
    - module_id: 7
      param_id: 0
      value: 0.375
    - module_id: 8
      param_id: 0
      value: 0.6495
    - module_id: 9
      param_id: 0
      value: 0.546
    - module_id: 10
      param_id: 0
      value: 0.453
    - module_id: 10
      param_id: 1
      value: 0.432
    - module_id: 10
      param_id: 2
      value: 0.25
    - module_id: 10
      param_id: 3
      value: 0.73
    - module_id: 11
      param_id: 0
      value: 0.5835
    - module_id: 11
      param_id: 1
      value: 0.432
    - module_id: 11
      param_id: 2
      value: 0.25
    - module_id: 11
      param_id: 3
      value: 0.73
  mapped_knobs:
    - name: 'EnOsc #1'
      set:
      - panel_knob_id: 0
        module_id: 2
        param_id: 0
        curve_type: 0
        min: 0
        max: 1
        alias_name: Pitch 1
      - panel_knob_id: 1
        module_id: 1
        param_id: 0
        curve_type: 0
        min: 0
        max: 1
        alias_name: 'Pitch-2'
      - panel_knob_id: 2
        module_id: 5
        param_id: 0
        curve_type: 0
        min: 0
        max: 1
        alias_name: Pitch3
      - panel_knob_id: 3
        module_id: 6
        param_id: 0
        curve_type: 0
        min: 0
        max: 1
        alias_name: Pitch4
      - panel_knob_id: 11
        module_id: 4
        param_id: 0
        curve_type: 0
        min: 0
        max: 0.459
      - panel_knob_id: 6
        module_id: 9
        param_id: 0
        curve_type: 0
        min: 0
        max: 1
      - panel_knob_id: 8
        module_id: 8
        param_id: 0
        curve_type: 0
        min: 0
        max: 1
      - panel_knob_id: 7
        module_id: 7
        param_id: 0
        curve_type: 0
        min: 0
        max: 1
      - panel_knob_id: 9
        module_id: 10
        param_id: 3
        curve_type: 0
        min: 0
        max: 1
      - panel_knob_id: 9
        module_id: 11
        param_id: 3
        curve_type: 0
        min: 0
        max: 1
      - panel_knob_id: 4
        module_id: 10
        param_id: 0
        curve_type: 0
        min: 0
        max: 1
      - panel_knob_id: 5
        module_id: 11
        param_id: 0
        curve_type: 0
        min: 0
        max: 1
      - panel_knob_id: 10
        module_id: 11
        param_id: 1
        curve_type: 0
        min: 0
        max: 1
      - panel_knob_id: 10
        module_id: 10
        param_id: 1
        curve_type: 0
        min: 0
        max: 1

)";
