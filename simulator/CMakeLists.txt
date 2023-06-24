cmake_minimum_required(VERSION 3.14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(mm_sim LANGUAGES C CXX)

find_package(PkgConfig)
pkg_check_modules(SDL2 REQUIRED sdl2)

set(LVDRV_DIR "${PROJECT_SOURCE_DIR}/lvgl_drv")
set(LVGL_DIR "${PROJECT_SOURCE_DIR}/../firmware/lib/lvgl")
set(LV_CONF_PATH
    ${PROJECT_SOURCE_DIR}/lv_conf.h
    CACHE STRING "" FORCE)

# TODO: create lvgl_drv/CMakeLists.txt:
add_library(lvglsdl ${LVDRV_DIR}/lv_sdl_disp.c ${LVDRV_DIR}/lv_port_indev.c)

target_compile_definitions(lvglsdl PRIVATE -DLV_LVGL_H_INCLUDE_SIMPLE)
target_compile_definitions(lvglsdl PRIVATE -DLV_CONF_PATH=${LV_CONF_PATH})
target_compile_options(lvglsdl PUBLIC -I /opt/homebrew/include -arch arm64
                                      -Wall -O2)
target_link_options(lvglsdl PUBLIC -L /opt/homebrew/lib)
target_include_directories(lvglsdl PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(lvglsdl PRIVATE ${LVGL_DIR})
target_include_directories(lvglsdl PRIVATE ${LVGL_DIR}/lvgl)
# ##############################################################################

add_executable(simulator src/main.cc)
target_compile_options(simulator PRIVATE -Wall -O2)

set(MM_ROOT ${PROJECT_SOURCE_DIR}/..)
target_include_directories(
  simulator
  PRIVATE ${LVGL_DIR}
          ${LVGL_DIR}/lvgl
          ${LVDRV_DIR}
          ${SDL2_INCLUDE_DIRS}
          src
          ${MM_ROOT}/firmware/src
          ${MM_ROOT}/firmware/src/medium
          ${MM_ROOT}/shared
          ${MM_ROOT}/shared/cpputil)

target_compile_options(simulator PRIVATE $<$<COMPILE_LANGUAGE:CXX>: -std=c++20>
                                         ${SDL2_CFLAGS_OTHER})

target_compile_definitions(simulator PRIVATE SIMULATOR)
target_link_libraries(simulator PRIVATE ${SDL2_LIBRARIES} lvglsdl lvgl::lvgl
                                        SDL2)

include(${LVGL_DIR}/lvgl/CMakeLists.txt)
