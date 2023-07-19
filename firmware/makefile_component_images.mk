#TODO:
#foreach brand...
# brands = 4ms Rack Befaco AudibleInstruments 

comp_svg_dir := ../graphics/4ms/components
befaco_svg_dir := ../graphics/Befaco/components
rack_svg_dir := ../graphics/Rack/components

comp_lvgl_img_dir := src/pages/images/4ms/components
befaco_lvgl_img_dir := src/pages/images/Befaco/components
rack_lvgl_img_dir := src/pages/images/Rack/components

comp_svgs := $(wildcard $(comp_svg_dir)/*.svg) 
befaco_svgs := $(wildcard $(befaco_svg_dir)/*.svg)
rack_svgs := $(wildcard $(rack_svg_dir)/*.svg) 

comp_lvgl_imgs := $(subst $(comp_svg_dir),$(comp_lvgl_img_dir),$(comp_svgs:.svg=.c))
befaco_lvgl_imgs := $(subst $(befaco_svg_dir),$(befaco_lvgl_img_dir),$(befaco_svgs:.svg=.c))
rack_lvgl_imgs := $(subst $(rack_svg_dir),$(rack_lvgl_img_dir),$(rack_svgs:.svg=.c))

comp-images: $(comp_lvgl_imgs) $(befaco_lvgl_imgs) $(rack_lvgl_imgs)

$(comp_lvgl_imgs): $(comp_lvgl_img_dir)/%.c : $(comp_svg_dir)/%.svg
	python3 ../shared/svgextract/svgextract.py convertSvgToLvgl $< $@

$(befaco_lvgl_imgs): $(befaco_lvgl_img_dir)/%.c : $(befaco_svg_dir)/%.svg
	python3 ../shared/svgextract/svgextract.py convertSvgToLvgl $< $@

$(rack_lvgl_imgs): $(rack_lvgl_img_dir)/%.c : $(rack_svg_dir)/%.svg
	python3 ../shared/svgextract/svgextract.py convertSvgToLvgl $< $@

