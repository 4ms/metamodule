project(PfFFT)

add_library(pffft)

target_sources(pffft PRIVATE
    pffft.h
    pffft.c
    fftpack.h
    fftpack.c
    )

# Fixup for pffft compiler warnings
set_source_files_properties(pffft.c PROPERTIES COMPILE_OPTIONS "-Wno-double-promotion;-Wno-pointer-to-int-cast")

target_include_directories(pffft PUBLIC .)