static char Sloth_Drone_patch[] =
	R"(
PatchData:
  patch_name: Sloth Drone
  description: "Knob A is main rate. Knobs D + E + F are the mixer. X and Y control the Sloth's randomness. A scrubs it"
  module_slugs:
    0: HubMedium
    1: Rings
    2: PhasorEuclidean
    3: PhasorGen
    4: Mixer
    5: Mixer
    6: Rings
    7: PhasorEuclidean
    8: TripleSloth
    9: Rings
  int_cables:
    - out:
        module_id: 3
        jack_id: 0
      ins:
        - module_id: 2
          jack_id: 0
        - module_id: 7
          jack_id: 0
      color: 35419
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 4
          jack_id: 0
        - module_id: 6
          jack_id: 7
      color: 64934
    - out:
        module_id: 1
        jack_id: 1
      ins:
        - module_id: 5
          jack_id: 0
      color: 1453
    - out:
        module_id: 6
        jack_id: 0
      ins:
        - module_id: 4
          jack_id: 1
        - module_id: 9
          jack_id: 7
      color: 64934
    - out:
        module_id: 6
        jack_id: 1
      ins:
        - module_id: 5
          jack_id: 1
      color: 1453
    - out:
        module_id: 7
        jack_id: 0
      ins:
        - module_id: 2
          jack_id: 2
      color: 13501
    - out:
        module_id: 2
        jack_id: 0
      ins:
        - module_id: 7
          jack_id: 3
        - module_id: 9
          jack_id: 0
      color: 35921
    - out:
        module_id: 2
        jack_id: 1
      ins:
        - module_id: 1
          jack_id: 5
      color: 61865
    - out:
        module_id: 8
        jack_id: 3
      ins:
        - module_id: 1
          jack_id: 0
      color: 1453
    - out:
        module_id: 8
        jack_id: 10
      ins:
        - module_id: 6
          jack_id: 2
      color: 13501
    - out:
        module_id: 8
        jack_id: 5
      ins:
        - module_id: 6
          jack_id: 4
      color: 35921
    - out:
        module_id: 8
        jack_id: 4
      ins:
        - module_id: 6
          jack_id: 0
      color: 35419
    - out:
        module_id: 7
        jack_id: 1
      ins:
        - module_id: 6
          jack_id: 5
      color: 64934
    - out:
        module_id: 3
        jack_id: 1
      ins:
        - module_id: 9
          jack_id: 5
      color: 35419
    - out:
        module_id: 9
        jack_id: 1
      ins:
        - module_id: 5
          jack_id: 2
      color: 13501
    - out:
        module_id: 9
        jack_id: 0
      ins:
        - module_id: 4
          jack_id: 2
      color: 35921
    - out:
        module_id: 8
        jack_id: 7
      ins:
        - module_id: 9
          jack_id: 2
      color: 13501
    - out:
        module_id: 8
        jack_id: 8
      ins:
        - module_id: 9
          jack_id: 4
      color: 35921
    - out:
        module_id: 8
        jack_id: 1
      ins:
        - module_id: 1
          jack_id: 2
      color: 35419
  mapped_ins: []
  mapped_outs:
    - panel_jack_id: 0
      out:
        module_id: 4
        jack_id: 0
    - panel_jack_id: 1
      out:
        module_id: 5
        jack_id: 0
  static_knobs:
    - module_id: 1
      param_id: 0
      value: 0
    - module_id: 1
      param_id: 1
      value: 0
    - module_id: 1
      param_id: 2
      value: 0.324096
    - module_id: 1
      param_id: 3
      value: 0.757831
    - module_id: 1
      param_id: 4
      value: 0.316868
    - module_id: 1
      param_id: 5
      value: 0.0759037
    - module_id: 1
      param_id: 6
      value: 0.136145
    - module_id: 1
      param_id: 7
      value: 0.674667
    - module_id: 1
      param_id: 8
      value: 0.5
    - module_id: 1
      param_id: 9
      value: 0.752
    - module_id: 1
      param_id: 10
      value: 0.809333
    - module_id: 1
      param_id: 11
      value: 0.869333
    - module_id: 2
      param_id: 0
      value: 0.15873
    - module_id: 2
      param_id: 1
      value: 1
    - module_id: 2
      param_id: 2
      value: 0.234375
    - module_id: 2
      param_id: 3
      value: 0.556
    - module_id: 2
      param_id: 4
      value: 0.227711
    - module_id: 2
      param_id: 5
      value: 1
    - module_id: 2
      param_id: 6
      value: 0.5
    - module_id: 2
      param_id: 7
      value: 1
    - module_id: 2
      param_id: 8
      value: 0.8
    - module_id: 2
      param_id: 9
      value: 1
    - module_id: 2
      param_id: 10
      value: 1
    - module_id: 2
      param_id: 11
      value: 1
    - module_id: 2
      param_id: 12
      value: 1
    - module_id: 2
      param_id: 13
      value: 1
    - module_id: 3
      param_id: 0
      value: 0.198235
    - module_id: 3
      param_id: 1
      value: 1
    - module_id: 3
      param_id: 2
      value: 0.269879
    - module_id: 3
      param_id: 3
      value: 1
    - module_id: 3
      param_id: 4
      value: 0.395181
    - module_id: 3
      param_id: 5
      value: 1
    - module_id: 3
      param_id: 6
      value: 0.507937
    - module_id: 3
      param_id: 7
      value: 1
    - module_id: 3
      param_id: 8
      value: 0.563855
    - module_id: 3
      param_id: 9
      value: 1
    - module_id: 3
      param_id: 10
      value: 0
    - module_id: 4
      param_id: 0
      value: 0.603615
    - module_id: 4
      param_id: 1
      value: 0.498795
    - module_id: 4
      param_id: 2
      value: 0.661446
    - module_id: 4
      param_id: 3
      value: 0
    - module_id: 5
      param_id: 0
      value: 0.603615
    - module_id: 5
      param_id: 1
      value: 0.498795
    - module_id: 5
      param_id: 2
      value: 0.661446
    - module_id: 5
      param_id: 3
      value: 0
    - module_id: 6
      param_id: 0
      value: 0
    - module_id: 6
      param_id: 1
      value: 0
    - module_id: 6
      param_id: 2
      value: 0.342168
    - module_id: 6
      param_id: 3
      value: 0.695181
    - module_id: 6
      param_id: 4
      value: 0.39759
    - module_id: 6
      param_id: 5
      value: 0.348193
    - module_id: 6
      param_id: 6
      value: 0.418072
    - module_id: 6
      param_id: 7
      value: 0.744
    - module_id: 6
      param_id: 8
      value: 0.709333
    - module_id: 6
      param_id: 9
      value: 0.704
    - module_id: 6
      param_id: 10
      value: 0.348
    - module_id: 6
      param_id: 11
      value: 0.86
    - module_id: 7
      param_id: 0
      value: 0.238095
    - module_id: 7
      param_id: 1
      value: 1
    - module_id: 7
      param_id: 2
      value: 0.28125
    - module_id: 7
      param_id: 3
      value: 1
    - module_id: 7
      param_id: 4
      value: 0.356626
    - module_id: 7
      param_id: 5
      value: 1
    - module_id: 7
      param_id: 6
      value: 0.610843
    - module_id: 7
      param_id: 7
      value: 1
    - module_id: 7
      param_id: 8
      value: 0.4
    - module_id: 7
      param_id: 9
      value: 1
    - module_id: 7
      param_id: 10
      value: 1
    - module_id: 7
      param_id: 11
      value: 1
    - module_id: 7
      param_id: 12
      value: 1
    - module_id: 7
      param_id: 13
      value: 1
    - module_id: 8
      param_id: 0
      value: 0.698795
    - module_id: 8
      param_id: 1
      value: 0.713253
    - module_id: 9
      param_id: 0
      value: 0
    - module_id: 9
      param_id: 1
      value: 0
    - module_id: 9
      param_id: 2
      value: 0.442169
    - module_id: 9
      param_id: 3
      value: 0.833735
    - module_id: 9
      param_id: 4
      value: 0.184337
    - module_id: 9
      param_id: 5
      value: 0.759036
    - module_id: 9
      param_id: 6
      value: 0.174699
    - module_id: 9
      param_id: 7
      value: 0.636
    - module_id: 9
      param_id: 8
      value: 0.5
    - module_id: 9
      param_id: 9
      value: 0.294667
    - module_id: 9
      param_id: 10
      value: 0.5
    - module_id: 9
      param_id: 11
      value: 0.696
  mapped_knobs:
    - name: ''
      set:
        - panel_knob_id: 0
          module_id: 3
          param_id: 0
          curve_type: 0
          min: 0.054
          max: 0.399
        - panel_knob_id: 1
          module_id: 9
          param_id: 3
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 2
          module_id: 9
          param_id: 5
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 3
          module_id: 4
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 3
          module_id: 5
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 4
          module_id: 4
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 4
          module_id: 5
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 5
          module_id: 4
          param_id: 2
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 5
          module_id: 5
          param_id: 2
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 6
          module_id: 3
          param_id: 2
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 7
          module_id: 3
          param_id: 6
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 9
          module_id: 8
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 10
          module_id: 8
          param_id: 1
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

'vcvModuleStates':
  - 'id': 1
    'plugin': 'AudibleInstruments'
    'model': 'Rings'
    'version': '2.0.0'
    'data':
      'polyphony': 0
      'model': 1
      'easterEgg': false
  - 'id': 6
    'plugin': 'AudibleInstruments'
    'model': 'Rings'
    'version': '2.0.0'
    'data':
      'polyphony': 2
      'model': 1
      'easterEgg': false
  - 'id': 9
    'plugin': 'AudibleInstruments'
    'model': 'Rings'
    'version': '2.0.0'
    'data':
      'polyphony': 1
      'model': 1
      'easterEgg': false

)";
