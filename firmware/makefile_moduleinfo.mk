# Makefile responsible for processing *_info.svg files 
# to generate ModuleInfo header files and VCV artwork 

# Add brands that have svg files in CoreModules/BRAND/svg/*_info.svg:
coremodule_brands := 4ms

svgscript := $(SHARED)/svgextract/svgextract.py
coremodules := $(SHARED)/CoreModules
4ms_vcv_faceplate_artwork_dir := ../vcv/res/modules

.SECONDEXPANSION:

# All dirs potentially containing module-info svg files:
svginfo_dirs := $(foreach brand,$(coremodule_brands),$(coremodules)/$(brand)/svg)

# List of svg info files (source)
svginfo_files := $(foreach dir,$(svginfo_dirs),$(wildcard $(dir)/*_info.svg))

# List of svg artwork files that are required
vcv_artwork_files := $(addprefix $(4ms_vcv_faceplate_artwork_dir)/,$(notdir $(svginfo_files:_info.svg=_artwork.svg)))

# List of module-info header files that are required
info_file_list := $(subst /svg/,/info/,$(svginfo_files:.svg=.hh))


################################## Rules ##############################

# Processes all modified module-info svg files to module-info files
module-infos: $(info_file_list)

%_info.hh: $$(basename $$(subst /info/,/svg/,$$@)).svg
	$(info $@: Creating ModuleInfo header file)
	python3 $(svgscript) createInfo $< ../info/
	
# Generate faceplate svgs for VCV, from info svgs (only for 4ms for now)
#TODO: this only works for 4ms, use $(foreach ..$(eval $(call...))) to work with all coremodule_brands
vcv-images: $(vcv_artwork_files)

%_artwork.svg: $$(subst $(4ms_vcv_faceplate_artwork_dir),$(coremodules)/4ms/svg,$$*)_info.svg
	python3 $(svgscript) createVcvSvg $< $@ 4ms

