// HubKnobLabel needs to know:
// parent module->id (onDeselect checks if we deselected by clicking on our hub)
// All knobMaps of parent module [Todo: don't need this, can check with centralData or with VCV engin)
// knobMap for this knob (onDeselect: knobmap.create()
//
// HubKnob needs to know:
// parent module ptr (draw() checks if it's null before reading knobMaps)
// parent module knobMap for this knob
