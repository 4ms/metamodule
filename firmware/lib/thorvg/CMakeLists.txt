project(ThorVG CXX)

add_library(ThorVG STATIC)

target_compile_features(ThorVG PRIVATE cxx_std_14)

target_include_directories(ThorVG PUBLIC 
    ./ 
    thorvg/inc
    thorvg/src/common
    thorvg/src/renderer
    thorvg/src/renderer/sw_engine
	thorvg/src/loaders/raw
)

target_include_directories(ThorVG PRIVATE thorvg/src)

target_sources(ThorVG PRIVATE 
   thorvg/src/common/tvgCompressor.cpp
   thorvg/src/common/tvgMath.cpp
   thorvg/src/common/tvgStr.cpp

   thorvg/src/renderer/tvgAccessor.cpp
   thorvg/src/renderer/tvgAnimation.cpp
   thorvg/src/renderer/tvgCanvas.cpp
   thorvg/src/renderer/tvgFill.cpp
   # thorvg/src/renderer/tvgGlCanvas.cpp
   thorvg/src/renderer/tvgInitializer.cpp
   thorvg/src/renderer/tvgLoader.cpp
   thorvg/src/renderer/tvgPaint.cpp
   thorvg/src/renderer/tvgPicture.cpp
   thorvg/src/renderer/tvgRender.cpp
   thorvg/src/renderer/tvgSaver.cpp
   thorvg/src/renderer/tvgScene.cpp
   thorvg/src/renderer/tvgShape.cpp
   thorvg/src/renderer/tvgSwCanvas.cpp
   thorvg/src/renderer/tvgTaskScheduler.cpp
   thorvg/src/renderer/tvgText.cpp
   thorvg/src/renderer/tvgTrimPath.cpp
   # thorvg/src/renderer/tvgWgCanvas.cpp

   thorvg/src/renderer/sw_engine/tvgSwFill.cpp
   thorvg/src/renderer/sw_engine/tvgSwImage.cpp
   thorvg/src/renderer/sw_engine/tvgSwMath.cpp
   thorvg/src/renderer/sw_engine/tvgSwMemPool.cpp
   thorvg/src/renderer/sw_engine/tvgSwPostEffect.cpp
   thorvg/src/renderer/sw_engine/tvgSwRenderer.h
   thorvg/src/renderer/sw_engine/tvgSwRaster.cpp
   thorvg/src/renderer/sw_engine/tvgSwRenderer.cpp
   thorvg/src/renderer/sw_engine/tvgSwRle.cpp
   thorvg/src/renderer/sw_engine/tvgSwShape.cpp
   thorvg/src/renderer/sw_engine/tvgSwStroke.cpp

   thorvg/src/loaders/raw/tvgRawLoader.cpp
)

# SVG loader: used to draw module faceplates from SVG files on platforms with a screen
# dense enough to need it (see src/gui/elements/svg_faceplate.hh)
if(METAMODULE_PLATFORM STREQUAL "mp2")
  set(THORVG_SVG_SOURCES
     thorvg/src/loaders/svg/tvgSvgCssStyle.cpp
     thorvg/src/loaders/svg/tvgSvgLoader.cpp
     thorvg/src/loaders/svg/tvgSvgPath.cpp
     thorvg/src/loaders/svg/tvgSvgSceneBuilder.cpp
     thorvg/src/loaders/svg/tvgSvgUtil.cpp
     thorvg/src/loaders/svg/tvgXmlParser.cpp
  )
  target_sources(ThorVG PRIVATE ${THORVG_SVG_SOURCES})
  # The loader calls tvg's identity() unqualified, with `using namespace std`: that's ambiguous
  # with std::identity in C++20 and later (gcc). ThorVG is written for C++14.
  set_source_files_properties(${THORVG_SVG_SOURCES} PROPERTIES COMPILE_OPTIONS "-std=gnu++17")
  target_include_directories(ThorVG PRIVATE thorvg/src/loaders/svg)
  target_compile_definitions(ThorVG PUBLIC THORVG_SVG_LOADER_SUPPORT=1)
endif()

target_compile_options(ThorVG PRIVATE 
	-Wno-unknown-pragmas
)

target_compile_definitions(ThorVG PUBLIC 
	TVG_STATIC=1
)
