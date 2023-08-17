static char SpectralPings_patch[] =
	R"(
PatchData:
  patch_name: Spectral Pings
  description: 'Echo-y resonant pings'
  module_slugs:
    0: HubMedium
    1: SMR
    2: QCD
    3: DLD
  int_cables:
    - out:
        module_id: 1
        jack_id: 6
      ins:
        - module_id: 3
          jack_id: 1
    - out:
        module_id: 1
        jack_id: 7
      ins:
        - module_id: 3
          jack_id: 6
    - out:
        module_id: 2
        jack_id: 3
      ins:
        - module_id: 1
          jack_id: 10
    - out:
        module_id: 2
        jack_id: 4
      ins:
        - module_id: 1
          jack_id: 11
    - out:
        module_id: 2
        jack_id: 2
      ins:
        - module_id: 1
          jack_id: 12
    - out:
        module_id: 2
        jack_id: 1
      ins:
        - module_id: 1
          jack_id: 14
    - out:
        module_id: 3
        jack_id: 1
      ins:
        - module_id: 2
          jack_id: 0
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 3
          jack_id: 2
    - panel_jack_id: 1
      ins:
        - module_id: 3
          jack_id: 5
    - panel_jack_id: 6
      ins:
        - module_id: 3
          jack_id: 3
    - panel_jack_id: 7
      ins:
        - module_id: 3
          jack_id: 4
    - panel_jack_id: 2
      ins:
        - module_id: 3
          jack_id: 9
    - panel_jack_id: 3
      ins:
        - module_id: 3
          jack_id: 14
  mapped_outs:
    - panel_jack_id: 0
      out:
        module_id: 3
        jack_id: 3
    - panel_jack_id: 1
      out:
        module_id: 3
        jack_id: 6
    - panel_jack_id: 2
      out:
        module_id: 3
        jack_id: 4
    - panel_jack_id: 3
      out:
        module_id: 3
        jack_id: 5
  static_knobs:
    - module_id: 3
      param_id: 0
      value: 0
    - module_id: 3
      param_id: 1
      value: 0
    - module_id: 3
      param_id: 2
      value: 0
    - module_id: 3
      param_id: 3
      value: 0
    - module_id: 3
      param_id: 4
      value: 1
    - module_id: 3
      param_id: 5
      value: 0.875
    - module_id: 3
      param_id: 6
      value: 0.875
    - module_id: 3
      param_id: 7
      value: 1
    - module_id: 3
      param_id: 8
      value: 0
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
    - module_id: 1
      param_id: 0
      value: 1
    - module_id: 1
      param_id: 1
      value: 0.5
    - module_id: 1
      param_id: 2
      value: 0.564
    - module_id: 1
      param_id: 3
      value: 0.66
    - module_id: 1
      param_id: 4
      value: 0.5
    - module_id: 1
      param_id: 5
      value: 1
    - module_id: 1
      param_id: 6
      value: 0
    - module_id: 1
      param_id: 7
      value: 0
    - module_id: 1
      param_id: 8
      value: 0
    - module_id: 1
      param_id: 9
      value: 0
    - module_id: 1
      param_id: 10
      value: 0
    - module_id: 1
      param_id: 11
      value: 0
    - module_id: 1
      param_id: 12
      value: 0
    - module_id: 1
      param_id: 13
      value: 0
    - module_id: 1
      param_id: 14
      value: 0
    - module_id: 1
      param_id: 15
      value: 0
    - module_id: 1
      param_id: 16
      value: 0
    - module_id: 1
      param_id: 17
      value: 0
    - module_id: 1
      param_id: 18
      value: 0
    - module_id: 1
      param_id: 19
      value: 0
    - module_id: 1
      param_id: 20
      value: 0
    - module_id: 1
      param_id: 21
      value: 0
    - module_id: 1
      param_id: 22
      value: 0
    - module_id: 1
      param_id: 23
      value: 0
    - module_id: 2
      param_id: 0
      value: 0.531
    - module_id: 2
      param_id: 1
      value: 0.621
    - module_id: 2
      param_id: 2
      value: 0.3855
    - module_id: 2
      param_id: 3
      value: 0.495
    - module_id: 2
      param_id: 4
      value: 0
  mapped_knobs:
    - name: 'Default'
      set:
      - panel_knob_id: 0
        module_id: 1
        param_id: 9
        curve_type: 0
        min: 0
        max: 1
      - panel_knob_id: 1
        module_id: 1
        param_id: 8
        curve_type: 0
        min: 0
        max: 1
      - panel_knob_id: 2
        module_id: 2
        param_id: 0
        curve_type: 0
        min: 0
        max: 1
      - panel_knob_id: 3
        module_id: 2
        param_id: 1
        curve_type: 0
        min: 0
        max: 1
      - panel_knob_id: 4
        module_id: 2
        param_id: 2
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
        module_id: 3
        param_id: 0
        curve_type: 0
        min: 0
        max: 1
      - panel_knob_id: 7
        module_id: 3
        param_id: 2
        curve_type: 0
        min: 0
        max: 1
      - panel_knob_id: 9
        module_id: 3
        param_id: 1
        curve_type: 0
        min: 0
        max: 1
      - panel_knob_id: 10
        module_id: 3
        param_id: 3
        curve_type: 0
        min: 0
        max: 1
      - panel_knob_id: 8
        module_id: 1
        param_id: 10
        curve_type: 0
        min: 0
        max: 1
      - panel_knob_id: 11
        module_id: 1
        param_id: 11
        curve_type: 0
        min: 0
        max: 1

)";
