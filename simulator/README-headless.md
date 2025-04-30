## MetaModule Headless 

This is designed to run a single patch, reading audio in from a file and saving
the audio output to a file.

**Usage:**
```
cd simulator
cmake --fresh --preset headless 
cmake --build build
build/simulator  -p ../patches/default/Djembe4Verb.yml
```

You should see some output like this:

```
Run for 4800000 samples (100 sec @ 48kHz)
HostFileIO: get file size ../patches/default/Djembe4verb.yml
HostFileIO: read ../patches/default/Djembe4verb.yml
Patch loaded: 16 modules
ERROR: WavReader: file 'audio_in.wav' not found
Input file not valid, using silence
Process time: 1195 ms
Effective load (single core): 1.195 percent
```

The `-p` option specifies the patch file to load.

You can provide it a stereo .wav file with the `--in` option. This will be sent
to In 1 and In 2. If you don't provide a file, then it will send silence to
those channels (hence the "ERROR: WavReader: file not found").

The output from Out 1 and Out 2 is saved to a .wav file, you can specify it
with `--out` or else a default name will be used.

You can specify the number of samples to process with `-n`, for example `-n
48000` will process 1 second of sound at 48kHz.

If you want to reduce compilation time by only building 4ms modules and not other brands,
you can use the cmake preset `headless-min` instead of `headess` (obviously your
patch files can't use modules that weren't built):

```
cmake --fresh --preset headless-min
```

**Purpose:**
This project is useful for testing the audio stream while developing, for
example, making sure that optimizations do not effect the audio outputs. It
also displays the processing time as a percentage of sample time at 48kHz,
which is useful for seeing if optimizations are having an effect (on the host
computer, at least). 

Finally, this can be run on a variety of processors to compare the MM engine performance.

**Future:**

A future improvement would be to tie it into the OS's audio drivers, so it
could stream audio. The driver adaptor should be done such that it can tie into
the hardware MM's audio stream easily (so we can run headless on the MM).

With streaming audio working, it could then respond to MIDI events on the host
computer, so you could use it as a full headless synth.

