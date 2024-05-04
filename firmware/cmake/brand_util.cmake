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
