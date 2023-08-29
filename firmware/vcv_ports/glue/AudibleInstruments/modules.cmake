# Add modules to be included
list(APPEND AudibleInstrumentsModules
  Braids 
)

list(TRANSFORM AudibleInstrumentsModules PREPEND res/ OUTPUT_VARIABLE AudibleInstruments_faceplate_svgs)
list(TRANSFORM AudibleInstruments_faceplate_svgs APPEND .svg)