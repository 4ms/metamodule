project(lvgl_simulation_driver LANGUAGES C CXX)

find_package(PkgConfig)
pkg_check_modules(SDL2 REQUIRED sdl2)

set(LV_CONF_PATH
    ${SIM_ROOT}/lv_conf.h
    CACHE STRING "" FORCE)

add_library(lvglsdl ${PROJECT_SOURCE_DIR}/lv_sdl_disp.c
                    ${PROJECT_SOURCE_DIR}/lv_port_indev.c)

target_compile_definitions(lvglsdl PRIVATE -DLV_LVGL_H_INCLUDE_SIMPLE
                                           -DLV_CONF_PATH=${LV_CONF_PATH})

target_compile_options(lvglsdl PRIVATE -Wall -O2)

# macOS m1 doesn't always find SDL:
if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm64")
  target_compile_options(lvglsdl PUBLIC -I /opt/homebrew/include)
  target_link_options(lvglsdl PUBLIC -L /opt/homebrew/lib)
endif()

target_include_directories(
  lvglsdl
  PRIVATE ${SDL2_INCLUDE_DIRS}
  PUBLIC ${PROJECT_SOURCE_DIR} ${LVGL_DIR} ${LVGL_DIR}/lvgl)
