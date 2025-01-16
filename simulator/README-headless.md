## MetaModule Headless 

This is designed to run a single patch, reading audio in from a file and saving
the audio output to a file.

**Usage:**
```
cd simulator
cmake --fresh --preset headless 
cmake --build build
build/simulator  -p../patches/default/Djembe4Verb.yml
```
The `-p` option specifies the patch file to load.

You can provide it a stereo .wav file with the `--in` option. This will be sent
to In 1 and In 2. If you don't provide a file, then it will send silence to
those channels. 

The output from Out 1 and Out 2 is saved to a .wav file, you can specify it
with `--out` or else a default name will be used.

You can specify the number of samples to process with `-n`, for example `-n
48000` will process 1 second of sound at 48kHz.


**Purpose:**
This project is useful for testing the audio stream while developing, for
example, making sure that optimizations do not effect the audio outputs. It
also displays the processing time as a percentage of sample time at 48kHz,
which is useful for seeing if optimizations are having an effect (on the host
computer, at least). 

Finally, we've been using this already to compare the MM engine performance on
various processors.

**Future:**

A future improvement would be to tie it into the OS's audio drivers, so it
could stream audio. The driver adaptor should be done such that it can tie into
the hardware MM's audio stream easily (so we can run headless on the MM).

With streaming audio working, it could then respond to MIDI events on the host
computer, so you could use it as a full headless synth.

