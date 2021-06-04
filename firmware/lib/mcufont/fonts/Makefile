# Path to the command-line utility program
MCUFONT = ../encoder/mcufont

# Names of fonts to process
# FONTS = DejaVuSans12 DejaVuSans12bw DejaVuSerif16 DejaVuSerif32 \
# 	fixed_5x8 fixed_7x14 fixed_10x20 DejaVuSans12bw_bwfont

FONTS = DejaVuSans12 DejaVuSans32 \
		DejaVuSerif16 DejaVuSerif32 \
		fixed_5x8 fixed_7x14 fixed_10x20 \
		GillSans12 \
		GillSans18 \
		GillSans32 \
		GillSans-Bold32 \
		GillSans-SemiBold24 \

		# SFCompactRounded-Regular32 \
		# SFNSRounded-Regular32

# Characters to include in the fonts
CHARS = 0-255 0x2010-0x2015

all: $(FONTS:=.c) $(FONTS:=.dat) fonts.h

clean:
	rm -f $(FONTS:=.c) $(FONTS:=.dat)

fonts.h: $(FONTS:=.c)
	for i in $(FONTS) ; do \
		/bin/echo '#include "'$$i.c'"' >> $@ ; \
	done

%.c: %.dat $(MCUFONT)
	$(MCUFONT) rlefont_export $<

fixed_5x8.c: fixed_5x8.dat $(MCUFONT)
	$(MCUFONT) bwfont_export $<

# DejaVuSans12bw_bwfont.c: DejaVuSans12bw_bwfont.dat $(MCUFONT)
# 	$(MCUFONT) bwfont_export $<

# DejaVuSans12bw_bwfont.dat: DejaVuSans12bw.dat
# 	cp $< $@
	
DejaVuSans12.dat: DejaVuSans.ttf
	$(MCUFONT) import_ttf $< 12
	$(MCUFONT) filter $@ $(CHARS)
	$(MCUFONT) rlefont_optimize $@ 30

DejaVuSans32.dat: DejaVuSans.ttf
	$(MCUFONT) import_ttf $< 32
	$(MCUFONT) filter $@ $(CHARS)
	$(MCUFONT) rlefont_optimize $@ 30

GillSans12.dat: GillSans.ttf
	$(MCUFONT) import_ttf $< 12
	$(MCUFONT) filter $@ $(CHARS)
	$(MCUFONT) rlefont_optimize $@ 30

GillSans18.dat: GillSans.ttf
	$(MCUFONT) import_ttf $< 18
	$(MCUFONT) filter $@ $(CHARS)
	$(MCUFONT) rlefont_optimize $@ 30

GillSans32.dat: GillSans.ttf
	$(MCUFONT) import_ttf $< 32
	$(MCUFONT) filter $@ $(CHARS)
	$(MCUFONT) rlefont_optimize $@ 30

GillSans-Bold32.dat: GillSans-Bold.ttf
	$(MCUFONT) import_ttf $< 32
	$(MCUFONT) filter $@ $(CHARS)
	$(MCUFONT) rlefont_optimize $@ 30

GillSans-SemiBold24.dat: GillSans-SemiBold.ttf
	$(MCUFONT) import_ttf $< 24
	$(MCUFONT) filter $@ $(CHARS)
	$(MCUFONT) rlefont_optimize $@ 30

# DejaVuSans12bw.dat: DejaVuSans.ttf
# 	$(MCUFONT) import_ttf $< 12 bw
# 	$(MCUFONT) filter $@ $(CHARS)
# 	$(MCUFONT) rlefont_optimize $@ 30

DejaVuSerif16.dat: DejaVuSerif.ttf
	$(MCUFONT) import_ttf $< 16
	$(MCUFONT) filter $@ $(CHARS)
	$(MCUFONT) rlefont_optimize $@ 30

DejaVuSerif32.dat: DejaVuSerif.ttf
	$(MCUFONT) import_ttf $< 32
	$(MCUFONT) filter $@ $(CHARS)
	$(MCUFONT) rlefont_optimize $@ 30

%.dat: %.bdf
	$(MCUFONT) import_bdf $<
	$(MCUFONT) filter $@ $(CHARS)
	$(MCUFONT) rlefont_optimize $@30
