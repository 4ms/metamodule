#pragma once
#include "patch/patch.hh"
#include "ryml_all.hpp"
#include "ryml_serial_chars.hh"

void write(ryml::NodeRef *n, Jack const &jack);
bool read(ryml::NodeRef const &n, Jack *jack);

void write(ryml::NodeRef *n, PatchHeader const &ph);
bool read(ryml::NodeRef const &n, PatchHeader *ph);

bool read(ryml::NodeRef const &n, InternalCable *cable);
bool read(ryml::NodeRef const &n, MappedInputJack *j);
bool read(ryml::NodeRef const &n, MappedOutputJack *j);
bool read(ryml::NodeRef const &n, MappedKnob *k);
bool read(ryml::NodeRef const &n, StaticParam *k);
