# Makefile responsible for generating module-info header files, LVGL faceplate images
# Note: currently only 4ms uses svg info files (other brands need manual creation of info headers)

brands := 4ms Befaco AudibleInstruments

svgscript := $(SHARED)/svgextract/svgextract.py
image_list_header := src/pages/images/image_list.hh

# All dirs potentially containing module-info svg files:
svginfo_dirs := $(foreach brand,$(brands),$(SHARED)/CoreModules/$(brand)/svg)

# All module-info svg files:
svginfo_files := $(foreach dir,$(svginfo_dirs),$(wildcard $(dir)/*_info.svg))

# List of module-info header files that are required:
info_file_list := $(subst /svg/,/info/,$(svginfo_files:.svg=.hh))

# All dirs potentially containing artwork-only svg files:
artwork_only_svg_dirs := $(foreach brand,$(brands),$(SHARED)/CoreModules/$(brand)/vcv_svg)

# List of LVGL faceplate artwork files we must generate from svg/*_info.svg and vcv_svg/*.svg
artwork_only_svg_files += $(foreach dir,$(artwork_only_svg_dirs),$(wildcard $(dir)/*.svg))

# List of all 240px and 120px (height) png files used to generate LVGL .c files
# These are intermediate files
png_files := $(subst $(SHARED)/CoreModules/,src/pages/images/,$(subst /svg/,/modules/,$(svginfo_files:_info.svg=_artwork_240.png)))
png_files += $(subst $(SHARED)/CoreModules/,src/pages/images/,$(subst /svg/,/modules/,$(svginfo_files:_info.svg=_artwork_120.png)))
png_files += $(subst $(SHARED)/CoreModules/,src/pages/images/,$(subst /vcv_svg/,/modules/,$(artwork_only_svg_files:.svg=_artwork_240.png)))
png_files += $(subst $(SHARED)/CoreModules/,src/pages/images/,$(subst /vcv_svg/,/modules/,$(artwork_only_svg_files:.svg=_artwork_120.png)))

MODULEIMG_C := $(png_files:.png=.c)

# Processes all modified module-info svg files to module-info files
module-infos: $(info_file_list)

# Generate all faceplate images to LVGL format (only 4ms for now)
images: $(MODULEIMG_C)

.SECONDEXPANSION:

# Processes module-info svg in /some/path/svg/XXX_info.svg, outputting to /some/path/info/XXX_info.hh
%_info.hh: $$(basename $$(subst /info/,/svg/,$$@)).svg
	$(info $@: Creating ModuleInfo header file)
	python3 $(svgscript) createInfo $< ../info/
	

# Generate LVGL Faceplate artwork from module-info SVG files in a brand/svg/ dir
%_artwork_120.c %_artwork_240.c: $$(subst /modules/,/svg/,$$(subst src/pages/images/,$(SHARED)/CoreModules/,$$*))_info.svg
	$(info)
	$(info -------)
	$(info $(notdir $*): Creating 120px and 240px-height lvgl imgs from full-sized svg artwork $<)
	python3 $(svgscript) createLvglFaceplate $< $*
	$(info)
	$(info -------)
	$(info $(notdir $*): Adding to image_list.hh if needed)
	@python3 $(svgscript) appendimglist $(notdir $*)_artwork $(image_list_header)


#Generate LVGL Faceplate artwork from artwork-only SVG files in a brand/vcv_svg/ dir
%_artwork_120.c %_artwork_240.c: $$(subst /modules/,/vcv_svg/,$$(subst src/pages/images/,$(SHARED)/CoreModules/,$$*)).svg
	$(info)
	$(info -------)
	$(info $(notdir $*): Creating 120px and 240px-height lvgl imgs from full-sized svg artwork $<)
	python3 $(svgscript) createLvglFaceplate $< $* all
	$(info)
	$(info -------)
	$(info $(notdir $*): Adding to image_list.hh if needed)
	@python3 $(svgscript) appendimglist $(notdir $*)_artwork $(image_list_header)


.SECONDARY: $(png_files)
