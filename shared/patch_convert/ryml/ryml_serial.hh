#pragma once
#include "patch/patch.hh"
#include "ryml_std.hpp"
//
#include "ryml.hpp"
#include "ryml_serial_chars.hh"

void write(ryml::NodeRef *n, Jack const &jack);
bool read(ryml::NodeRef const &n, Jack *jack);

bool read(ryml::NodeRef const &n, InternalCable *cable);
bool read(ryml::NodeRef const &n, MappedInputJack *j);
bool read(ryml::NodeRef const &n, MappedOutputJack *j);
bool read(ryml::NodeRef const &n, MappedKnob *k);
bool read(ryml::NodeRef const &n, StaticParam *k);
bool read(ryml::NodeRef const &n, MidiMap *k);

namespace RymlInit
{
void init_once();
};
