project(lvgl_simulation_driver LANGUAGES C CXX)

find_package(SDL2 REQUIRED)

add_library(lvglsdl lv_sdl_disp.c lv_port_indev_encoder.cc)

target_compile_definitions(
  lvglsdl PRIVATE -DLV_CONF_INCLUDE_SIMPLE -DLV_LVGL_H_INCLUDE_SIMPLE
                  -DLV_CONF_PATH=${LV_CONF_PATH})

message("lvgl_drv: LV_CONF_PATH =${LV_CONF_PATH}")
message("lvgl_drv: LV_CONF_DIR =${LV_CONF_DIR}")

target_compile_options(lvglsdl PRIVATE -Wall -O2)

set_property(TARGET lvglsdl PROPERTY CXX_STANDARD 20)

# Fixup for compiler warning in lvgl header file included from here
set_source_files_properties(
  lv_port_indev_encoder.cc
  PROPERTIES COMPILE_OPTIONS "-Wno-deprecated-anon-enum-enum-conversion")

if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm64")
  # possible macOS m1 homebrew SDL location
  target_include_directories(lvglsdl PUBLIC /opt/homebrew/include)
  target_link_options(lvglsdl PUBLIC -L /opt/homebrew/lib)
elseif(WIN32)
  target_link_libraries(
    lvglsdl
    PRIVATE $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
            $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>)
else()
  target_include_directories(lvglsdl PUBLIC /usr/local/include)
  target_link_options(lvglsdl PUBLIC -L /usr/local/lib)
endif()

message(SDL2_INCLUDE_DIRS=${SDL2_INCLUDE_DIRS})

target_include_directories(
  lvglsdl
  PRIVATE ${SDL2_INCLUDE_DIRS}
  PUBLIC ${PROJECT_SOURCE_DIR} ${LV_CONF_DIR} ${LVGL_DIR})
