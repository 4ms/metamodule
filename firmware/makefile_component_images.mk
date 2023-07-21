#TODO: foreach brand...
brands = 4ms Rack Befaco AudibleInstruments 

4ms_svg_dir    := ../graphics/4ms/components
Befaco_svg_dir := ../graphics/Befaco/components
Rack_svg_dir   := ../graphics/Rack/components

4ms_lvgl_img_dir    := src/gui/images/4ms/components
Befaco_lvgl_img_dir := src/gui/images/Befaco/components
Rack_lvgl_img_dir   := src/gui/images/Rack/components

4ms_svgs    := $(wildcard $(4ms_svg_dir)/*.svg) 
Befaco_svgs := $(wildcard $(Befaco_svg_dir)/*.svg)
Rack_svgs   := $(wildcard $(Rack_svg_dir)/*.svg) 

4ms_lvgl_imgs    := $(subst $(4ms_svg_dir),   $(4ms_lvgl_img_dir),   $(4ms_svgs:.svg=.c))
Befaco_lvgl_imgs := $(subst $(Befaco_svg_dir),$(Befaco_lvgl_img_dir),$(Befaco_svgs:.svg=.c))
Rack_lvgl_imgs   := $(subst $(Rack_svg_dir),  $(Rack_lvgl_img_dir),  $(Rack_svgs:.svg=.c))

## Recipe to make all images
comp-images: $(4ms_lvgl_imgs) $(Befaco_lvgl_imgs) $(Rack_lvgl_imgs)

## Details:
$(4ms_lvgl_imgs): $(4ms_lvgl_img_dir)/%.c : $(4ms_svg_dir)/%.svg
	@python3 ../shared/svgextract/svgextract.py convertSvgToLvgl $< $@

$(Befaco_lvgl_imgs): $(Befaco_lvgl_img_dir)/%.c : $(Befaco_svg_dir)/%.svg
	@python3 ../shared/svgextract/svgextract.py convertSvgToLvgl $< $@

$(Rack_lvgl_imgs): $(Rack_lvgl_img_dir)/%.c : $(Rack_svg_dir)/%.svg
	@python3 ../shared/svgextract/svgextract.py convertSvgToLvgl $< $@


4ms_faceplate_svg_dir    := ../vcv/res/modules
Befaco_faceplate_svg_dir := vcv_ports/Befaco/res/panels
Rack_faceplate_svg_dir   := vcv_ports/AudibleInstruments/res

4ms_faceplate_lvgl_dir    := src/gui/images/4ms/modules
Befaco_faceplate_lvgl_dir := src/gui/images/Befaco/modules
Rack_faceplate_lvgl_dir   := src/gui/images/Rack/modules

4ms_faceplate_svgs    := $(wildcard $(4ms_faceplate_svg_dir)/*.svg) 
Befaco_faceplate_svgs := $(wildcard $(Befaco_faceplate_svg_dir)/*.svg)
Rack_faceplate_svgs   := $(wildcard $(Rack_faceplate_svg_dir)/*.svg) 

4ms_faceplate_lvgls    := $(subst $(4ms_faceplate_svg_dir),   $(4ms_lvgl_faceplate_dir),   $(4ms_svgs:.svg=.c))
Befaco_faceplate_lvgls := $(subst $(Befaco_faceplate_svg_dir),$(Befaco_lvgl_faceplate_dir),$(Befaco_svgs:.svg=.c))
Rack_faceplate_lvgls   := $(subst $(Rack_faceplate_svg_dir),  $(Rack_lvgl_faceplate_dir),  $(Rack_svgs:.svg=.c))

module-images: $(4ms_faceplate_lvgls) $(Befaco_faceplate_lvgls) $(Rack_faceplate_lvgls)

## Details:
$(4ms_faceplate_lvgls): $(4ms_faceplate_lvgl_dir)/%.c : $(4ms_faceplate_svg_dir)/%.svg
	$(info)
	$(info -------)
	$(info $(notdir $*): Creating 240px-height lvgl img from full-sized svg artwork $<)
	python3 $(svgscript) createLvglFaceplate $< $* faceplate
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

