## MetaModule Headless 

This is designed to run a single patch, reading audio in from a file and saving the audio output to a file.

Initially the point of this is to test the performance on various hardware.
The time to run patch N samples is reported (processing time / audio sample duration = load).

Future options:
 - Run indefinitely, tying audio to hardware IO (would need to provide an audio driver to the build)
 - MIDI control of parameters
 - MIDI program changes to select patches

