#pragma once
#include "patch/patch.hh"
#include "ryml_std.hpp"
//
#include "ryml.hpp"
#include "ryml_serial_chars.hh"

void write(ryml::NodeRef *n, Jack const &jack);
void write(ryml::NodeRef *n, MappedKnob const &mapped_knob);
void write(ryml::NodeRef *n, MappedKnobSet const &knob_set);

bool read(ryml::ConstNodeRef const &n, Jack *jack);
bool read(ryml::ConstNodeRef const &n, InternalCable *cable);
bool read(ryml::ConstNodeRef const &n, MappedInputJack *j);
bool read(ryml::ConstNodeRef const &n, MappedOutputJack *j);
bool read(ryml::ConstNodeRef const &n, MappedKnob *k);
bool read(ryml::ConstNodeRef const &n, MappedKnobSet *ks);
bool read(ryml::ConstNodeRef const &n, StaticParam *k);

namespace RymlInit
{
void init_once();
};
