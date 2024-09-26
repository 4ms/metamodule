set(LOG_LEVELS DUMP TRACE DEBUG INFO WARN ERROR NONE)
set(LOG_LEVEL NONE CACHE STRING "Console log level")
set_property(CACHE LOG_LEVEL PROPERTY STRINGS ${LOG_LEVELS})

if(NOT LOG_LEVEL IN_LIST LOG_LEVELS)
	message(FATAL_ERROR "LOG_LEVEL must be one of ${LOG_LEVELS}")
endif()



function(enable_logging)

if (LOG_LEVEL STREQUAL "DUMP")
	message("Log Level: Dump")
	set(LOG_LEVEL_NUM 6)
endif()

if (LOG_LEVEL STREQUAL "TRACE")
	message("Log Level: Trace")
	set(LOG_LEVEL_NUM 5)
endif()

if (LOG_LEVEL STREQUAL "DEBUG")
	message("Log Level: Debug")
	set(LOG_LEVEL_NUM 4)
endif()

if (LOG_LEVEL STREQUAL "INFO")
	message("Log Level: Info")
	set(LOG_LEVEL_NUM 3)
endif()

if (LOG_LEVEL STREQUAL "WARN")
	message("Log Level: Warn")
	set(LOG_LEVEL_NUM 2)
endif()

if (LOG_LEVEL STREQUAL "ERROR")
	message("Log Level: Error")
	set(LOG_LEVEL_NUM 1)
endif()

if (LOG_LEVEL STREQUAL "NONE")
	message("Log Level: None")
	set(LOG_LEVEL_NUM 0)
endif()

add_compile_definitions(LOG_LEVEL=${LOG_LEVEL_NUM})

endfunction()
