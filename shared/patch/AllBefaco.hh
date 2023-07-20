static char AllBefaco_patch[] =
	R"(
PatchData:
  patch_name: AllBefaco
  description: Patch Description
  module_slugs:
    0: HubMedium
    1: Morphader
    2: PonyVCO
    3: EvenVCO
    4: Rampage
    5: ABC
    6: SpringReverb
    7: Mixer
    8: SlewLimiter
    9: DualAtenuverter
    10: Percall
    11: HexmixVCA
    12: ChoppingKinky
    13: Kickall
    14: SamplingModulator
    15: ADSR
    16: STMix
    17: MotionMTR
    18: StereoStrip
  int_cables: []
  mapped_ins: []
  mapped_outs: []
  static_knobs:
    - module_id: 1
      param_id: 0
      value: 1
    - module_id: 1
      param_id: 1
      value: 0.5
    - module_id: 1
      param_id: 2
      value: 0
    - module_id: 1
      param_id: 3
      value: 0
    - module_id: 1
      param_id: 4
      value: 0
    - module_id: 1
      param_id: 5
      value: 0.5
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
      value: 1
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
      value: 7.505
    - module_id: 1
      param_id: 14
      value: -0.277108
    - module_id: 2
      param_id: 0
      value: 0
    - module_id: 2
      param_id: 1
      value: 0
    - module_id: 2
      param_id: 2
      value: 0
    - module_id: 2
      param_id: 3
      value: 6
    - module_id: 2
      param_id: 4
      value: 0
    - module_id: 3
      param_id: 0
      value: 0
    - module_id: 3
      param_id: 1
      value: 0
    - module_id: 3
      param_id: 2
      value: 0
    - module_id: 4
      param_id: 0
      value: 0
    - module_id: 4
      param_id: 1
      value: 0
    - module_id: 4
      param_id: 2
      value: 0
    - module_id: 4
      param_id: 3
      value: 0
    - module_id: 4
      param_id: 4
      value: 0
    - module_id: 4
      param_id: 5
      value: 0
    - module_id: 4
      param_id: 6
      value: 0
    - module_id: 4
      param_id: 7
      value: 0
    - module_id: 4
      param_id: 8
      value: 0
    - module_id: 4
      param_id: 9
      value: 0
    - module_id: 4
      param_id: 10
      value: 0
    - module_id: 4
      param_id: 11
      value: 0
    - module_id: 4
      param_id: 12
      value: 0.5
    - module_id: 5
      param_id: 0
      value: 0
    - module_id: 5
      param_id: 1
      value: 0
    - module_id: 5
      param_id: 2
      value: 0
    - module_id: 5
      param_id: 3
      value: 0
    - module_id: 6
      param_id: 0
      value: 0.5
    - module_id: 6
      param_id: 1
      value: 0
    - module_id: 6
      param_id: 2
      value: 0
    - module_id: 6
      param_id: 3
      value: 0.5
    - module_id: 7
      param_id: 0
      value: 0
    - module_id: 7
      param_id: 1
      value: 0
    - module_id: 7
      param_id: 2
      value: 0
    - module_id: 7
      param_id: 3
      value: 0
    - module_id: 8
      param_id: 0
      value: 0
    - module_id: 8
      param_id: 1
      value: 0
    - module_id: 8
      param_id: 2
      value: 0
    - module_id: 9
      param_id: 0
      value: 0
    - module_id: 9
      param_id: 1
      value: 0
    - module_id: 9
      param_id: 2
      value: 0
    - module_id: 9
      param_id: 3
      value: 0
    - module_id: 10
      param_id: 0
      value: 1
    - module_id: 10
      param_id: 1
      value: 1
    - module_id: 10
      param_id: 2
      value: 1
    - module_id: 10
      param_id: 3
      value: 1
    - module_id: 10
      param_id: 4
      value: 0
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
      value: 0
    - module_id: 10
      param_id: 9
      value: 0
    - module_id: 11
      param_id: 0
      value: 0
    - module_id: 11
      param_id: 1
      value: 0
    - module_id: 11
      param_id: 2
      value: 0
    - module_id: 11
      param_id: 3
      value: 0
    - module_id: 11
      param_id: 4
      value: 0
    - module_id: 11
      param_id: 5
      value: 0
    - module_id: 11
      param_id: 6
      value: 1
    - module_id: 11
      param_id: 7
      value: 1
    - module_id: 11
      param_id: 8
      value: 1
    - module_id: 11
      param_id: 9
      value: 1
    - module_id: 11
      param_id: 10
      value: 1
    - module_id: 11
      param_id: 11
      value: 1
    - module_id: 12
      param_id: 0
      value: 0
    - module_id: 12
      param_id: 1
      value: 0
    - module_id: 12
      param_id: 2
      value: 0
    - module_id: 12
      param_id: 3
      value: 0
    - module_id: 13
      param_id: 0
      value: 75.4855
    - module_id: 13
      param_id: 1
      value: 0
    - module_id: 13
      param_id: 2
      value: 0
    - module_id: 13
      param_id: 3
      value: 0.01
    - module_id: 13
      param_id: 4
      value: 0
    - module_id: 13
      param_id: 5
      value: 0
    - module_id: 14
      param_id: 0
      value: 0
    - module_id: 14
      param_id: 1
      value: 0
    - module_id: 14
      param_id: 2
      value: 1
    - module_id: 14
      param_id: 3
      value: 2
    - module_id: 14
      param_id: 4
      value: 2
    - module_id: 14
      param_id: 5
      value: 2
    - module_id: 14
      param_id: 6
      value: 2
    - module_id: 14
      param_id: 7
      value: 2
    - module_id: 14
      param_id: 8
      value: 2
    - module_id: 14
      param_id: 9
      value: 2
    - module_id: 14
      param_id: 10
      value: 2
    - module_id: 15
      param_id: 0
      value: 0
    - module_id: 15
      param_id: 1
      value: 0
    - module_id: 15
      param_id: 2
      value: 0
    - module_id: 15
      param_id: 3
      value: 0
    - module_id: 15
      param_id: 4
      value: 0
    - module_id: 15
      param_id: 5
      value: 0
    - module_id: 15
      param_id: 6
      value: 0
    - module_id: 16
      param_id: 0
      value: 0
    - module_id: 16
      param_id: 1
      value: 0
    - module_id: 16
      param_id: 2
      value: 0
    - module_id: 16
      param_id: 3
      value: 0
    - module_id: 17
      param_id: 0
      value: 1
    - module_id: 17
      param_id: 1
      value: 0.0638554
    - module_id: 17
      param_id: 2
      value: 1
    - module_id: 17
      param_id: 3
      value: 0
    - module_id: 17
      param_id: 4
      value: 1
    - module_id: 17
      param_id: 5
      value: 0.23253
    - module_id: 18
      param_id: 0
      value: 0
    - module_id: 18
      param_id: 1
      value: 0
    - module_id: 18
      param_id: 2
      value: 0
    - module_id: 18
      param_id: 3
      value: 0
    - module_id: 18
      param_id: 4
      value: 1
    - module_id: 18
      param_id: 5
      value: 0
    - module_id: 18
      param_id: 6
      value: -60
    - module_id: 18
      param_id: 7
      value: 0
    - module_id: 18
      param_id: 8
      value: 0
  mapped_knobs:
    - panel_knob_id: 0
      module_id: 1
      param_id: 14
      curve_type: 0
      min: 0
      max: 1
    - panel_knob_id: 1
      module_id: 1
      param_id: 1
      curve_type: 0
      min: 0
      max: 1
    - panel_knob_id: 2
      module_id: 1
      param_id: 5
      curve_type: 0
      min: 0
      max: 1
    - panel_knob_id: 3
      module_id: 1
      param_id: 9
      curve_type: 0
      min: 0
      max: 1
    - panel_knob_id: 4
      module_id: 1
      param_id: 13
      curve_type: 0
      min: 0
      max: 1

)";
