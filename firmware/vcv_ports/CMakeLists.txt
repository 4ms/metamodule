cmake_minimum_required(VERSION 3.24)
project(vcv_ports)

include(${CMAKE_CURRENT_LIST_DIR}/brands.cmake)


# Create library that combines all brands
# Link against this library from outside
add_library(_vcv_ports_internal STATIC)
target_sources(_vcv_ports_internal PRIVATE ${CMAKE_CURRENT_LIST_DIR}/glue/empty.cc)

if (CMAKE_CROSSCOMPILING)
  # Enable LTO for top level library
  set_property(TARGET _vcv_ports_internal PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

set_property(TARGET _vcv_ports_internal PROPERTY CXX_STANDARD 20)

# Create interface wrapper that whole-links the actual library
add_library(vcv_ports INTERFACE)
target_link_libraries(vcv_ports INTERFACE "$<LINK_LIBRARY:WHOLE_ARCHIVE,_vcv_ports_internal>")

# Common paths
set(IMAGES_BASEDIR ${FWDIR}/src/gui/images)

foreach(brand ${brands})

  #
  ## Component artwork
  #

  # Search for all component c files
  file(GLOB BRAND_ARTWORK_SOURCES ${IMAGES_BASEDIR}/${brand}/components/*.c)
  list(APPEND COMP_ARTWORK_SOURCES ${BRAND_ARTWORK_SOURCES})

  foreach(component ${BRAND_ARTWORK_SOURCES})
    cmake_path(GET component STEM LAST_ONLY COMPIMGNAME)
    set(_this_component_image_file ${CMAKE_CURRENT_BINARY_DIR}/${brand}/${COMPIMGNAME}_register.cc)

    # generate image file for component
    if(${brand} STREQUAL "Rack")
      set(COMPFILENAME "sys/res/ComponentLibrary/${COMPIMGNAME}.png")
    else()
      set(COMPFILENAME "res/components/${COMPIMGNAME}.png")
    endif()
    configure_file(${IMAGES_BASEDIR}/component_register.cc.in ${_this_component_image_file})
    list(APPEND COMP_ARTWORK_SOURCES ${_this_component_image_file})

    # Fixup for compiler warning on files that include LVGL 8.3 headers:
    set_source_files_properties(${_this_component_image_file}
      PROPERTIES COMPILE_OPTIONS "-Wno-deprecated-enum-enum-conversion;-Wno-deprecated-anon-enum-enum-conversion;")
  endforeach()

  # Faceplate artwork
  # Use provided module list file.
  include(${CMAKE_CURRENT_LIST_DIR}/glue/${brand}/modules.cmake)
  
  foreach(module IN LISTS ${brand}Modules)
    if(brand EQUAL "4ms")
      set(IMGNAME "${module}_artwork")
    else()
      set(IMGNAME ${module})
    endif()

    set(_this_module_faceplate_image ${IMAGES_BASEDIR}/${brand}/modules/${IMGNAME}_240.c)
    if(EXISTS "${_this_module_faceplate_image}")
      list(APPEND FACEPLATE_ARTWORK_SOURCES ${_this_module_faceplate_image})

      set(_this_module_image_file ${CMAKE_CURRENT_BINARY_DIR}/${brand}/${module}_register.cc)

      # Generate a .cc file that will register the map from slug to lvgl image
      # data
      cleanup_imgname(${IMGNAME})
      configure_file(${IMAGES_BASEDIR}/faceplate_register.cc.in ${_this_module_image_file})

      list(APPEND FACEPLATE_ARTWORK_SOURCES ${_this_module_image_file})

      # Fixup for compiler warning on files that include LVGL 8.3 headers:
      set_source_files_properties(${_this_module_image_file}
          PROPERTIES COMPILE_OPTIONS "-Wno-deprecated-enum-enum-conversion;-Wno-deprecated-anon-enum-enum-conversion;")
    else()
      message("Image file not found for ${_this_module_faceplate_image}") 
    endif()
  endforeach()

  # brand cmake library
  add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/glue/${brand})

  target_compile_options(${brand}Library PRIVATE -Wno-attributes $<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-enum-enum-conversion>)
  target_sources(${brand}Library PRIVATE ${CMAKE_CURRENT_LIST_DIR}/glue/empty.cc)
  target_link_libraries(${brand}Library PUBLIC VCV_adaptor)

  if (CMAKE_CROSSCOMPILING)
    # Enable LTO for all brands
    set_property(TARGET ${brand}Library PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
  endif()

  target_link_libraries(_vcv_ports_internal PUBLIC ${brand}Library)

endforeach()

target_link_libraries(_vcv_ports_internal PRIVATE lvgl)

# add all image source files as public sources
# TODO: Can we already compile them here? (lvgl dependency)
target_sources(_vcv_ports_internal PRIVATE  ${COMP_ARTWORK_SOURCES})
target_sources(_vcv_ports_internal PRIVATE  ${FACEPLATE_ARTWORK_SOURCES})
