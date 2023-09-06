static char EnOsc8StepSeq_patch[] =
	R"(
PatchData:
  patch_name: 'EnOsc-8-step-seq'
  description: '8-step seq driving an EnOsc. Patch clock into Gate1, or use internal LFO  (Out8) into Gate1.'
  module_slugs:
    0: HubMedium
    1: Seq8
    2: MultiLFO
    3: EnOsc
    4: ENVVCA
    5: ENVVCA
    6: CLKD
    7: CLKD
    8: CLKM
    9: CLKM
    10: EnOsc
    11: Seq8
  int_cables:
    - out:
        module_id: 3
        jack_id: 0
      ins:
        - module_id: 4
          jack_id: 4
    - out:
        module_id: 1
        jack_id: 1
      ins:
        - module_id: 3
          jack_id: 5
    - out:
        module_id: 4
        jack_id: 0
      ins:
        - module_id: 3
          jack_id: 8
    - out:
        module_id: 2
        jack_id: 1
      ins:
        - module_id: 1
          jack_id: 0
        - module_id: 6
          jack_id: 1
        - module_id: 7
          jack_id: 1
        - module_id: 11
          jack_id: 0
    - out:
        module_id: 6
        jack_id: 0
      ins:
        - module_id: 8
          jack_id: 1
    - out:
        module_id: 8
        jack_id: 0
      ins:
        - module_id: 5
          jack_id: 1
    - out:
        module_id: 7
        jack_id: 0
      ins:
        - module_id: 9
          jack_id: 1
    - out:
        module_id: 9
        jack_id: 0
      ins:
        - module_id: 4
          jack_id: 1
    - out:
        module_id: 10
        jack_id: 0
      ins:
        - module_id: 5
          jack_id: 4
    - out:
        module_id: 5
        jack_id: 0
      ins:
        - module_id: 10
          jack_id: 2
    - out:
        module_id: 11
        jack_id: 1
      ins:
        - module_id: 10
          jack_id: 0
  mapped_ins:
    - panel_jack_id: 7
      ins:
        - module_id: 1
          jack_id: 1
  mapped_outs:
    - panel_jack_id: 7
      out:
        module_id: 2
        jack_id: 1
    - panel_jack_id: 3
      out:
        module_id: 1
        jack_id: 0
    - panel_jack_id: 2
      out:
        module_id: 1
        jack_id: 1
    - panel_jack_id: 0
      out:
        module_id: 4
        jack_id: 2
    - panel_jack_id: 1
      out:
        module_id: 5
        jack_id: 2
  static_knobs:
    - module_id: 1
      param_id: 0
      value: 0.366265
    - module_id: 1
      param_id: 1
      value: 0.666265
    - module_id: 1
      param_id: 2
      value: 0.540964
    - module_id: 1
      param_id: 3
      value: 0.407229
    - module_id: 1
      param_id: 4
      value: 0.631325
    - module_id: 1
      param_id: 5
      value: 0.303614
    - module_id: 1
      param_id: 6
      value: 0.284337
    - module_id: 1
      param_id: 7
      value: 0.173494
    - module_id: 2
      param_id: 0
      value: 0.40482
    - module_id: 2
      param_id: 1
      value: 0
    - module_id: 2
      param_id: 2
      value: 0.377108
    - module_id: 3
      param_id: 0
      value: 0.5
    - module_id: 3
      param_id: 1
      value: 0.306024
    - module_id: 3
      param_id: 2
      value: 0
    - module_id: 3
      param_id: 3
      value: 0.331325
    - module_id: 3
      param_id: 4
      value: 0.40482
    - module_id: 3
      param_id: 5
      value: 0.280723
    - module_id: 3
      param_id: 6
      value: 0
    - module_id: 3
      param_id: 7
      value: 0
    - module_id: 3
      param_id: 8
      value: 0.379826
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
      value: 0.0762654
    - module_id: 4
      param_id: 1
      value: 0.331325
    - module_id: 4
      param_id: 2
      value: 0.351807
    - module_id: 4
      param_id: 3
      value: 0.5
    - module_id: 4
      param_id: 4
      value: 0.5
    - module_id: 4
      param_id: 5
      value: 0
    - module_id: 4
      param_id: 6
      value: 0.5
    - module_id: 4
      param_id: 7
      value: 0
    - module_id: 5
      param_id: 0
      value: 0.173494
    - module_id: 5
      param_id: 1
      value: 0.331325
    - module_id: 5
      param_id: 2
      value: 0.154
    - module_id: 5
      param_id: 3
      value: 0.5
    - module_id: 5
      param_id: 4
      value: 0.5
    - module_id: 5
      param_id: 5
      value: 0
    - module_id: 5
      param_id: 6
      value: 0.5
    - module_id: 5
      param_id: 7
      value: 0
    - module_id: 6
      param_id: 0
      value: 0.631325
    - module_id: 7
      param_id: 0
      value: 0.666265
    - module_id: 8
      param_id: 0
      value: 0.303614
    - module_id: 9
      param_id: 0
      value: 0.540964
    - module_id: 10
      param_id: 0
      value: 0.361446
    - module_id: 10
      param_id: 1
      value: 0.379826
    - module_id: 10
      param_id: 2
      value: 0.5
    - module_id: 10
      param_id: 3
      value: 0.331325
    - module_id: 10
      param_id: 4
      value: 0.40482
    - module_id: 10
      param_id: 5
      value: 0
    - module_id: 10
      param_id: 6
      value: 0
    - module_id: 10
      param_id: 7
      value: 0
    - module_id: 10
      param_id: 8
      value: 0.280723
    - module_id: 10
      param_id: 9
      value: 0.20241
    - module_id: 10
      param_id: 10
      value: 0
    - module_id: 10
      param_id: 11
      value: 0
    - module_id: 10
      param_id: 12
      value: 0
    - module_id: 10
      param_id: 13
      value: 0
    - module_id: 10
      param_id: 14
      value: 0
    - module_id: 11
      param_id: 0
      value: 0.366265
    - module_id: 11
      param_id: 1
      value: 0.666265
    - module_id: 11
      param_id: 2
      value: 0.540964
    - module_id: 11
      param_id: 3
      value: 0.407229
    - module_id: 11
      param_id: 4
      value: 0.631325
    - module_id: 11
      param_id: 5
      value: 0.303614
    - module_id: 11
      param_id: 6
      value: 0.284337
    - module_id: 11
      param_id: 7
      value: 0.173494
  mapped_knobs:
    - name: seq1
      set:
        - panel_knob_id: 0
          module_id: 1
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 1
          module_id: 1
          param_id: 2
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 2
          module_id: 1
          param_id: 3
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 3
          module_id: 1
          param_id: 4
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 4
          module_id: 1
          param_id: 5
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 5
          module_id: 1
          param_id: 6
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 6
          module_id: 3
          param_id: 4
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 7
          module_id: 3
          param_id: 3
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 8
          module_id: 1
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 9
          module_id: 3
          param_id: 8
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 10
          module_id: 3
          param_id: 5
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 11
          module_id: 1
          param_id: 7
          curve_type: 0
          min: 0
          max: 1
    - name: seq2
      set:
        - panel_knob_id: 0
          module_id: 11
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 1
          module_id: 11
          param_id: 2
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 2
          module_id: 11
          param_id: 3
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 3
          module_id: 11
          param_id: 4
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 4
          module_id: 11
          param_id: 5
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 5
          module_id: 11
          param_id: 6
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 6
          module_id: 10
          param_id: 4
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 7
          module_id: 10
          param_id: 3
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 8
          module_id: 11
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 9
          module_id: 10
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 10
          module_id: 10
          param_id: 8
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 11
          module_id: 11
          param_id: 7
          curve_type: 0
          min: 0
          max: 1
    - name: timing
      set:
        - panel_knob_id: 0
          module_id: 7
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 1
          module_id: 9
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 2
          module_id: 4
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 3
          module_id: 6
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 4
          module_id: 8
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 5
          module_id: 5
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 6
          module_id: 2
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 8
          module_id: 4
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 11
          module_id: 5
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
    - name: ''
      set: []

)";
