// Automatically generated, do not edit
static const char patch_Wooden_Groove[] =
	R"(
PatchData:
  patch_name: Wooden Groove
  description: "Orca's Heart sequencer driving 4 macro oscillators in Drum mode. All 4 drums running into DLD. "
  module_slugs:
    0: '4msCompany:HubMedium'
    1: 'eightfold:SDOrcasHeartV2'
    2: 'AudibleInstruments:Braids'
    3: 'AudibleInstruments:Braids'
    4: '4msCompany:StMix'
    5: '4msCompany:StMix'
    6: 'AudibleInstruments:Braids'
    7: 'AudibleInstruments:Braids'
    8: '4msCompany:DLD'
    9: 'Valley:Plateau'
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 8
          jack_id: 0
      color: 13501
    - out:
        module_id: 4
        jack_id: 0
      ins:
        - module_id: 8
          jack_id: 1
      color: 13501
    - out:
        module_id: 4
        jack_id: 1
      ins:
        - module_id: 8
          jack_id: 6
      color: 35419
    - out:
        module_id: 2
        jack_id: 0
      ins:
        - module_id: 4
          jack_id: 0
      color: 13501
    - out:
        module_id: 3
        jack_id: 0
      ins:
        - module_id: 4
          jack_id: 2
      color: 35419
    - out:
        module_id: 6
        jack_id: 0
      ins:
        - module_id: 4
          jack_id: 4
      color: 61865
    - out:
        module_id: 7
        jack_id: 0
      ins:
        - module_id: 4
          jack_id: 6
      color: 64934
    - out:
        module_id: 1
        jack_id: 10
      ins:
        - module_id: 2
          jack_id: 0
      color: 61865
    - out:
        module_id: 1
        jack_id: 2
      ins:
        - module_id: 2
          jack_id: 1
      color: 35419
    - out:
        module_id: 1
        jack_id: 11
      ins:
        - module_id: 3
          jack_id: 0
      color: 64934
    - out:
        module_id: 1
        jack_id: 3
      ins:
        - module_id: 3
          jack_id: 1
      color: 61865
    - out:
        module_id: 1
        jack_id: 13
      ins:
        - module_id: 7
          jack_id: 0
      color: 13501
    - out:
        module_id: 1
        jack_id: 12
      ins:
        - module_id: 6
          jack_id: 0
      color: 1453
    - out:
        module_id: 1
        jack_id: 4
      ins:
        - module_id: 6
          jack_id: 1
      color: 64934
    - out:
        module_id: 1
        jack_id: 5
      ins:
        - module_id: 7
          jack_id: 1
      color: 1453
    - out:
        module_id: 8
        jack_id: 3
      ins:
        - module_id: 5
          jack_id: 0
      color: 64934
    - out:
        module_id: 8
        jack_id: 6
      ins:
        - module_id: 5
          jack_id: 2
      color: 1453
    - out:
        module_id: 5
        jack_id: 0
      ins:
        - module_id: 9
          jack_id: 0
      color: 1453
    - out:
        module_id: 5
        jack_id: 1
      ins:
        - module_id: 9
          jack_id: 1
      color: 13501
  mapped_ins: []
  mapped_outs:
    - panel_jack_id: 0
      out:
        module_id: 9
        jack_id: 0
    - panel_jack_id: 1
      out:
        module_id: 9
        jack_id: 1
  static_knobs:
    - module_id: 2
      param_id: 0
      value: 0.5
    - module_id: 2
      param_id: 1
      value: 0.5
    - module_id: 2
      param_id: 2
      value: 0.5
    - module_id: 2
      param_id: 3
      value: 0.242168
    - module_id: 2
      param_id: 4
      value: 0.5
    - module_id: 2
      param_id: 5
      value: 0.5
    - module_id: 2
      param_id: 6
      value: 0.725301
    - module_id: 3
      param_id: 0
      value: 0.5
    - module_id: 3
      param_id: 1
      value: 0.5
    - module_id: 3
      param_id: 2
      value: 0.5
    - module_id: 3
      param_id: 3
      value: 0.303614
    - module_id: 3
      param_id: 4
      value: 0.5
    - module_id: 3
      param_id: 5
      value: 0.5
    - module_id: 3
      param_id: 6
      value: 0.713253
    - module_id: 7
      param_id: 0
      value: 0.5
    - module_id: 7
      param_id: 1
      value: 0.375
    - module_id: 7
      param_id: 2
      value: 0.5
    - module_id: 7
      param_id: 3
      value: 0.309639
    - module_id: 7
      param_id: 4
      value: 0.5
    - module_id: 7
      param_id: 5
      value: 0.5
    - module_id: 7
      param_id: 6
      value: 0.718073
    - module_id: 6
      param_id: 0
      value: 0.5
    - module_id: 6
      param_id: 1
      value: 0.375
    - module_id: 6
      param_id: 2
      value: 0.5
    - module_id: 6
      param_id: 3
      value: 0.328916
    - module_id: 6
      param_id: 4
      value: 0.5
    - module_id: 6
      param_id: 5
      value: 0.259036
    - module_id: 6
      param_id: 6
      value: 0.714458
    - module_id: 4
      param_id: 0
      value: 1
    - module_id: 4
      param_id: 1
      value: 1
    - module_id: 4
      param_id: 2
      value: 1
    - module_id: 4
      param_id: 3
      value: 1
    - module_id: 4
      param_id: 4
      value: 0.318072
    - module_id: 4
      param_id: 5
      value: 0.653012
    - module_id: 4
      param_id: 6
      value: 0.0903614
    - module_id: 4
      param_id: 7
      value: 0.949397
    - module_id: 8
      param_id: 0
      value: 0.489156
    - module_id: 8
      param_id: 1
      value: 0.5
    - module_id: 8
      param_id: 2
      value: 0
    - module_id: 8
      param_id: 3
      value: 0.5
    - module_id: 8
      param_id: 4
      value: 0.777108
    - module_id: 8
      param_id: 5
      value: 0.444578
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
      value: 0.444578
    - module_id: 8
      param_id: 11
      value: 0.761446
    - module_id: 8
      param_id: 12
      value: 0.383133
    - module_id: 8
      param_id: 13
      value: 0.383133
    - module_id: 8
      param_id: 14
      value: 0.845783
    - module_id: 8
      param_id: 15
      value: 0
    - module_id: 8
      param_id: 16
      value: 0
    - module_id: 8
      param_id: 17
      value: 0
    - module_id: 8
      param_id: 18
      value: 0
    - module_id: 8
      param_id: 19
      value: 0
    - module_id: 8
      param_id: 20
      value: 0
    - module_id: 8
      param_id: 21
      value: 0
    - module_id: 8
      param_id: 22
      value: 0
    - module_id: 8
      param_id: 23
      value: 0
    - module_id: 8
      param_id: 24
      value: 0
    - module_id: 8
      param_id: 25
      value: 0
    - module_id: 8
      param_id: 26
      value: 0
    - module_id: 8
      param_id: 27
      value: 0
    - module_id: 8
      param_id: 28
      value: 0
    - module_id: 8
      param_id: 29
      value: 0
    - module_id: 8
      param_id: 30
      value: 0.5
    - module_id: 8
      param_id: 31
      value: 0.5
    - module_id: 1
      param_id: 0
      value: 0
    - module_id: 1
      param_id: 1
      value: 0
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
      value: 0
    - module_id: 1
      param_id: 6
      value: 0
    - module_id: 1
      param_id: 7
      value: 0.551807
    - module_id: 1
      param_id: 8
      value: 0.698413
    - module_id: 1
      param_id: 9
      value: 0.5
    - module_id: 1
      param_id: 10
      value: 0.252104
    - module_id: 1
      param_id: 11
      value: 0.428571
    - module_id: 1
      param_id: 12
      value: 0
    - module_id: 1
      param_id: 13
      value: 0
    - module_id: 1
      param_id: 14
      value: 0.307087
    - module_id: 1
      param_id: 15
      value: 0.5
    - module_id: 1
      param_id: 16
      value: 0.3125
    - module_id: 1
      param_id: 17
      value: 0.3125
    - module_id: 1
      param_id: 18
      value: 0
    - module_id: 1
      param_id: 19
      value: 1
    - module_id: 1
      param_id: 20
      value: 0
    - module_id: 1
      param_id: 21
      value: 1
    - module_id: 1
      param_id: 22
      value: 0
    - module_id: 1
      param_id: 23
      value: 1
    - module_id: 1
      param_id: 24
      value: 1
    - module_id: 1
      param_id: 25
      value: 0
    - module_id: 1
      param_id: 26
      value: 1
    - module_id: 1
      param_id: 27
      value: 0
    - module_id: 1
      param_id: 28
      value: 0
    - module_id: 1
      param_id: 29
      value: 0
    - module_id: 1
      param_id: 30
      value: 0
    - module_id: 1
      param_id: 31
      value: 1
    - module_id: 1
      param_id: 32
      value: 0
    - module_id: 1
      param_id: 33
      value: 1
    - module_id: 1
      param_id: 34
      value: 0
    - module_id: 1
      param_id: 35
      value: 1
    - module_id: 1
      param_id: 36
      value: 0
    - module_id: 1
      param_id: 37
      value: 0
    - module_id: 1
      param_id: 38
      value: 1
    - module_id: 1
      param_id: 39
      value: 0
    - module_id: 1
      param_id: 40
      value: 1
    - module_id: 1
      param_id: 41
      value: 0
    - module_id: 1
      param_id: 42
      value: 0
    - module_id: 5
      param_id: 0
      value: 1
    - module_id: 5
      param_id: 1
      value: 1
    - module_id: 5
      param_id: 2
      value: 0.875
    - module_id: 5
      param_id: 3
      value: 0.875
    - module_id: 5
      param_id: 4
      value: 0.210241
    - module_id: 5
      param_id: 5
      value: 0.789759
    - module_id: 5
      param_id: 6
      value: 0.5
    - module_id: 5
      param_id: 7
      value: 0.5
    - module_id: 9
      param_id: 0
      value: 0.38773
    - module_id: 9
      param_id: 1
      value: 0.0455785
    - module_id: 9
      param_id: 2
      value: 0
    - module_id: 9
      param_id: 3
      value: 1
    - module_id: 9
      param_id: 4
      value: 1
    - module_id: 9
      param_id: 5
      value: 0.386747
    - module_id: 9
      param_id: 6
      value: 1
    - module_id: 9
      param_id: 7
      value: 0.379518
    - module_id: 9
      param_id: 8
      value: 0.26988
    - module_id: 9
      param_id: 9
      value: 1
    - module_id: 9
      param_id: 10
      value: 0
    - module_id: 9
      param_id: 11
      value: 0.5
    - module_id: 9
      param_id: 12
      value: 0.03125
    - module_id: 9
      param_id: 13
      value: 0
    - module_id: 9
      param_id: 14
      value: 0
    - module_id: 9
      param_id: 15
      value: 0
    - module_id: 9
      param_id: 16
      value: 0
    - module_id: 9
      param_id: 17
      value: 0.5
    - module_id: 9
      param_id: 18
      value: 0.5
    - module_id: 9
      param_id: 19
      value: 0.5
    - module_id: 9
      param_id: 20
      value: 0.5
    - module_id: 9
      param_id: 21
      value: 0.5
    - module_id: 9
      param_id: 22
      value: 0.5
    - module_id: 9
      param_id: 23
      value: 0.5
    - module_id: 9
      param_id: 24
      value: 0.5
    - module_id: 9
      param_id: 25
      value: 0.5
    - module_id: 9
      param_id: 26
      value: 0.5
    - module_id: 9
      param_id: 27
      value: 0.5
    - module_id: 9
      param_id: 28
      value: 0.5
    - module_id: 9
      param_id: 29
      value: 0
    - module_id: 9
      param_id: 30
      value: 1
  mapped_knobs:
    - name: Sequencing
      set:
        - panel_knob_id: 0
          module_id: 1
          param_id: 13
          curve_type: 0
          min: 0
          max: 1
          alias_name: Algo X
        - panel_knob_id: 1
          module_id: 1
          param_id: 14
          curve_type: 0
          min: 0
          max: 1
          alias_name: Algo Y
        - panel_knob_id: 2
          module_id: 1
          param_id: 8
          curve_type: 0
          min: 0
          max: 1
          alias_name: Seq Length
        - panel_knob_id: 3
          module_id: 1
          param_id: 16
          curve_type: 0
          min: 0
          max: 1
          alias_name: Space
        - panel_knob_id: 4
          module_id: 1
          param_id: 17
          curve_type: 0
          min: 0
          max: 1
          alias_name: Rotate
        - panel_knob_id: 5
          module_id: 1
          param_id: 15
          curve_type: 0
          min: 0
          max: 1
          alias_name: Root Note
        - panel_knob_id: 6
          module_id: 8
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
          alias_name: DLD Time A
        - panel_knob_id: 7
          module_id: 8
          param_id: 4
          curve_type: 0
          min: 0
          max: 1
          alias_name: DLD Time B
        - panel_knob_id: 8
          module_id: 8
          param_id: 5
          curve_type: 0
          min: 0
          max: 1
          alias_name: DLD Feedback
        - panel_knob_id: 8
          module_id: 8
          param_id: 10
          curve_type: 0
          min: 0
          max: 1
          alias_name: DLD Feedback
        - panel_knob_id: 9
          module_id: 8
          param_id: 13
          curve_type: 0
          min: 0
          max: 1
          alias_name: DLD Dry/Wet
        - panel_knob_id: 9
          module_id: 8
          param_id: 12
          curve_type: 0
          min: 0
          max: 1
          alias_name: DLD Dry/Wet
        - panel_knob_id: 10
          module_id: 5
          param_id: 4
          curve_type: 0
          min: 0.5
          max: 0
          alias_name: Stereo Spread
        - panel_knob_id: 10
          module_id: 5
          param_id: 5
          curve_type: 0
          min: 0.5
          max: 1
          alias_name: Stereo Spread
        - panel_knob_id: 11
          module_id: 5
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
          alias_name: Master Volume
        - panel_knob_id: 11
          module_id: 5
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
          alias_name: Master Volume
    - name: Decay + Mixing
      set:
        - panel_knob_id: 0
          module_id: 2
          param_id: 3
          curve_type: 0
          min: 0
          max: 1
          alias_name: Decay 1
        - panel_knob_id: 1
          module_id: 3
          param_id: 3
          curve_type: 0
          min: 0
          max: 1
          alias_name: Decay 2
        - panel_knob_id: 2
          module_id: 6
          param_id: 3
          curve_type: 0
          min: 0
          max: 1
          alias_name: Decay 3
        - panel_knob_id: 3
          module_id: 7
          param_id: 3
          curve_type: 0
          min: 0
          max: 1
          alias_name: Decay 4
        - panel_knob_id: 4
          module_id: 9
          param_id: 5
          curve_type: 0
          min: 0
          max: 1
          alias_name: Reverb Size
        - panel_knob_id: 5
          module_id: 9
          param_id: 1
          curve_type: 0
          min: 0
          max: 0.195001
          alias_name: Reverb Dry/Wet
        - panel_knob_id: 5
          module_id: 9
          param_id: 0
          curve_type: 0
          min: 0.506
          max: 0
          alias_name: Reverb Dry/Wet
        - panel_knob_id: 6
          module_id: 4
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
          alias_name: Vol 1
        - panel_knob_id: 7
          module_id: 4
          param_id: 1
          curve_type: 0
          min: 0
          max: 1
          alias_name: Vol 2
        - panel_knob_id: 8
          module_id: 4
          param_id: 2
          curve_type: 0
          min: 0
          max: 1
          alias_name: Vol 3
        - panel_knob_id: 9
          module_id: 4
          param_id: 3
          curve_type: 0
          min: 0
          max: 1
          alias_name: Vol 4
        - panel_knob_id: 10
          module_id: 9
          param_id: 7
          curve_type: 0
          min: 0
          max: 1
          alias_name: Reverb Decay
        - panel_knob_id: 11
          module_id: 9
          param_id: 8
          curve_type: 0
          min: 1
          max: 0
          alias_name: Reverb Damping
    - name: Tranpose
      set:
        - panel_knob_id: 0
          module_id: 1
          param_id: 9
          curve_type: 0
          min: 0
          max: 1
          alias_name: Transpose
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
  mapped_lights: []
  vcvModuleStates:
    - module_id: 2
      data: |-
        {"settings":[33,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],"lowCpu":false}
    - module_id: 3
      data: |-
        {"settings":[33,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],"lowCpu":false}
    - module_id: 7
      data: |-
        {"settings":[33,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],"lowCpu":false}
    - module_id: 6
      data: |-
        {"settings":[33,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],"lowCpu":false}
    - module_id: 8
      data: |-
        aLIm++RG
    - module_id: 1
      data: |-
        {"scaleSwitchMode":0,"selectedScale":0,"globalCounter":26,"totalWeight":38,"counter":[26,26,26,26,26,26,26,26],"divisor":[1,3,2,1,6,5,4,3],"phase":[0,1,0,0,4,0,2,1],"trackOn":[0,1,1,0,1,1,1,1],"weightOn":[0,2,4,0,5,3,11,13],"notes0":[16,14,12,9,37,34,25,16],"notes1":[13,14,14,9,9,7,7,7],"notes2":[6,6,6,9,6,6,6,6],"notes3":[21,22,18,9,23,11,11,15],"notes4":[16,14,12,9,23,23,25,16],"notes5":[15,14,16,9,30,31,22,9],"notes6":[21,6,8,8,30,30,21,8],"notes7":[21,22,18,15,24,22,11,15],"gateOn0":[true,true,true,false,true,true,true,true],"gateOn1":[true,true,true,false,true,true,true,true],"gateOn2":[false,false,false,false,false,false,false,false],"gateOn3":[true,true,true,false,true,true,true,true],"gateOn4":[true,true,true,false,true,true,true,true],"gateOn5":[true,true,true,false,true,true,true,true],"gateOn6":[true,true,true,true,true,true,true,true],"gateOn7":[true,true,true,false,true,true,true,true],"gateChanged0":[true,true,true,false,true,true,true,true],"gateChanged1":[true,true,true,false,true,true,true,true],"gateChanged2":[true,true,true,false,true,true,true,true],"gateChanged3":[true,true,true,false,false,true,true,true],"gateChanged4":[true,true,true,false,true,true,true,true],"gateChanged5":[true,true,true,true,true,true,true,true],"gateChanged6":[false,true,true,true,true,true,true,true],"gateChanged7":[true,true,true,true,true,true,true,true],"gateTimer":[0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0],"gateTriggered":[true,true,true,true,false,false,false,false],"muted":[0,1,0,0,3,0,5,5],"shifts":[6,6,6,6,6,6,6,6],"modCvs":[2.6666667461395264,2.6666667461395264,3.0,8.6666669845581055,7.0,9.3333339691162109,2.0,2.6666667461395264],"modGate":[false,true,true,true,true,true,true,true]}
    - module_id: 9
      data: |-
        {"frozen":false,"freezeToggle":false,"panelStyle":0,"tuned":0,"diffuseInput":1,"preDelayCVSens":0,"inputSensitivity":0,"outputSaturation":0}
)";

