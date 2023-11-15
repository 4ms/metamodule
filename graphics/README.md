## Graphics

These are the source svg files which get converted to PNG and LVGL-format .c files, to be used in the firmware and simulator.

Typically these will be copied from the original svg files (i.e. firmware/vcv_ports/BRAND/res/components/*.svg), and then modified to look good on a small  240x320px 16-bit color screen. Things like gradients are removed, contrast is increased, subtle markings are made larger, etc.

Sometimes the files are changed more drastically to work with the way the MetaModule draws things. 
For instance, in VCV a knob can have background svg (which doesn't change) and a foreground svg (which is rotated as the knob turns). The MetaModule, however, just has one image which is rotated. Therefore knob bg and fg svgs must be combined into one rotate-able svg.
