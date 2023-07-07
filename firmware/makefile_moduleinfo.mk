# Makefile responsible for generating module-info header files, LVGL faceplate images
# Note: currently only 4ms uses svg info files (other brands need manual creation of info headers)

# Add brands here: brands need appropriate directories in CoreModules and firmware image dir
brands := 4ms Befaco AudibleInstruments

# Modify Paths here:
svgscript := $(SHARED)/svgextract/svgextract.py
coremodules := $(SHARED)/CoreModules
vcv_faceplate_artwork_dir := res/modules
lvgl_image_dir := src/pages/images
image_list_header := $(lvgl_image_dir)/image_list.hh


# All dirs potentially containing module-info svg files:
svginfo_dirs := $(foreach brand,$(brands),$(coremodules)/$(brand)/svg)

# All module-info svg files:
svginfo_files := $(foreach dir,$(svginfo_dirs),$(wildcard $(dir)/*_info.svg))

# List of module-info header files that are required:
info_file_list := $(subst /svg/,/info/,$(svginfo_files:.svg=.hh))

# All dirs potentially containing artwork-only svg files:
artwork_only_svg_dirs := $(foreach brand,$(brands),$(coremodules)/$(brand)/vcv_svg)

# List of LVGL faceplate artwork files we must generate from svg/*_info.svg and vcv_svg/*.svg
artwork_only_svg_files += $(foreach dir,$(artwork_only_svg_dirs),$(wildcard $(dir)/*.svg))

# List of all 240px and 120px (height) png files used to generate LVGL .c files
# These are intermediate files
png_files := $(subst $(coremodules)/,$(lvgl_image_dir)/,$(subst /svg/,/modules/,$(svginfo_files:_info.svg=_artwork_240.png)))
png_files += $(subst $(coremodules)/,$(lvgl_image_dir)/,$(subst /svg/,/modules/,$(svginfo_files:_info.svg=_artwork_120.png)))
png_files += $(subst $(coremodules)/,$(lvgl_image_dir)/,$(subst /vcv_svg/,/modules/,$(artwork_only_svg_files:.svg=_artwork_240.png)))
png_files += $(subst $(coremodules)/,$(lvgl_image_dir)/,$(subst /vcv_svg/,/modules/,$(artwork_only_svg_files:.svg=_artwork_120.png)))

lvgl_faceplate_imgs := $(png_files:.png=.c)

vcv_artwork_files := $(subst $(coremodules)/4ms/svg,$(vcv_faceplate_artwork_dir),$(svginfo_files:_info.svg=-artwork.svg))

################################## Rules ##############################

# Processes all modified module-info svg files to module-info files
module-infos: $(info_file_list)

# Generate all faceplate images to LVGL format (only 4ms for now)
firmware-images: $(lvgl_faceplate_imgs)

# Generate faceplate svgs for VCV, from info svgs (only for 4ms for now)
vcv-images: $(vcv_artwork_files)

#######################################################################

# Details:

.SECONDEXPANSION:

%_info.hh: $$(basename $$(subst /info/,/svg/,$$@)).svg
	$(info $@: Creating ModuleInfo header file)
	python3 $(svgscript) createInfo $< ../info/
	

%_artwork_120.c %_artwork_240.c: $$(subst /modules/,/svg/,$$(subst $(lvgl_image_dir)/,$(coremodules)/,$$*))_info.svg
	$(info)
	$(info -------)
	$(info $(notdir $*): Creating 120px and 240px-height lvgl imgs from full-sized svg artwork $<)
	python3 $(svgscript) createLvglFaceplate $< $*
	$(info)
	$(info -------)
	$(info $(notdir $*): Adding to image_list.hh if needed)
	@python3 $(svgscript) appendimglist $(notdir $*)_artwork $(image_list_header)


%_artwork_120.c %_artwork_240.c: $$(subst /modules/,/vcv_svg/,$$(subst $(lvgl_image_dir)/,$(coremodules)/,$$*)).svg
	$(info)
	$(info -------)
	$(info $(notdir $*): Creating 120px and 240px-height lvgl imgs from full-sized svg artwork $<)
	python3 $(svgscript) createLvglFaceplate $< $* all
	$(info)
	$(info -------)
	$(info $(notdir $*): Adding to image_list.hh if needed)
	@python3 $(svgscript) appendimglist $(notdir $*)_artwork $(image_list_header)

%-artwork.svg: $$(subst $(vcv_faceplate_artwork_dir),$(coremodules)/4ms/svg,$$*)_info.svg
	python3 $(svgscript) createVcvSvg $< $@ 4ms

.SECONDARY: $(png_files)
