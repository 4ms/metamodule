static char EnOscPoly4_patch[] =
	R"(
PatchData:
  patch_name: EnOscPoly4
  description: 'V/oct: Bottom row of Ins. Triggers:Top row of Ins. Stereo Mix Outs 1+2. Separate outs 5-8'
  module_slugs:
    0: HubMedium
    1: ENVVCA
    2: ENVVCA
    3: ENVVCA
    4: ENVVCA
    5: EnOsc
    6: EnOsc
    7: EnOsc
    8: EnOsc
    9: StMix
  int_cables:
    - out:
        module_id: 5
        jack_id: 0
      ins:
        - module_id: 1
          jack_id: 4
      color: 1453
    - out:
        module_id: 6
        jack_id: 0
      ins:
        - module_id: 2
          jack_id: 4
      color: 13501
    - out:
        module_id: 7
        jack_id: 0
      ins:
        - module_id: 3
          jack_id: 4
      color: 35419
    - out:
        module_id: 8
        jack_id: 0
      ins:
        - module_id: 4
          jack_id: 4
      color: 61865
    - out:
        module_id: 4
        jack_id: 0
      ins:
        - module_id: 8
          jack_id: 3
      color: 61865
    - out:
        module_id: 3
        jack_id: 0
      ins:
        - module_id: 7
          jack_id: 3
      color: 35419
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 5
          jack_id: 3
      color: 1453
    - out:
        module_id: 2
        jack_id: 0
      ins:
        - module_id: 6
          jack_id: 3
      color: 13501
    - out:
        module_id: 3
        jack_id: 2
      ins:
        - module_id: 9
          jack_id: 0
      color: 35419
    - out:
        module_id: 4
        jack_id: 2
      ins:
        - module_id: 9
          jack_id: 2
      color: 61865
    - out:
        module_id: 1
        jack_id: 2
      ins:
        - module_id: 9
          jack_id: 4
      color: 1453
    - out:
        module_id: 2
        jack_id: 2
      ins:
        - module_id: 9
          jack_id: 6
      color: 13501
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 7
          jack_id: 0
    - panel_jack_id: 1
      ins:
        - module_id: 8
          jack_id: 0
    - panel_jack_id: 2
      ins:
        - module_id: 5
          jack_id: 0
    - panel_jack_id: 3
      ins:
        - module_id: 6
          jack_id: 0
    - panel_jack_id: 6
      ins:
        - module_id: 3
          jack_id: 1
    - panel_jack_id: 7
      ins:
        - module_id: 4
          jack_id: 1
    - panel_jack_id: 5
      ins:
        - module_id: 2
          jack_id: 1
    - panel_jack_id: 4
      ins:
        - module_id: 1
          jack_id: 1
  mapped_outs:
    - panel_jack_id: 4
      out:
        module_id: 3
        jack_id: 2
    - panel_jack_id: 5
      out:
        module_id: 4
        jack_id: 2
    - panel_jack_id: 6
      out:
        module_id: 1
        jack_id: 2
    - panel_jack_id: 7
      out:
        module_id: 2
        jack_id: 2
    - panel_jack_id: 0
      out:
        module_id: 9
        jack_id: 0
    - panel_jack_id: 1
      out:
        module_id: 9
        jack_id: 1
  static_knobs:
    - module_id: 1
      param_id: 0
      value: 0.180723
    - module_id: 1
      param_id: 1
      value: 0.5
    - module_id: 1
      param_id: 2
      value: 0
    - module_id: 1
      param_id: 3
      value: 0.5
    - module_id: 1
      param_id: 4
      value: 0.5
    - module_id: 1
      param_id: 5
      value: 0
    - module_id: 1
      param_id: 6
      value: 0.5
    - module_id: 1
      param_id: 7
      value: 0
    - module_id: 2
      param_id: 0
      value: 0.180723
    - module_id: 2
      param_id: 1
      value: 0.5
    - module_id: 2
      param_id: 2
      value: 0
    - module_id: 2
      param_id: 3
      value: 0.318072
    - module_id: 2
      param_id: 4
      value: 0.691566
    - module_id: 2
      param_id: 5
      value: 0
    - module_id: 2
      param_id: 6
      value: 0.5
    - module_id: 2
      param_id: 7
      value: 0
    - module_id: 3
      param_id: 0
      value: 0.180723
    - module_id: 3
      param_id: 1
      value: 0.5
    - module_id: 3
      param_id: 2
      value: 0
    - module_id: 3
      param_id: 3
      value: 0.5
    - module_id: 3
      param_id: 4
      value: 0.5
    - module_id: 3
      param_id: 5
      value: 0
    - module_id: 3
      param_id: 6
      value: 0.5
    - module_id: 3
      param_id: 7
      value: 0
    - module_id: 4
      param_id: 0
      value: 0.180723
    - module_id: 4
      param_id: 1
      value: 0.5
    - module_id: 4
      param_id: 2
      value: 0
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
      value: 0.5
    - module_id: 5
      param_id: 1
      value: 0.495181
    - module_id: 5
      param_id: 2
      value: 0.5
    - module_id: 5
      param_id: 3
      value: 0.0629921
    - module_id: 5
      param_id: 4
      value: 0.5
    - module_id: 5
      param_id: 5
      value: 0
    - module_id: 5
      param_id: 6
      value: 0
    - module_id: 5
      param_id: 7
      value: 0.165354
    - module_id: 5
      param_id: 8
      value: 0
    - module_id: 5
      param_id: 9
      value: 0
    - module_id: 5
      param_id: 10
      value: 0
    - module_id: 5
      param_id: 11
      value: 0.5
    - module_id: 5
      param_id: 12
      value: 0
    - module_id: 5
      param_id: 13
      value: 0
    - module_id: 5
      param_id: 14
      value: 0
    - module_id: 6
      param_id: 0
      value: 0.5
    - module_id: 6
      param_id: 1
      value: 0.495181
    - module_id: 6
      param_id: 2
      value: 0.5
    - module_id: 6
      param_id: 3
      value: 0.5
    - module_id: 6
      param_id: 4
      value: 0.5
    - module_id: 6
      param_id: 5
      value: 0
    - module_id: 6
      param_id: 6
      value: 0
    - module_id: 6
      param_id: 7
      value: 0
    - module_id: 6
      param_id: 8
      value: 0
    - module_id: 6
      param_id: 9
      value: 0
    - module_id: 6
      param_id: 10
      value: 0
    - module_id: 6
      param_id: 11
      value: 0.5
    - module_id: 6
      param_id: 12
      value: 0
    - module_id: 6
      param_id: 13
      value: 0
    - module_id: 6
      param_id: 14
      value: 0
    - module_id: 7
      param_id: 0
      value: 0.5
    - module_id: 7
      param_id: 1
      value: 0.495181
    - module_id: 7
      param_id: 2
      value: 0.5
    - module_id: 7
      param_id: 3
      value: 0.5
    - module_id: 7
      param_id: 4
      value: 0.5
    - module_id: 7
      param_id: 5
      value: 0
    - module_id: 7
      param_id: 6
      value: 0
    - module_id: 7
      param_id: 7
      value: 0
    - module_id: 7
      param_id: 8
      value: 0
    - module_id: 7
      param_id: 9
      value: 0
    - module_id: 7
      param_id: 10
      value: 0
    - module_id: 7
      param_id: 11
      value: 0.5
    - module_id: 7
      param_id: 12
      value: 0
    - module_id: 7
      param_id: 13
      value: 0
    - module_id: 7
      param_id: 14
      value: 0
    - module_id: 8
      param_id: 0
      value: 0.5
    - module_id: 8
      param_id: 1
      value: 0.495181
    - module_id: 8
      param_id: 2
      value: 0.5
    - module_id: 8
      param_id: 3
      value: 0.5
    - module_id: 8
      param_id: 4
      value: 0.5
    - module_id: 8
      param_id: 5
      value: 0
    - module_id: 8
      param_id: 6
      value: 0
    - module_id: 8
      param_id: 7
      value: 0
    - module_id: 8
      param_id: 8
      value: 0
    - module_id: 8
      param_id: 9
      value: 0
    - module_id: 8
      param_id: 10
      value: 0
    - module_id: 8
      param_id: 11
      value: 0.5
    - module_id: 8
      param_id: 12
      value: 0
    - module_id: 8
      param_id: 13
      value: 0
    - module_id: 8
      param_id: 14
      value: 0
    - module_id: 9
      param_id: 0
      value: 0.75
    - module_id: 9
      param_id: 1
      value: 0.75
    - module_id: 9
      param_id: 2
      value: 0.75
    - module_id: 9
      param_id: 3
      value: 0.75
    - module_id: 9
      param_id: 4
      value: 0.377108
    - module_id: 9
      param_id: 5
      value: 0.63253
    - module_id: 9
      param_id: 6
      value: 0.39759
    - module_id: 9
      param_id: 7
      value: 0.603615
  mapped_knobs:
    - name: ''
      set:
        - panel_knob_id: 0
          module_id: 5
          param_id: 4
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 0
          module_id: 6
          param_id: 4
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 0
          module_id: 7
          param_id: 4
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 0
          module_id: 8
          param_id: 4
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 1
          module_id: 6
          param_id: 2
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 1
          module_id: 5
          param_id: 2
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 1
          module_id: 7
          param_id: 2
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 1
          module_id: 8
          param_id: 2
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 2
          module_id: 5
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 2
          module_id: 6
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 2
          module_id: 7
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 2
          module_id: 8
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 3
          module_id: 6
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 3
          module_id: 7
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 3
          module_id: 8
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 3
          module_id: 5
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 4
          module_id: 5
          param_id: 6
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 4
          module_id: 6
          param_id: 6
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 4
          module_id: 7
          param_id: 6
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 4
          module_id: 8
          param_id: 6
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 5
          module_id: 6
          param_id: 8
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 5
          module_id: 7
          param_id: 8
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 5
          module_id: 5
          param_id: 8
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 5
          module_id: 8
          param_id: 8
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 6
          module_id: 1
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 6
          module_id: 2
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 6
          module_id: 3
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
          module_id: 1
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 7
          module_id: 2
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 7
          module_id: 3
          param_id: 1
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
          module_id: 5
          param_id: 11
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 8
          module_id: 6
          param_id: 11
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 8
          module_id: 7
          param_id: 11
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 8
          module_id: 8
          param_id: 11
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 11
          module_id: 6
          param_id: 5
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 11
          module_id: 5
          param_id: 5
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 11
          module_id: 7
          param_id: 5
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 11
          module_id: 8
          param_id: 5
          curve_type: 0
          min: 0
          max: 1
    - name: ''
      set: []
    - name: ''
      set: []
    - name: ''
      set: []
    - name: ''
      set: []
    - name: ''
      set: []
    - name: ''
      set: []
    - name: ''
      set: []
  midi_maps:
    name: ''
    set: []
  midi_poly_num: 0

'vcvModuleStates': []
)";
