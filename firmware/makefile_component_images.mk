####
#### Generate LVGL image files from SVGs for components
####
#### make comp-images
####
#### The component Svg files must be in ../graphics/BRANDNAME/components/
#### The converted LVGL-format image files will be in src/gui/images/BRANDNAME/components/ 

#### Add a brand name here:
brands = 4ms Rack Befaco AudibleInstruments 

svgscript := ../shared/svgextract/svgextract.py
graphics_dir := ../graphics
lvgl_image_dir := src/gui/images
image_list_header := $(lvgl_image_dir)/faceplate_images.hh

define comp_TEMPLATE =
$(1)_comp_svgs := $(wildcard $(graphics_dir)/$(1)/components/*.svg)
$(1)_comp_lvgls := $$(addprefix $(lvgl_image_dir)/$(1)/components/,$$(notdir $$($(1)_comp_svgs:.svg=.c)))
comp_lvgls += $$($(1)_comp_lvgls)
endef

comp_lvgls = 
$(foreach brand,$(brands),$(eval $(call comp_TEMPLATE,$(brand))))

comp-images: $(comp_lvgls)


.SECONDEXPANSION:
src/gui/images/%.c : ../graphics/$$*.svg
	@echo "Converting: $*"
	@python3 $(svgscript) convertSvgToLvgl $< $@
	@echo "______________"



#####


4ms_faceplate_svg_dir    := ../vcv/res/modules
Befaco_faceplate_svg_dir := vcv_ports/Befaco/res/panels
Rack_faceplate_svg_dir   := vcv_ports/AudibleInstruments/res

4ms_faceplate_lvgl_dir    := src/gui/images/4ms/modules
Befaco_faceplate_lvgl_dir := src/gui/images/Befaco/modules
Rack_faceplate_lvgl_dir   := src/gui/images/Rack/modules

4ms_faceplate_svgs    := $(wildcard $(4ms_faceplate_svg_dir)/*.svg) 
Befaco_faceplate_svgs := $(wildcard $(Befaco_faceplate_svg_dir)/*.svg)
Rack_faceplate_svgs   := $(wildcard $(Rack_faceplate_svg_dir)/*.svg) 

4ms_faceplate_lvgls    := $(subst $(4ms_faceplate_svg_dir),$(4ms_faceplate_lvgl_dir),$(4ms_faceplate_svgs:.svg=.c))
Befaco_faceplate_lvgls := $(subst $(Befaco_faceplate_svg_dir),$(Befaco_faceplate_lvgl_dir),$(Befaco_faceplate_svgs:.svg=.c))
Rack_faceplate_lvgls   := $(subst $(Rack_faceplate_svg_dir),$(Rack_faceplate_lvgl_dir),$(Rack_faceplate_svgs:.svg=.c))

module-images: $(4ms_faceplate_lvgls) $(Befaco_faceplate_lvgls) $(Rack_faceplate_lvgls)

## Details:
$(4ms_faceplate_lvgls): $(4ms_faceplate_lvgl_dir)/%.c : $(4ms_faceplate_svg_dir)/%.svg
	$(info)
	$(info -------)
	$(info $(notdir $*): Creating 240px-height lvgl img from full-sized svg artwork $<)
	python3 $(svgscript) createLvglFaceplate $< $@ all
	$(info)
	$(info -------)
	$(info $(notdir $*): Adding to image_list.hh if needed)
	@python3 $(svgscript) appendimglist $(notdir $*)_artwork $(image_list_header)

$(Befaco_faceplate_lvgls): $(Befaco_faceplate_lvgl_dir)/%.c : $(Befaco_faceplate_svg_dir)/%.svg
	$(info)
	$(info -------)
	$(info $(notdir $*): Creating 240px-height lvgl img from full-sized svg artwork $<)
	python3 $(svgscript) createLvglFaceplate $< $* all
	$(info)
	$(info -------)
	$(info $(notdir $*): Adding to image_list.hh if needed)
	@python3 $(svgscript) appendimglist $(notdir $*)_artwork $(image_list_header)

$(Rack_faceplate_lvgls): $(Rack_faceplate_lvgl_dir)/%.c : $(Rack_faceplate_svg_dir)/%.svg
	$(info)
	$(info -------)
	$(info $(notdir $*): Creating 240px-height lvgl img from full-sized svg artwork $<)
	python3 $(svgscript) createLvglFaceplate $< $* all
	$(info)
	$(info -------)
	$(info $(notdir $*): Adding to image_list.hh if needed)
	@python3 $(svgscript) appendimglist $(notdir $*)_artwork $(image_list_header)

