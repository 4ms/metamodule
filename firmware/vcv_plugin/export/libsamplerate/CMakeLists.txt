add_library(
  libsamplerate STATIC
  libsamplerate-0.1.9/src/samplerate.c
  libsamplerate-0.1.9/src/src_linear.c
  libsamplerate-0.1.9/src/src_sinc.c
  libsamplerate-0.1.9/src/src_zoh.c
)

target_include_directories(libsamplerate PUBLIC libsamplerate/src )
