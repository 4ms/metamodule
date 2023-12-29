cmake_minimum_required(VERSION 3.14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(mm_sim LANGUAGES C CXX)

set(MM_ROOT ${PROJECT_SOURCE_DIR}/..)
set(FWDIR ${PROJECT_SOURCE_DIR}/../firmware)
set(SHARED ${PROJECT_SOURCE_DIR}/../shared)
set(SIM_ROOT ${PROJECT_SOURCE_DIR})
set(LVGL_DIR ${FWDIR}/lib/lvgl/lvgl)

set(LV_CONF_PATH
    ${SIM_ROOT}/lv_conf.h
    CACHE STRING "" FORCE)

get_filename_component(LV_CONF_DIR ${LV_CONF_PATH} DIRECTORY)

# #################### LVGL Simulator Driver #################################

add_subdirectory(lvgl_drv)

# #################### LVGL ############################################

include(${LVGL_DIR}/CMakeLists.txt)

# #################### SLS Export ##################################

file(STRINGS ${FWDIR}/src/gui/slsexport/meta5/filelist.txt SLS_SOURCES)
list(TRANSFORM SLS_SOURCES PREPEND "${FWDIR}/src/gui/slsexport/meta5/")

# Fixup for compiler warning in LVGL 8.3.4:
set_source_files_properties(${FWDIR}/src/gui/slsexport/meta5/ui.c
                            PROPERTIES COMPILE_FLAGS -Wno-unused-variable)

# #################### VCV Adaptor ##################################

add_subdirectory(${FWDIR}/src/VCV_adaptor
                 ${CMAKE_CURRENT_BINARY_DIR}/VCV_adaptor)
target_sources(VCV_adaptor PRIVATE stubs/random.cpp)
target_include_directories(VCV_adaptor PRIVATE stubs/ ${FWDIR}/src/console)

# #################### Other brands ##################################

# Only build a limited set of modules, defined in an external file
include(${FWDIR}/vcv_ports/glue/filter.cmake)
unset(USE_LIMITED_MODULES)
if(DEFINED LIMITED_MODULES_FILE)
  validate_limited_modules_file(${LIMITED_MODULES_FILE})
endif()

include(${FWDIR}/vcv_ports/brands.cmake)

foreach(brand ${brands})

  # Component artwork
  file(GLOB BRAND_ARTWORK_SOURCES ${FWDIR}/src/gui/images/${brand}/components/*.c)
  list(APPEND COMP_ARTWORK_SOURCES ${BRAND_ARTWORK_SOURCES})
  foreach(component ${BRAND_ARTWORK_SOURCES})
    cmake_path(GET component STEM LAST_ONLY COMPIMGNAME)
    set(COMPFILENAME "${COMPIMGNAME}.png")
    configure_file(${FWDIR}/src/gui/images/component_register.cc.in ${brand}/${COMPIMGNAME}_register.cc)
    list(APPEND COMP_ARTWORK_SOURCES ${brand}/${COMPIMGNAME}_register.cc)

    # Fixup for compiler warning on files that include LVGL 8.3 headers:
    set_source_files_properties(${brand}/${COMPIMGNAME}_register.cc
      PROPERTIES COMPILE_OPTIONS "-Wno-deprecated-enum-enum-conversion;-Wno-deprecated-anon-enum-enum-conversion;")
  endforeach()

  add_subdirectory(${FWDIR}/vcv_ports/glue/${brand} ${CMAKE_CURRENT_BINARY_DIR}/${brand})
  #target_link_libraries(${brand}Library PRIVATE mp15xa7_arch)
  # Module Library
  target_include_directories(
    ${brand}Library
    PUBLIC ${FWDIR}/src/VCV_adaptor
           ${FWDIR}/src/VCV_adaptor/pffft
           ${FWDIR}/lib/jansson
           ${FWDIR}/lib/jansson/jansson/src
           ${FWDIR}/src
           ${FWDIR}
           ${SHARED}
           ${SHARED}/cpputil)
  target_compile_options(${brand}Library PRIVATE -Wno-attributes -Wno-deprecated-enum-enum-conversion)
  target_sources(${brand}Library PRIVATE ${FWDIR}/vcv_ports/glue/empty.cc)

  # Faceplate artwork
  # Use provided module list file.
  include(${FWDIR}/vcv_ports/glue/${brand}/modules.cmake)
  foreach(module IN LISTS ${brand}Modules)
    if(brand EQUAL "4ms")
      set(IMGNAME "${module}_artwork")
    else()
      set(IMGNAME ${module})
    endif()

    set(image_path ${FWDIR}/src/gui/images/${brand}/modules/${IMGNAME}_240.c)
    if(EXISTS "${image_path}")
      cleanup_imgname(${IMGNAME})

      # Generate a .cc file that will register the map from slug to lvgl image
      # data
      configure_file(${FWDIR}/src/gui/images/faceplate_register.cc.in
                     ${brand}/${module}_register.cc)

      list(APPEND FACEPLATE_ARTWORK_SOURCES
           ${CMAKE_CURRENT_BINARY_DIR}/${brand}/${module}_register.cc)
      list(APPEND FACEPLATE_ARTWORK_SOURCES ${image_path})
    endif()
  endforeach()

endforeach()

# #################### RYML + Patch Convert ##################################
set(RYMLDIR ${SHARED}/patch_convert/ryml/rapidyaml)
file(GLOB RYML_SOURCES ${RYMLDIR}/src/c4/yml/*.cpp ${RYMLDIR}/ext/c4core/src/c4/*.cpp)
add_library(ryml OBJECT ${RYML_SOURCES})
target_include_directories(ryml PUBLIC ${RYMLDIR}/src ${RYMLDIR}/ext/c4core/src)
target_compile_options(ryml PRIVATE $<$<COMPILE_LANGUAGE:CXX>: -std=c++20>)

# #################### Application ############################################

add_executable(
	simulator 
	src/main.cc 
	src/ui.cc
	${FWDIR}/src/gui/elements/element_name.cc
	${SHARED}/patch_convert/ryml/ryml_serial.cc
	${SHARED}/patch_convert/yaml_to_patch.cc 
	${SHARED}/patch_convert/patch_to_yaml.cc
	${FACEPLATE_ARTWORK_SOURCES}
	${COMP_ARTWORK_SOURCES} 
	${SLS_SOURCES})

target_include_directories(
  simulator
  PRIVATE src
          stubs
          lvgl_drv
          sdl_audio
          ${SDL2_INCLUDE_DIRS}
          ${SIM_ROOT}
          ${FWDIR}
          ${FWDIR}/src
          ${FWDIR}/src/console
          ${FWDIR}/src/params
          ${FWDIR}/src/medium
          ${SHARED}
          ${SHARED}/cpputil
          ${SHARED}/patch
          ${SHARED}/patch_convert/ryml/rapidyaml/src
          ${SHARED}/CoreModules
          ${SHARED}/CoreModules/4ms)

target_compile_options(simulator PRIVATE -Wall -Og -g2 ${SDL2_CFLAGS_OTHER})

target_link_libraries(simulator PRIVATE ${SDL2_LIBRARIES} lvglsdl ryml SDL2 VCV_adaptor)

foreach(brand ${brands})
  target_link_libraries(simulator PRIVATE ${brand}Library)
endforeach()

set_property(TARGET simulator PROPERTY CXX_STANDARD 20)

# Arch-dependent Link options:
message("CMAKE_CXX_COMPILER_ID = ${CMAKE_CXX_COMPILER_ID}")
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_link_options(simulator PUBLIC "-Wl,-map,simulator.map")
  else()
    target_link_options(simulator PUBLIC LINKER:-Map,simulator.map)
  endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_link_options(simulator PUBLIC LINKER:-Map,simulator.map)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_link_options(simulator PRIVATE "/MAP:simulator.map")
endif()
