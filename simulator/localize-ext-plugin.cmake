# Build-time script (cmake -P) that prelinks an ext-builtin plugin brand's
# static library into a single relocatable object, renames the plugin's init()
# entry point to init_<BRAND>, and localizes all other symbols.
#
# Why: ext-builtin plugins are statically linked into the simulator alongside
# the firmware's built-in brands. Without this step, same-named global symbols
# in two plugins  get merged by the linker, and one plugin's code/vtables
# silently operate on another plugin's incompatible objects. Localizing each
# brand's symbols gives it the same isolation it has when dynamically loaded on
# hardware, with no source changes needed in the plugin.
#
# The plugin may define its entry point in any of the ways the hardware dynamic
# loader accepts:
#   - extern "C" void init(rack::plugin::Plugin *)
#   - void init(rack::plugin::Plugin *)            (C++ linkage)
#   - void init_<BRAND>(rack::plugin::Plugin *)    (legacy simulator style)
# The first two are renamed to the mangled name of init_<BRAND> that the generated
# ext_plugin_builtin.hh declares. Only init_<BRAND> is left exported.
#
# Inputs:
#   ARCHIVE      - path to the brand's static library (libBrand.a)
#   DEP_ARCHIVES - "|"-separated paths of the brand's own static-lib dependencies
#                  (loaded lazily: only members the plugin references are pulled in)
#   BRAND        - brand library name (init entry point becomes init_<BRAND>)
#   OUTPUT       - path of the localized relocatable object to produce
#   HOST_APPLE   - TRUE when building on macOS
#   CXX          - C++ compiler driver (macOS: used to drive `ld -r`)
#   LINKER       - ld (Linux only)
#   OBJCOPY      - objcopy (Linux only)

if (DEP_ARCHIVES)
	string(REPLACE "|" ";" dep_archives "${DEP_ARCHIVES}")
else()
	set(dep_archives "")
endif()

# Mangled name of `void init_<BRAND>(rack::plugin::Plugin *)`, which is how the
# generated ext_plugin_builtin.hh declares each brand's entry point:
string(LENGTH "init_${BRAND}" init_name_len)
set(entry_sym "_Z${init_name_len}init_${BRAND}PN4rack6plugin6PluginE")

# Find which init symbol (if any) the plugin defines. Legacy-style plugins that
# already define init_<BRAND>() need no rename.
execute_process(COMMAND nm -g ${ARCHIVE} OUTPUT_VARIABLE archive_syms COMMAND_ERROR_IS_FATAL ANY)

if (HOST_APPLE)
	# macOS symbol names have a leading underscore
	set(alias_args "")
	if (archive_syms MATCHES "T __Z4initPN4rack6plugin6PluginE")
		set(alias_args -Wl,-alias,__Z4initPN4rack6plugin6PluginE,_${entry_sym})
	elseif (archive_syms MATCHES "T _init([\r\n]|$)")
		set(alias_args -Wl,-alias,_init,_${entry_sym})
	endif()

	file(WRITE ${OUTPUT}.exports "*init_${BRAND}*\n")

	# -r: partial (relocatable) link; unexported symbols become local.
	# -mmacosx-version-min: stamp a floor version so the final link never sees the
	# prelinked object as "newer" than its target. -Wl,-w: silence the resulting
	# version-mismatch warnings within this (purely mechanical) prelink step.
	execute_process(
		COMMAND ${CXX} -r -nostdlib -mmacosx-version-min=11.0 -Wl,-w
				-Wl,-force_load,${ARCHIVE}
				${dep_archives}
				${alias_args}
				-Wl,-exported_symbols_list,${OUTPUT}.exports
				-o ${OUTPUT}
		COMMAND_ERROR_IS_FATAL ANY
	)
else()
	set(rename_args "")
	if (archive_syms MATCHES "T _Z4initPN4rack6plugin6PluginE")
		set(rename_args --redefine-sym _Z4initPN4rack6plugin6PluginE=${entry_sym})
	elseif (archive_syms MATCHES "T init([\r\n]|$)")
		set(rename_args --redefine-sym init=${entry_sym})
	endif()

	execute_process(
		COMMAND ${LINKER} -r --whole-archive ${ARCHIVE} --no-whole-archive ${dep_archives} -o ${OUTPUT}.partial.o
		COMMAND_ERROR_IS_FATAL ANY
	)
	execute_process(
		COMMAND ${OBJCOPY} ${rename_args} -w --keep-global-symbol=*init_${BRAND}* ${OUTPUT}.partial.o ${OUTPUT}
		COMMAND_ERROR_IS_FATAL ANY
	)
endif()

# Sanity check: the result must export the entry point, or the final simulator link
# will fail with a much more confusing undefined-symbol error.
execute_process(COMMAND nm -g ${OUTPUT} OUTPUT_VARIABLE output_syms COMMAND_ERROR_IS_FATAL ANY)
string(FIND "${output_syms}" "${entry_sym}" entry_found)
if (entry_found EQUAL -1)
	message(FATAL_ERROR
		"Plugin brand '${BRAND}' does not define an init() entry point.\n"
		"Expected the plugin to define `void init(rack::plugin::Plugin *)` "
		"(with C or C++ linkage), or `void init_${BRAND}(rack::plugin::Plugin *)`.\n"
		"Symbols searched in: ${ARCHIVE}"
	)
endif()
