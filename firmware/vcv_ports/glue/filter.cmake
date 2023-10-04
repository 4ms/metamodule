macro(limit_modules_built ModuleList)

  if(USE_LIMITED_MODULES)
    foreach(m IN LISTS ${ModuleList})
      if(m IN_LIST LIMITED_MODULE_SLUGS)
        # message(${m} " will be built")
      else()
        # message(${m} " not be built")
        list(REMOVE_ITEM ${ModuleList} ${m})
      endif()
    endforeach()
  endif()

endmacro()
