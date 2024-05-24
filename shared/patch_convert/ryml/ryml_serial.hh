#pragma once
#include "CoreModules/module_type_slug.hh"
#include "patch/patch.hh"
#include "ryml_std.hpp"

// These must be included after ryml_std.hpp:
#include "ryml.hpp"
#include "ryml_serial_chars.hh"

void write(ryml::NodeRef *n, Jack const &jack);
void write(ryml::NodeRef *n, MappedKnob const &mapped_knob);
void write(ryml::NodeRef *n, MappedKnobSet const &knob_set);
void write(ryml::NodeRef *n, InternalCable const &cable);
void write(ryml::NodeRef *n, MappedInputJack const &j);
void write(ryml::NodeRef *n, MappedOutputJack const &j);
void write(ryml::NodeRef *n, StaticParam const &k);
void write(ryml::NodeRef *n, std::vector<BrandModuleSlug> const &slugs);
void write(ryml::NodeRef *n, ModuleInitState const &state);

bool read(ryml::ConstNodeRef const &n, Jack *jack);
bool read(ryml::ConstNodeRef const &n, InternalCable *cable);
bool read(ryml::ConstNodeRef const &n, MappedInputJack *j);
bool read(ryml::ConstNodeRef const &n, MappedOutputJack *j);
bool read(ryml::ConstNodeRef const &n, MappedKnob *k);
bool read(ryml::ConstNodeRef const &n, MappedKnobSet *ks);
bool read(ryml::ConstNodeRef const &n, StaticParam *k);
bool read(ryml::ConstNodeRef const &n, ModuleInitState *m);
