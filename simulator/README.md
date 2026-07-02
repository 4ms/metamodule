## MetaModule Simulator


The simulator runs on a host computer and simulates the screen and the audio
outputs. The pixels should be identical to the actual hardware's pixels.

The audio should be the same as in hardware (though, your sound card might be
AC-coupled, vs. the hardware is DC-coupled).

The following guides are available for the simulator with GUI:

- [Simulator Usage](../docs/simulator-usage.md)
- [Compiling the Simulator](../docs/simulator-building.md)
- [Using plugins with the Simulator](../docs/simulator-ext-plugins.md)

The project can also be built without a GUI, and run headless.

- [Headless simulator](README-headless.md)

### MIDI

The GUI simulator supports MIDI input and output via
[rtmidi](https://github.com/thestk/rtmidi), which is added as a git submodule.

One-time setup:

```
git submodule update --init simulator/rtmidi
# Linux only: install the ALSA dev headers rtmidi needs
sudo apt install libasound2-dev
```

If the submodule is not found, the simulator still builds but MIDI is
disabled (a warning is printed at configure time).

Usage:

- By default the simulator creates virtual MIDI ports named `MetaModule Simulator`
  (ALSA / CoreMIDI). Connect a controller or DAW to these ports.
- `--listmidi` prints the available hardware MIDI ports and exits.
- `--midiin <n>` / `--midiout <n>` open hardware MIDI port `<n>` instead of a
  virtual port (required on Windows, which has no virtual ports).

