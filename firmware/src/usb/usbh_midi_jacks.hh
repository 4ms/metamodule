#pragma once
#include "usb/midi_jack_parse.hh"
#include "usbh_def.h"

// USB-stack-facing half of MIDI jack discovery. The descriptor parsing itself
// (and MidiJackCollection) lives in midi_jack_parse.hh, which is pure and unit
// tested; this file just feeds it the host's config descriptor and drives the
// control transfers needed to read the jack name strings.

void count_midi_jacks(USBH_HandleTypeDef const *phost, uint8_t *num_in_jacks, uint8_t *num_out_jacks);

// Fill jack ids, types, counts, cable numbers and name string indices from the
// already-fetched configuration descriptor. Synchronous; no USB transfers.
// Sets jacks->parsed.
void parse_midi_jacks(USBH_HandleTypeDef const *phost, MidiJackCollection *jacks);

// Drive the name-string reads. Call repeatedly (it issues one control transfer at
// a time): returns USBH_BUSY while a name is still being fetched, USBH_OK once all
// names are collected. Best-effort -- a jack whose name read fails is left with an
// empty name rather than failing the whole connection. Requires parse_midi_jacks()
// to have run first. Sets jacks->done.
USBH_StatusTypeDef collect_midi_jack_names(USBH_HandleTypeDef *phost, MidiJackCollection *jacks);
