# TODO: This is only used by makefiles/makefile_component_images.mk
# Delete this once we convert that to CMake


list(APPEND BefacoModules
  EvenVCO
  DualAtenuverter
  SpringReverb
  ABC
  ADSR
  ChoppingKinky
  HexmixVCA
  Kickall
  Mixer
  Morphader
  MotionMTR
  Percall
  PonyVCO
  Rampage
  STMix
  SamplingModulator
  SlewLimiter
  StereoStrip
  # Muxlicer
  # NoisePlethora
)

list(TRANSFORM BefacoModules PREPEND res/panels/ OUTPUT_VARIABLE Befaco_faceplate_svgs)
list(TRANSFORM Befaco_faceplate_svgs APPEND .svg)