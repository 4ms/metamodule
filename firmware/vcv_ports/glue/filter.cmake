# Reads the given MODULE_LIST.
# If a match for the given BRAND:MODULE is NOT found in the
# global list LIMITED_MODULE_SLUGS, then the item is removed
# from MODULE_LIST.
# Nothing is done if the global var USE_LIMITED_MODULES is not set
macro(limit_modules_built BRAND MODULE_LIST)
  if(USE_LIMITED_MODULES)
    foreach(module IN LISTS ${MODULE_LIST})
      set(combinedslug "${BRAND}:${module}")
      if(combinedslug IN_LIST LIMITED_MODULE_SLUGS)
          # message("WILL build: ${module} (${combinedslug})")
      else()
          # message("NOT build: ${module} (${combinedslug})")
        list(REMOVE_ITEM ${MODULE_LIST} ${module})
      endif()
    endforeach()
  endif()
endmacro()

# Given a combined slug of the format brand:module, 
# return the brand in P_BRAND, and the module in P_MODULE.
# If the combined slug is not valid, unset P_BRAND and P_MODULE.
function(parse_brandmodule COMBINEDSLUG)
  string(REPLACE ":" ";" BRANDMODULELIST "${COMBINEDSLUG}")

  list(LENGTH BRANDMODULELIST len)

  if(len EQUAL 2)
    list(GET BRANDMODULELIST 0 P_BRAND)
    list(GET BRANDMODULELIST 1 P_MODULE)
  else()
    unset(P_BRAND)
    unset(P_MODULE)
  endif()

  set(P_BRAND "${P_BRAND}" PARENT_SCOPE)
  set(P_MODULE "${P_MODULE}" PARENT_SCOPE)
endfunction()

# Parses a file containing Brand:Module slugs and returns:
# USE_LIMITED_MODULES is set if the file is found
# LIMITED_MODULE_SLUGS is set to a list of Brand:Module slugs
# Note that this only checks syntax, the brands and modules given do not have to exist
function (validate_limited_modules_file LIMITED_MODULES_FILE)
  if("${LIMITED_MODULES_FILE}" STREQUAL "")
    message(FATAL_ERROR "Empty filename given for limit file")
  endif()

  # Relative -> Abs path (is relative to firmware/ dir)
  get_filename_component(LIMITED_MODULES_FILE "${LIMITED_MODULES_FILE}" ABSOLUTE)

  if(NOT EXISTS "${LIMITED_MODULES_FILE}")
      message(FATAL_ERROR "The file `${LIMITED_MODULES_FILE}` does not exist.")
  endif()

  file(STRINGS ${LIMITED_MODULES_FILE} RAW_LIMITED_MODULE_SLUGS)
  message("Building limited set of modules:")

  # Fill LIMITED_MODULE_SLUGS list with valid entries
  foreach(m IN LISTS RAW_LIMITED_MODULE_SLUGS)
    if(NOT "${m}" STREQUAL "") #Skip blank lines
      parse_brandmodule(${m})
      if("${P_BRAND}" STREQUAL "" AND "${P_MODULE}" STREQUAL "")
        message(WARNING "   \"${m}\" not valid. Must be in format Brand:ModuleSlug")
      else()
        message("   ${P_BRAND}:${P_MODULE}")
        list(APPEND LIMITED_MODULE_SLUGS "${P_BRAND}:${P_MODULE}")
      endif()
    endif()
  endforeach()

  set(USE_LIMITED_MODULES ON PARENT_SCOPE)
  set(LIMITED_MODULE_SLUGS "${LIMITED_MODULE_SLUGS}" PARENT_SCOPE)
endfunction()


# Given IMGNAME, applies cleanups so we can use it
# as the name of an array in the LVGL image .c file
# Returns the result in variable IMGNAME
function (cleanup_imgname IMGNAME)
  # Handle slugs that start with a number by prefixing "img_" to it
  # This matches what svgextract does in svgextract/actions/lvgl.py
  string(REGEX REPLACE "^([0-9])" "img_\\1" IMGNAME "${IMGNAME}")

  set(IMGNAME ${IMGNAME} PARENT_SCOPE)
endfunction()

