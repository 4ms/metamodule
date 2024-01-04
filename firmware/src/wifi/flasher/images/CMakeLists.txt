set(WIFI_IMAGES
    ${CMAKE_CURRENT_LIST_DIR}/bootloader.bin
    ${CMAKE_CURRENT_LIST_DIR}/application.bin
    ${CMAKE_CURRENT_LIST_DIR}/filesystem.img
    )

# Create empty target to be filled with images
add_library(wifi_images)
set_target_properties(wifi_images PROPERTIES LINKER_LANGUAGE CXX)

# Convert a binary file into an object file without absolute paths embedded in symbol names
# Adapted from https://stackoverflow.com/a/62152985
function(make_binary_object __file __object)
  get_filename_component(__file_name ${__file} NAME)
  string(MAKE_C_IDENTIFIER ${__file_name} __file_c_identifier)
  add_custom_command(OUTPUT ${__object}
      COMMAND ${CMAKE_OBJCOPY}
          --input-format binary
          --output-format elf32-littlearm
          --binary-architecture arm
          --prefix-sections .binary
          /dev/stdin
          ${__object} < ${__file}
      COMMAND ${CMAKE_OBJCOPY}
          --redefine-sym _binary__dev_stdin_start=_binary_${__file_c_identifier}_start
          --redefine-sym _binary__dev_stdin_end=_binary_${__file_c_identifier}_end
          --redefine-sym _binary__dev_stdin_size=_binary_${__file_c_identifier}_size
          ${__object}
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      DEPENDS ${__file})
  set_source_files_properties(${__object} PROPERTIES EXTERNAL_OBJECT TRUE)
endfunction()

# Convert all images to object files and add them to the images target
foreach(WIFI_IMAGE_FILE ${WIFI_IMAGES})

  # Set locations for target files
  get_filename_component(IMAGE_BASE_NAME ${WIFI_IMAGE_FILE} NAME)
  set(IMAGE_TARGET_FILE ${CMAKE_CURRENT_BINARY_DIR}/wifi-images/${IMAGE_BASE_NAME}.obj)

  # Convert binary to object file and add to library
  make_binary_object(${WIFI_IMAGE_FILE} ${IMAGE_TARGET_FILE})
  target_sources(wifi_images PRIVATE ${IMAGE_TARGET_FILE})

  # Provide expected hash
  file(MD5 ${WIFI_IMAGE_FILE} THIS_HASH)
  get_filename_component(IMAGE_BASE_NAME_NO_EXT ${WIFI_IMAGE_FILE} NAME_WE)
  target_compile_definitions(wifi_images PUBLIC ${IMAGE_BASE_NAME_NO_EXT}_MD5="${THIS_HASH}")
  
endforeach() 
