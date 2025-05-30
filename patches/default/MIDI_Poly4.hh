static const char MIDI_Poly4_patch[] =
	R"(
PatchData:
  patch_name: 'MIDI-Poly4'
  description: 'Mix Outs on 1 and 2, separate outs on 3,4,5,6'
  module_slugs:
    0: '4msCompany:HubMedium'
    1: '4msCompany:ENVVCA'
    2: '4msCompany:ENVVCA'
    3: '4msCompany:ENVVCA'
    4: '4msCompany:ENVVCA'
    5: '4msCompany:EnOsc'
    6: '4msCompany:EnOsc'
    7: '4msCompany:EnOsc'
    8: '4msCompany:EnOsc'
    9: '4msCompany:Atvert2'
    10: '4msCompany:Atvert2'
    11: '4msCompany:Atvert2'
    12: '4msCompany:Atvert2'
    13: '4msCompany:StMix'
  int_cables:
    - out:
        module_id: 7
        jack_id: 0
      ins:
        - module_id: 3
          jack_id: 4
      color: 1453
    - out:
        module_id: 8
        jack_id: 0
      ins:
        - module_id: 4
          jack_id: 4
      color: 13501
    - out:
        module_id: 6
        jack_id: 0
      ins:
        - module_id: 2
          jack_id: 4
      color: 61865
    - out:
        module_id: 3
        jack_id: 0
      ins:
        - module_id: 7
          jack_id: 3
      color: 1453
    - out:
        module_id: 11
        jack_id: 0
      ins:
        - module_id: 7
          jack_id: 7
      color: 1453
    - out:
        module_id: 12
        jack_id: 0
      ins:
        - module_id: 7
          jack_id: 8
      color: 1453
    - out:
        module_id: 4
        jack_id: 0
      ins:
        - module_id: 8
          jack_id: 3
      color: 13501
    - out:
        module_id: 11
        jack_id: 1
      ins:
        - module_id: 8
          jack_id: 7
      color: 13501
    - out:
        module_id: 12
        jack_id: 1
      ins:
        - module_id: 8
          jack_id: 8
      color: 13501
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 5
          jack_id: 3
      color: 35419
    - out:
        module_id: 9
        jack_id: 0
      ins:
        - module_id: 5
          jack_id: 7
      color: 35419
    - out:
        module_id: 10
        jack_id: 0
      ins:
        - module_id: 5
          jack_id: 8
      color: 35419
    - out:
        module_id: 2
        jack_id: 0
      ins:
        - module_id: 6
          jack_id: 3
      color: 61865
    - out:
        module_id: 9
        jack_id: 1
      ins:
        - module_id: 6
          jack_id: 7
      color: 61865
    - out:
        module_id: 10
        jack_id: 1
      ins:
        - module_id: 6
          jack_id: 8
      color: 61865
    - out:
        module_id: 1
        jack_id: 2
      ins:
        - module_id: 13
          jack_id: 0
      color: 35419
    - out:
        module_id: 2
        jack_id: 2
      ins:
        - module_id: 13
          jack_id: 2
      color: 61865
    - out:
        module_id: 3
        jack_id: 2
      ins:
        - module_id: 13
          jack_id: 4
      color: 1453
    - out:
        module_id: 4
        jack_id: 2
      ins:
        - module_id: 13
          jack_id: 6
      color: 13501
    - out:
        module_id: 5
        jack_id: 0
      ins:
        - module_id: 1
          jack_id: 4
      color: 35419
  mapped_ins:
    - panel_jack_id: 272
      ins:
        - module_id: 3
          jack_id: 3
    - panel_jack_id: 273
      ins:
        - module_id: 4
          jack_id: 3
    - panel_jack_id: 275
      ins:
        - module_id: 2
          jack_id: 3
    - panel_jack_id: 256
      ins:
        - module_id: 7
          jack_id: 0
    - panel_jack_id: 257
      ins:
        - module_id: 8
          jack_id: 0
    - panel_jack_id: 258
      ins:
        - module_id: 5
          jack_id: 0
    - panel_jack_id: 259
      ins:
        - module_id: 6
          jack_id: 0
    - panel_jack_id: 288
      ins:
        - module_id: 12
          jack_id: 0
    - panel_jack_id: 289
      ins:
        - module_id: 12
          jack_id: 1
    - panel_jack_id: 290
      ins:
        - module_id: 10
          jack_id: 0
    - panel_jack_id: 291
      ins:
        - module_id: 10
          jack_id: 1
    - panel_jack_id: 304
      ins:
        - module_id: 11
          jack_id: 0
    - panel_jack_id: 305
      ins:
        - module_id: 11
          jack_id: 1
    - panel_jack_id: 306
      ins:
        - module_id: 9
          jack_id: 0
    - panel_jack_id: 307
      ins:
        - module_id: 9
          jack_id: 1
    - panel_jack_id: 274
      ins:
        - module_id: 1
          jack_id: 3
  mapped_outs:
    - panel_jack_id: 4
      out:
        module_id: 3
        jack_id: 2
    - panel_jack_id: 5
      out:
        module_id: 4
        jack_id: 2
    - panel_jack_id: 3
      out:
        module_id: 2
        jack_id: 2
    - panel_jack_id: 2
      out:
        module_id: 1
        jack_id: 2
    - panel_jack_id: 1
      out:
        module_id: 13
        jack_id: 1
    - panel_jack_id: 0
      out:
        module_id: 13
        jack_id: 0
  static_knobs:
    - module_id: 3
      param_id: 0
      value: 0
    - module_id: 3
      param_id: 1
      value: 0.5
    - module_id: 3
      param_id: 2
      value: 0
    - module_id: 3
      param_id: 3
      value: 0.27
    - module_id: 3
      param_id: 4
      value: 0.5
    - module_id: 3
      param_id: 5
      value: 0
    - module_id: 3
      param_id: 6
      value: 1
    - module_id: 3
      param_id: 7
      value: 0
    - module_id: 4
      param_id: 0
      value: 0
    - module_id: 4
      param_id: 1
      value: 0.5
    - module_id: 4
      param_id: 2
      value: 0
    - module_id: 4
      param_id: 3
      value: 0.318072
    - module_id: 4
      param_id: 4
      value: 0.691566
    - module_id: 4
      param_id: 5
      value: 0
    - module_id: 4
      param_id: 6
      value: 1
    - module_id: 4
      param_id: 7
      value: 0
    - module_id: 2
      param_id: 0
      value: 0
    - module_id: 2
      param_id: 1
      value: 0.5
    - module_id: 2
      param_id: 2
      value: 0
    - module_id: 2
      param_id: 3
      value: 0.26
    - module_id: 2
      param_id: 4
      value: 0.5
    - module_id: 2
      param_id: 5
      value: 0
    - module_id: 2
      param_id: 6
      value: 1
    - module_id: 2
      param_id: 7
      value: 0
    - module_id: 7
      param_id: 0
      value: 0.0578314
    - module_id: 7
      param_id: 1
      value: 0.212048
    - module_id: 7
      param_id: 2
      value: 0.5
    - module_id: 7
      param_id: 3
      value: 0.497932
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
      value: 1
    - module_id: 7
      param_id: 10
      value: 1
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
    - module_id: 7
      param_id: 15
      value: 0
    - module_id: 7
      param_id: 16
      value: 0
    - module_id: 7
      param_id: 17
      value: 0.5
    - module_id: 7
      param_id: 18
      value: 1
    - module_id: 7
      param_id: 19
      value: 0.5
    - module_id: 8
      param_id: 0
      value: 0.0578314
    - module_id: 8
      param_id: 1
      value: 0.212048
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
      value: 1
    - module_id: 8
      param_id: 10
      value: 1
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
    - module_id: 8
      param_id: 15
      value: 0
    - module_id: 8
      param_id: 16
      value: 0
    - module_id: 8
      param_id: 17
      value: 0.5
    - module_id: 8
      param_id: 18
      value: 1
    - module_id: 8
      param_id: 19
      value: 0.5
    - module_id: 5
      param_id: 0
      value: 0.0578314
    - module_id: 5
      param_id: 1
      value: 0.212048
    - module_id: 5
      param_id: 2
      value: 0.5
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
      value: 0
    - module_id: 5
      param_id: 7
      value: 0
    - module_id: 5
      param_id: 8
      value: 0
    - module_id: 5
      param_id: 9
      value: 1
    - module_id: 5
      param_id: 10
      value: 1
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
    - module_id: 5
      param_id: 15
      value: 0
    - module_id: 5
      param_id: 16
      value: 0
    - module_id: 5
      param_id: 17
      value: 0.5
    - module_id: 5
      param_id: 18
      value: 1
    - module_id: 5
      param_id: 19
      value: 0.5
    - module_id: 6
      param_id: 0
      value: 0.0578314
    - module_id: 6
      param_id: 1
      value: 0.212048
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
      value: 1
    - module_id: 6
      param_id: 10
      value: 1
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
    - module_id: 6
      param_id: 15
      value: 0
    - module_id: 6
      param_id: 16
      value: 0
    - module_id: 6
      param_id: 17
      value: 0.5
    - module_id: 6
      param_id: 18
      value: 1
    - module_id: 6
      param_id: 19
      value: 0.5
    - module_id: 12
      param_id: 0
      value: 0.466265
    - module_id: 12
      param_id: 1
      value: 0.466265
    - module_id: 10
      param_id: 0
      value: 0.466265
    - module_id: 10
      param_id: 1
      value: 0.466265
    - module_id: 11
      param_id: 0
      value: 0.490362
    - module_id: 11
      param_id: 1
      value: 0.490362
    - module_id: 9
      param_id: 0
      value: 0.490362
    - module_id: 9
      param_id: 1
      value: 0.490362
    - module_id: 13
      param_id: 0
      value: 0.875
    - module_id: 13
      param_id: 1
      value: 0.875
    - module_id: 13
      param_id: 2
      value: 0.875
    - module_id: 13
      param_id: 3
      value: 0.875
    - module_id: 13
      param_id: 4
      value: 0.368675
    - module_id: 13
      param_id: 5
      value: 0.624096
    - module_id: 13
      param_id: 6
      value: 0.359036
    - module_id: 13
      param_id: 7
      value: 0.637349
    - module_id: 1
      param_id: 0
      value: 0
    - module_id: 1
      param_id: 1
      value: 0.5
    - module_id: 1
      param_id: 2
      value: 0
    - module_id: 1
      param_id: 3
      value: 0.252
    - module_id: 1
      param_id: 4
      value: 0.5
    - module_id: 1
      param_id: 5
      value: 0
    - module_id: 1
      param_id: 6
      value: 1
    - module_id: 1
      param_id: 7
      value: 0
  mapped_knobs:
    - name: ''
      set:
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
        - panel_knob_id: 1
          module_id: 8
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
          module_id: 5
          param_id: 2
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 1
          module_id: 6
          param_id: 2
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
        - panel_knob_id: 5
          module_id: 8
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
          module_id: 7
          param_id: 8
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 5
          module_id: 6
          param_id: 8
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
        - panel_knob_id: 9
          module_id: 12
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 9
          module_id: 10
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 9
          module_id: 12
          param_id: 1
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
          module_id: 9
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 10
          module_id: 9
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 11
          module_id: 8
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
          module_id: 5
          param_id: 5
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 11
          module_id: 6
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
  midi_poly_num: 4
  vcvModuleStates: []
)";
