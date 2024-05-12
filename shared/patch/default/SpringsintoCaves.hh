static const char SpringsIntoCaves_patch[] =
	R"(
PatchData:
  patch_name: Springs into Caves
  description: Patch Description
  module_slugs:
    0: HubMedium
    1: Rings
    2: Tapo
    3: QCD
    4: Mixer
    5: MPEG
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 2
          jack_id: 4
      color: 1453
    - out:
        module_id: 3
        jack_id: 2
      ins:
        - module_id: 1
          jack_id: 5
      color: 13501
    - out:
        module_id: 3
        jack_id: 4
      ins:
        - module_id: 4
          jack_id: 0
      color: 61865
    - out:
        module_id: 3
        jack_id: 6
      ins:
        - module_id: 4
          jack_id: 1
      color: 64934
    - out:
        module_id: 3
        jack_id: 8
      ins:
        - module_id: 4
          jack_id: 3
      color: 1453
    - out:
        module_id: 4
        jack_id: 0
      ins:
        - module_id: 1
          jack_id: 4
      color: 13501
    - out:
        module_id: 5
        jack_id: 1
      ins:
        - module_id: 3
          jack_id: 2
      color: 61865
    - out:
        module_id: 4
        jack_id: 1
      ins:
        - module_id: 1
          jack_id: 2
      color: 64934
  mapped_ins: []
  mapped_outs:
    - panel_jack_id: 0
      out:
        module_id: 2
        jack_id: 1
    - panel_jack_id: 1
      out:
        module_id: 2
        jack_id: 2
  static_knobs:
    - module_id: 1
      param_id: 0
      value: 0
    - module_id: 1
      param_id: 1
      value: 0
    - module_id: 1
      param_id: 2
      value: 0.63253
    - module_id: 1
      param_id: 3
      value: 0.5610665
    - module_id: 1
      param_id: 4
      value: 0.679518
    - module_id: 1
      param_id: 5
      value: 0.333735
    - module_id: 1
      param_id: 6
      value: 0.304819
    - module_id: 1
      param_id: 7
      value: 0.253333
    - module_id: 1
      param_id: 8
      value: 0.5
    - module_id: 1
      param_id: 9
      value: 0.376
    - module_id: 1
      param_id: 10
      value: 0.262667
    - module_id: 1
      param_id: 11
      value: 0.761333
    - module_id: 2
      param_id: 0
      value: 0.5
    - module_id: 2
      param_id: 1
      value: 0.4928693
    - module_id: 2
      param_id: 2
      value: 0.278313
    - module_id: 2
      param_id: 3
      value: 0.13
    - module_id: 2
      param_id: 4
      value: 0.7477743
    - module_id: 2
      param_id: 5
      value: 0.5
    - module_id: 2
      param_id: 6
      value: 0
    - module_id: 2
      param_id: 7
      value: 0
    - module_id: 2
      param_id: 8
      value: 0
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
    - module_id: 2
      param_id: 15
      value: 0
    - module_id: 2
      param_id: 16
      value: 0
    - module_id: 2
      param_id: 17
      value: 0
    - module_id: 2
      param_id: 18
      value: 0
    - module_id: 2
      param_id: 19
      value: 0
    - module_id: 2
      param_id: 20
      value: 0
    - module_id: 3
      param_id: 0
      value: 0.5
    - module_id: 3
      param_id: 1
      value: 0.331325
    - module_id: 3
      param_id: 2
      value: 0.5
    - module_id: 3
      param_id: 3
      value: 0.246988
    - module_id: 3
      param_id: 4
      value: 0.5
    - module_id: 3
      param_id: 5
      value: 0.5
    - module_id: 3
      param_id: 6
      value: 0.5
    - module_id: 3
      param_id: 7
      value: 0.30241
    - module_id: 3
      param_id: 8
      value: 0.5
    - module_id: 3
      param_id: 9
      value: 0.5
    - module_id: 3
      param_id: 10
      value: 0.5
    - module_id: 3
      param_id: 11
      value: 0.226506
    - module_id: 3
      param_id: 12
      value: 0.5
    - module_id: 3
      param_id: 13
      value: 0.5
    - module_id: 3
      param_id: 14
      value: 0.5
    - module_id: 3
      param_id: 15
      value: 0.175904
    - module_id: 3
      param_id: 16
      value: 0
    - module_id: 3
      param_id: 17
      value: 0
    - module_id: 3
      param_id: 18
      value: 0
    - module_id: 3
      param_id: 19
      value: 0
    - module_id: 3
      param_id: 20
      value: 0
    - module_id: 4
      param_id: 0
      value: 0.187952
    - module_id: 4
      param_id: 1
      value: 0.216867
    - module_id: 4
      param_id: 2
      value: 0.273494
    - module_id: 4
      param_id: 3
      value: 0
    - module_id: 5
      param_id: 0
      value: 0.5
    - module_id: 5
      param_id: 1
      value: 0.5
    - module_id: 5
      param_id: 2
      value: 0.5
    - module_id: 5
      param_id: 3
      value: 0.5
    - module_id: 5
      param_id: 4
      value: 0
    - module_id: 5
      param_id: 5
      value: 0
    - module_id: 5
      param_id: 6
      value: 0.5
    - module_id: 5
      param_id: 7
      value: 0
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
      value: 0
    - module_id: 5
      param_id: 12
      value: 0
  mapped_knobs:
    - name: ''
      set:
        - panel_knob_id: 1
          module_id: 2
          param_id: 4
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
        - panel_knob_id: 9
          module_id: 2
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
  midi_maps:
    name: ''
    set: []
  midi_poly_num: 0
  vcvModuleStates:
    - module_id: 1
      data: |-
        {"polyphony":0,"model":1,"easterEgg":false}
    - module_id: 2
      data: |-
        +aA+uQD/AAA=

)";
