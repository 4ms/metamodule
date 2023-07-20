SVG info file Specifications
----------------------------

Red: Knob or Slider
Circle = Knob, with a default position specified by amount of blue:
0% (fully CCW): color is ‘#FF0000’ or ‘#f00’ or ‘red’
25%: #FF0020
50%: #FF0040
75%: #FF0060
100%: #FF0080
[and any default value can be specified with anything between Hex 00 - Hex 80 for the last two digits]
See below for circle sizes

Rectangle = Slider
Same colors and default position as knob
2mm x 27mm = standard 4ms slider
Can be vertical or horizontal

Deep Magenta: Rotary Encoder
color is ‘#C000C0’

Green: Input jack, analog (CV or audio):
color is ‘#00FF00’ or ‘#0f0’ or ‘lime’

Light Green: Input jack, digital (gate or trig)
color is ‘#80FF80’

Blue: Output jack, analog (CV or audio)
color is ‘#0000FF’ or ‘#00f’ or ‘blue’

Light Blue: Output jack, digital (gate or trig)
color is ‘#8080FF’

Magenta: LED
color is #FF00FF
Append name with class name:
    - #RedGreenBlueLight (default)
    - #RedBlueLight
    - #OrangeLight

Orange: Button - Latching
color is ‘#FF8000’

Light Orange: Button - Momentary
color is ‘#FFC000’

Light Coral: Switch - 2pos
color is ‘#FF8080’

Faded Orange: Switch - 3pos
color is ‘#FFC080’

Misc widget/undefined custom element
color is ‘#FFFF00’ or color is ‘#ff0’ or color is ‘yellow’

-------------

Knob sizes:

Small (SMR Freq, EnOsc Detune, etc):
Diameter = 6mm
(or anything < 7mm)
Code: radius < 10px

Medium (normal Davies):
Diameter = 12mm
(or anything between 7mm and 14.1mm)
Code: 10px < radius < 20px

Large (EnOsc Root):
Diameter = 22mm
(or anything > 14.1mm)
Code: 20px < radius < 40px

----------

Button sizes:

Big button cap (EnOsc, SMR):
Diameter = 8mm
(or anything > 7mm)
Code: radius > 10

Small button cap (Tapo):
Diameter = 5mm
(or anything < 7mm)
Code: radius < 10

------------

Names:
Set the name of each object in AI or Inkscape to the display name.
Example: “Scale CV” (without the quotes).

There are two text elements required. They both must *not* be converted to outlines (must be editable text):
 - Text object with the name “slug”. Text content should be a short identifier (e.g. “SMR” or “EnOsc”)
 - Text object with the name “modulename”. Content is full module name (“Spectral Multiband Resonator”)

--------------

Object Order:
The order of the components in the layer in the AI file is the order that they will be scrolled through on hardware 
Therefore, make sure the order makes sense to a user.
Generally, go from top-left to bottom-right, but with common-sense groupings applied.
For example, on something like the SMR's six channel sliders and buttons, either go through all buttons then all sliders,
or go button1-slider1-button2-slider2-etc. But don't go button-FreqKnob-slider1-button2-LFOCV-slider2.

------------

Export from AI settings:
File > Export > Export As… > select SVG, uncheck “Use Artboards”
Styling: Inline Style
Font: SVG
Images: Link (doesn’t matter)
Object IDs: Layer Names
Decimal: 2
[unchecked: Minify] [unchecked: Responsive] 
