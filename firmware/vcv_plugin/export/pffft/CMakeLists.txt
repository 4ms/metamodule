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

# Disable inline assembly until we ensure alignment
# if(NOT DEFINED SIMULATOR)
# 	target_compile_definitions(pffft PRIVATE ZCONVOLVE_USING_INLINE_ASM=1)
# endif()

target_include_directories(pffft PUBLIC .)
