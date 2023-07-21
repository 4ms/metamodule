#### Generate LVGL image files from SVGs for components:
#### make comp-images
####
#### The component files to be converted is ../graphics/BRANDNAME/components/*.svg
#### The converted LVGL-format image files will be in src/gui/images/BRANDNAME/components/*.[png,c]
####
#### Generate LVGL image files from SVGs for faceplates:
#### make faceplate-images
####
####  the fullpaths to a list of faceplates to convert
#### and 

#### Add a brand name here:
brands = 4ms Rack Befaco AudibleInstruments 

# We can use wildcards like this:
4ms_faceplate_svgs := $(wildcard ../vcv/res/modules/*.svg) 

# ... Or could use the modules.mk list like this:
include vcv_ports/glue/Befaco/modules.mk
Befaco_faceplate_svgs := $(addprefix vcv_ports/Befaco/res/panels/,$(addsuffix .svg,$(Befaco_modules)))

# ... Or specify them manully like this:
AudibleInstruments_faceplate_svgs := ./vcv_ports/AudibleInstruments/res/Braids.svg

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

comp_lvgls = 
$(foreach brand,$(brands),$(eval $(call comp_TEMPLATE,$(brand))))

comp-images: $(comp_lvgls)

src/gui/images/%.c: ../graphics/$$*.svg
	@echo "Converting: $*"
	@python3 $(svgscript) convertSvgToLvgl $< $@
	@echo "______________"

# Faceplates:

Rack_faceplate_svg_dir :=  

define make_faceplate =
$(info -------)
$(info $(notdir $*): Creating 240px-height lvgl img from full-sized svg artwork $<)
python3 $(svgscript) createLvglFaceplate $< $@ all
@echo "-------"
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
$(foreach brand,$(brands),$(eval $(call faceplate_TEMPLATE,$(brand))))

faceplate-images: $(faceplate_lvgls) 

image-list:
	$(foreach m,$(basename $(notdir $(faceplate_lvgls))), $(call update_img_list,$m))
