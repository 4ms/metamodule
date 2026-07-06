BUILDDIR := build

# MIDI support (rtmidi) in the GUI simulator. Override on the command line, e.g.
# `make config-sim MIDI=OFF`, or use the config-sim-midi / config-sim-nomidi targets.
# Enabling MIDI requires the rtmidi submodule:
#     git submodule update --init simulator/rtmidi
# (Linux also needs ALSA headers: sudo apt install libasound2-dev)
MIDI ?= ON

all: | $(BUILDDIR)
	cmake --build $(BUILDDIR)

$(BUILDDIR):
	cmake --fresh --preset Default -DLOG_LEVEL=DEBUG -DSIMULATOR_MIDI=$(MIDI)

clean:
	cmake --fresh --preset Default -DLOG_LEVEL=DEBUG -DSIMULATOR_MIDI=$(MIDI)

config-sim: clean

# Reconfigure with MIDI explicitly enabled or disabled
config-sim-midi:
	cmake --fresh --preset Default -DLOG_LEVEL=DEBUG -DSIMULATOR_MIDI=ON

config-sim-nomidi:
	cmake --fresh --preset Default -DLOG_LEVEL=DEBUG -DSIMULATOR_MIDI=OFF

realclean:
	rm -rf $(BUILDDIR) build-headless

warnings:
	cmake --fresh --preset gcc-warn -DLOG_LEVEL=TRACE -DSIMULATOR_MIDI=$(MIDI)

run: all
	build/simulator

debug:
	cmake --build ${BUILDDIR} --target debug

config-headless:
	cmake --fresh --preset headless -DLOG_LEVEL=DEBUG

config-headless-min:
	cmake --fresh --preset headless-min -DLOG_LEVEL=NONE

headless:
	@test -f build-headless/CMakeCache.txt || cmake --fresh --preset headless -DLOG_LEVEL=DEBUG
	cmake --build build-headless

headless-min:
	@test -f build-headless/CMakeCache.txt || cmake --fresh --preset headless-min -DLOG_LEVEL=NONE
	cmake --build build-headless

.PHONY: all clean warnings run headless headless-min config-sim config-sim-midi config-sim-nomidi realclean debug config-headless config-headless-min
