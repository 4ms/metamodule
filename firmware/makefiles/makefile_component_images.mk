# make comp-images
#   Generates LVGL image files from SVGs for components:
#   The component files to be converted is ../graphics/BRANDNAME/components/*.svg
#   The converted LVGL-format image files will be in src/gui/images/BRANDNAME/components/*.[png,c]
#   Unlike normal Makefile rules, the .c file will only be built if it's not present
#   (not just because the .svg file has a newer timestamp)

# make faceplate-images
#   Generates LVGL image files from SVGs for faceplates:
#   Specify the path to faceplates in a variable called BRANDNAME_faceplate_svgs
#   (full path or relative path from this makefile)

# make image-list
#   Adds any missing images to the faceplate_images.hh file
#   Uses the list of all brands faceplate SVGs


brands := 4ms
4ms_faceplate_svgs := $(filter-out ../vcv/res/modules/HubMedium_artwork.svg,$(wildcard ../vcv/res/modules/*.svg))

brands += Befaco 
include vcv_ports/glue/Befaco/modules.mk
Befaco_faceplate_svgs := $(addprefix vcv_ports/Befaco/res/panels/,$(addsuffix .svg,$(Befaco_modules)))

brands += AudibleInstruments 
include vcv_ports/glue/AudibleInstruments/modules.mk
AudibleInstruments_faceplate_svgs := $(addprefix vcv_ports/AudibleInstruments/res/panels/,$(addsuffix .svg,$(AudibleInstruments_modules)))

brands += hetrickcv
include vcv_ports/glue/hetrickcv/modules.mk
hetrickcv_faceplate_svgs := $(addprefix vcv_ports/hetrickcv/res/panels/,$(addsuffix .svg,$(hetriccv_modules)))


brands += Rack 


###########################################################################################################
###########################################################################################################
###########################################################################################################
###########################################################################################################
###########################################################################################################

.SECONDEXPANSION:

svgscript := ../shared/svgextract/svgextract.py
graphics_dir := ../graphics
lvgl_image_dir := src/gui/images
image_list_header := $(lvgl_image_dir)/faceplate_images.hh

# Components:

define comp_TEMPLATE =
$(1)_comp_svgs := $(wildcard $(graphics_dir)/$(1)/components/*.svg)
$(1)_comp_lvgls := $$(addprefix $(lvgl_image_dir)/$(1)/components/,$$(notdir $$($(1)_comp_svgs:.svg=.c)))
comp_lvgls += $$($(1)_comp_lvgls)
endef

comp_lvgls :=
$(foreach brand,$(brands),$(eval $(call comp_TEMPLATE,$(brand))))

comp-images: $(comp_lvgls)

# This rule is order-only, so the .c will only be built if it's not found
src/gui/images/%.c: | ../graphics/$$*.svg
	@echo "Converting: $*"
	python3 $(svgscript) convertSvgToLvgl $| $@

# Faceplates:

Rack_faceplate_svg_dir :=  

define make_faceplate =
@echo "-------"
$(info $(notdir $*): Creating 240px-height lvgl img from full-sized svg artwork $<)
python3 $(svgscript) createLvglFaceplate $< $@ $(if $(findstring 4ms,$@),faceplate,all)
endef

define update_img_list =
@echo "" && \
echo "$(1): Adding to image list if needed" && \
python3 $(svgscript) appendimglist $(1) $(image_list_header)
endef

define faceplate_TEMPLATE =
$(1)_faceplate_lvgls := $$(addprefix $(lvgl_image_dir)/$(1)/modules/,$$(notdir $$($(1)_faceplate_svgs:.svg=_240.c)))
faceplate_lvgls += $$($(1)_faceplate_lvgls)
$(1)_faceplate_lvgl_dir := $(lvgl_image_dir)/$(1)/modules
$(1)_faceplate_svg_dir := $$(dir $$(firstword $$($(1)_faceplate_svgs)))

$$($(1)_faceplate_lvgl_dir)/%_240.c: $$($(1)_faceplate_svg_dir)/%.svg
	$$(make_faceplate)

$(1)_debug:
	ls -l $$($(1)_faceplate_lvgl_dir)
	ls -l $$($(1)_faceplate_svg_dir)
endef

faceplate_lvgls =
non4msbrands := $(filter-out 4ms,$(brands))
$(foreach brand,$(brands),$(eval $(call faceplate_TEMPLATE,$(brand))))

faceplate-images: $(faceplate_lvgls) 

image-list:
	$(foreach m,$(basename $(notdir $(faceplate_lvgls))), $(call update_img_list,$m))
