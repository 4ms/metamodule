## MetaModule Simulator

This simulates the screen and the audio input/outputs. The pixels should be identical to the actual hardware's pixels.

The audio should be 1:1 the same as in hardware (though, your sound card might be AC-coupled, vs. the hardware is DC-coupled).

### Patch files

Patches are loaded from a local host directory, which can be passed as an argument to the simulator:

```
build/simulator path/to/patchfile/dir/
```

If no path is specified, `../shared/patch` will be used



