add_library(SlsExport OBJECT)

target_sources(SlsExport PRIVATE
	main_menu/ui.cpp
	main_menu/screens/ui_MainMenu.c
)
