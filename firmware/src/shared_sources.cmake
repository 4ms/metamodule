# Canonical lists of portable (hardware-independent) firmware sources that are
# compiled by every consumer of firmware/src: the MP1 firmware, the simulator,
# and the MP2 firmware. Set METAMODULE_FW_DIR to the firmware/ directory before
# including this file.
#
# When a portable source file is added to the codebase, add it here so all
# consumers pick it up (target-specific sources stay in each project's own lists).

# Core patch-playing sources -- used by all consumers, including headless
# (audio-only) builds:
set(MM_SHARED_CORE_SOURCES
	${METAMODULE_FW_DIR}/src/midi/midi_router.cc
	${METAMODULE_FW_DIR}/src/patch_play/plugin_module.cc
	${METAMODULE_FW_DIR}/metamodule-plugin-sdk/version.cc
)

# GUI, patch-file, filesystem, and settings sources -- consumers with a display
# and filesystem (the full simulator and the hardware firmwares):
set(MM_SHARED_APP_SOURCES
	${METAMODULE_FW_DIR}/src/gui/elements/element_name.cc
	${METAMODULE_FW_DIR}/src/gui/elements/panel_name.cc
	${METAMODULE_FW_DIR}/src/gui/slsexport/ui_local.cc
	${METAMODULE_FW_DIR}/src/gui/fonts/fonts.cc
	${METAMODULE_FW_DIR}/src/gui/fonts/ttf.cc
	${METAMODULE_FW_DIR}/src/gui/pages/module_view/element_roller.cc
	${METAMODULE_FW_DIR}/src/gui/pages/module_view/quick_assign.cc
	${METAMODULE_FW_DIR}/src/gui/pages/module_view/draw_module.cc
	${METAMODULE_FW_DIR}/src/gui/pages/tags.cc

	${METAMODULE_FW_DIR}/src/fw_update/updater_proxy.cc
	${METAMODULE_FW_DIR}/src/patch_play/modules_helpers.cc
	${METAMODULE_FW_DIR}/src/patch_play/patch_player_catchup.cc
	${METAMODULE_FW_DIR}/src/patch_file/reload_patch.cc
	${METAMODULE_FW_DIR}/src/params/expanders.cc

	${METAMODULE_FW_DIR}/src/fs/helpers.cc
	${METAMODULE_FW_DIR}/src/fs/time_convert.cc
	${METAMODULE_FW_DIR}/src/fs/general_io.cc
	${METAMODULE_FW_DIR}/src/fs/asset_drive/untar.cc
	${METAMODULE_FW_DIR}/src/fs/fatfs/diskio.cc
	${METAMODULE_FW_DIR}/src/fs/fatfs/delete_node.cc
	${METAMODULE_FW_DIR}/lib/fatfs/source/ff.c
	${METAMODULE_FW_DIR}/lib/fatfs/source/ffunicode.c

	${METAMODULE_FW_DIR}/src/user_settings/settings_file.cc
	${METAMODULE_FW_DIR}/src/user_settings/settings_parse.cc
	${METAMODULE_FW_DIR}/src/user_settings/settings_serialize.cc

	${METAMODULE_FW_DIR}/coreproc_plugin/internal_interface/plugin_app_interface.cc
)
