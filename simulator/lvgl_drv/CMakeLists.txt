project(lvgl_simulation_driver LANGUAGES C CXX)

find_package(SDL2 REQUIRED)

add_library(lvglsdl ${PROJECT_SOURCE_DIR}/lv_sdl_disp.c
                    ${PROJECT_SOURCE_DIR}/lv_port_indev_encoder.cc)

target_compile_definitions(
  lvglsdl PRIVATE -DLV_CONF_INCLUDE_SIMPLE -DLV_LVGL_H_INCLUDE_SIMPLE
                  -DLV_CONF_PATH=${LV_CONF_PATH})

message("lvgl_drv: LV_CONF_PATH =${LV_CONF_PATH}")
message("lvgl_drv: LV_CONF_DIR =${LV_CONF_DIR}")

target_compile_options(lvglsdl PRIVATE -Wall -O2 $<$<COMPILE_LANGUAGE:CXX>:
                                       -std=c++20>)

# possible macOS m1 homebrew SDL location
if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm64")
  target_include_directories(lvglsdl PUBLIC /opt/homebrew/include)
  target_link_options(lvglsdl PUBLIC -L /opt/homebrew/lib)
# possible macOS intel homebrew SDL location
elseif(WIN32)
	target_link_libraries(lvglsdl PRIVATE SDL2::SDL2main SDL2::SDL2)
else()	
  target_include_directories(lvglsdl PUBLIC /usr/local/include)
  target_link_options(lvglsdl PUBLIC -L /usr/local/lib)
endif()

message(SDL2_INCLUDE_DIRS=${SDL2_INCLUDE_DIRS})

target_include_directories(
  lvglsdl
  PRIVATE ${SDL2_INCLUDE_DIRS}
  PUBLIC ${PROJECT_SOURCE_DIR} ${LV_CONF_DIR} ${LVGL_DIR})
