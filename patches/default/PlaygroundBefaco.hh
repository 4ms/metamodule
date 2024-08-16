static const char PlaygroundBefaco_patch[] =
	R"(
PatchData:
  patch_name: PlaygroundBefaco
  description: Patch Description
  module_slugs:
    0: '4msCompany:HubMedium'
    1: 'Befaco:EvenVCO'
    2: 'Befaco:Mixer'
    3: 'Befaco:Kickall'
    4: '4msCompany:MultiLFO'
    5: '4msCompany:CLKD'
    6: '4msCompany:ENVVCA'
    7: '4msCompany:CLKM'
    8: '4msCompany:SH'
    9: '4msCompany:Noise'
    10: 'Befaco:DualAtenuverter'
    11: 'Befaco:PonyVCO'
    12: '4msCompany:DLD'
  int_cables:
    - out:
        module_id: 3
        jack_id: 0
      ins:
        - module_id: 2
          jack_id: 0
      color: 35419
    - out:
        module_id: 4
        jack_id: 1
      ins:
        - module_id: 5
          jack_id: 1
        - module_id: 7
          jack_id: 1
        - module_id: 12
          jack_id: 0
      color: 1453
    - out:
        module_id: 5
        jack_id: 0
      ins:
        - module_id: 3
          jack_id: 0
      color: 13501
    - out:
        module_id: 1
        jack_id: 2
      ins:
        - module_id: 6
          jack_id: 4
      color: 64934
    - out:
        module_id: 6
        jack_id: 2
      ins:
        - module_id: 2
          jack_id: 1
      color: 1453
    - out:
        module_id: 7
        jack_id: 0
      ins:
        - module_id: 6
          jack_id: 1
        - module_id: 8
          jack_id: 0
      color: 35419
    - out:
        module_id: 8
        jack_id: 0
      ins:
        - module_id: 1
          jack_id: 1
      color: 1453
    - out:
        module_id: 9
        jack_id: 0
      ins:
        - module_id: 10
          jack_id: 0
      color: 61865
    - out:
        module_id: 10
        jack_id: 0
      ins:
        - module_id: 8
          jack_id: 1
      color: 61865
    - out:
        module_id: 11
        jack_id: 0
      ins:
        - module_id: 2
          jack_id: 2
      color: 13501
    - out:
        module_id: 6
        jack_id: 0
      ins:
        - module_id: 11
          jack_id: 1
      color: 1453
    - out:
        module_id: 1
        jack_id: 1
      ins:
        - module_id: 10
          jack_id: 1
      color: 64934
    - out:
        module_id: 10
        jack_id: 1
      ins:
        - module_id: 11
          jack_id: 0
      color: 1453
    - out:
        module_id: 2
        jack_id: 1
      ins:
        - module_id: 12
          jack_id: 1
      color: 64934
    - out:
        module_id: 2
        jack_id: 0
      ins:
        - module_id: 12
          jack_id: 6
      color: 61865
  mapped_ins: []
  mapped_outs:
    - panel_jack_id: 2
      out:
        module_id: 3
        jack_id: 0
    - panel_jack_id: 3
      out:
        module_id: 6
        jack_id: 2
    - panel_jack_id: 1
      out:
        module_id: 12
        jack_id: 3
    - panel_jack_id: 0
      out:
        module_id: 12
        jack_id: 6
  static_knobs:
    - module_id: 1
      param_id: 0
      value: 0.333333
    - module_id: 1
      param_id: 1
      value: 0.5
    - module_id: 1
      param_id: 2
      value: 0.5
    - module_id: 2
      param_id: 0
      value: 0.874289
    - module_id: 2
      param_id: 1
      value: 0.669271
    - module_id: 2
      param_id: 2
      value: 0.535535
    - module_id: 2
      param_id: 3
      value: 1
    - module_id: 3
      param_id: 0
      value: 0.63125
    - module_id: 3
      param_id: 1
      value: 0
    - module_id: 3
      param_id: 2
      value: 0.408434
    - module_id: 3
      param_id: 3
      value: 0.491566
    - module_id: 3
      param_id: 4
      value: 0.295
    - module_id: 3
      param_id: 5
      value: 0.153012
    - module_id: 4
      param_id: 0
      value: 0.19966
    - module_id: 4
      param_id: 1
      value: 0.5
    - module_id: 4
      param_id: 2
      value: 0.19966
    - module_id: 5
      param_id: 0
      value: 0.1005
    - module_id: 6
      param_id: 0
      value: 0
    - module_id: 6
      param_id: 1
      value: 0
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
      value: 1
    - module_id: 6
      param_id: 7
      value: 0
    - module_id: 7
      param_id: 0
      value: 0.104941
    - module_id: 10
      param_id: 0
      value: 0.619277
    - module_id: 10
      param_id: 1
      value: 0.5
    - module_id: 10
      param_id: 2
      value: 0.80241
    - module_id: 10
      param_id: 3
      value: 0.530241
    - module_id: 11
      param_id: 0
      value: 0.162651
    - module_id: 11
      param_id: 1
      value: 0
    - module_id: 11
      param_id: 2
      value: 0
    - module_id: 11
      param_id: 3
      value: 0.666667
    - module_id: 11
      param_id: 4
      value: 0.333333
    - module_id: 12
      param_id: 0
      value: 0.113253
    - module_id: 12
      param_id: 1
      value: 0
    - module_id: 12
      param_id: 2
      value: 0
    - module_id: 12
      param_id: 3
      value: 0.5
    - module_id: 12
      param_id: 4
      value: 0.506024
    - module_id: 12
      param_id: 5
      value: 0.628012
    - module_id: 12
      param_id: 6
      value: 0
    - module_id: 12
      param_id: 7
      value: 0
    - module_id: 12
      param_id: 8
      value: 0
    - module_id: 12
      param_id: 9
      value: 0
    - module_id: 12
      param_id: 10
      value: 0.364157
    - module_id: 12
      param_id: 11
      value: 0.949398
    - module_id: 12
      param_id: 12
      value: 0.589157
    - module_id: 12
      param_id: 13
      value: 0.589157
    - module_id: 12
      param_id: 14
      value: 1
    - module_id: 12
      param_id: 15
      value: 0
    - module_id: 12
      param_id: 16
      value: 0
    - module_id: 12
      param_id: 17
      value: 0
    - module_id: 12
      param_id: 18
      value: 0
    - module_id: 12
      param_id: 19
      value: 0
    - module_id: 12
      param_id: 20
      value: 0
    - module_id: 12
      param_id: 21
      value: 0
    - module_id: 12
      param_id: 22
      value: 0
    - module_id: 12
      param_id: 23
      value: 0
    - module_id: 12
      param_id: 24
      value: 0
    - module_id: 12
      param_id: 25
      value: 0
    - module_id: 12
      param_id: 26
      value: 0
    - module_id: 12
      param_id: 27
      value: 0
    - module_id: 12
      param_id: 28
      value: 0
    - module_id: 12
      param_id: 29
      value: 0
    - module_id: 12
      param_id: 30
      value: 0.5
    - module_id: 12
      param_id: 31
      value: 0.5
  mapped_knobs:
    - name: ''
      set:
        - panel_knob_id: 0
          module_id: 4
          param_id: 0
          curve_type: 0
          min: 0
          max: 0.623
        - panel_knob_id: 1
          module_id: 1
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 2
          module_id: 10
          param_id: 2
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 3
          module_id: 3
          param_id: 3
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 4
          module_id: 3
          param_id: 5
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 5
          module_id: 12
          param_id: 12
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 5
          module_id: 12
          param_id: 13
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 6
          module_id: 7
          param_id: 0
          curve_type: 0
          min: 0
          max: 0.541
        - panel_knob_id: 7
          module_id: 5
          param_id: 0
          curve_type: 0
          min: 0
          max: 0.201
        - panel_knob_id: 9
          module_id: 2
          param_id: 0
          curve_type: 0
          min: 0.26
          max: 1
        - panel_knob_id: 10
          module_id: 2
          param_id: 1
          curve_type: 0
          min: 0.195
          max: 1
        - panel_knob_id: 11
          module_id: 2
          param_id: 2
          curve_type: 0
          min: 0.274
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
  vcvModuleStates:
    - module_id: 1
      data: |-
        {"removePulseDC":true}
    - module_id: 11
      data: |-
        {"blockTZFMDC":true,"removePulseDC":true,"oversamplingIndex":1}
    - module_id: 12
      data: |-
        aLIm++Bd
)";
