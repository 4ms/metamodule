SVG info file Specifications
----------------------------
In general, all elements are specified with a circle. But some objects that require a horizontal/vertical orientation are specified by a rectangle.


**Red: Knob or Slider**
Circle = Knob
Default position specified by amount of blue:
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
If height > width then it's vertical. Otherwise it's horizontal

**Deep Magenta: Rotary Encoder**
color is ‘#C000C0’

**Green: Input jack, analog:**
color is ‘#00FF00’ or ‘#0f0’ or ‘lime’

**Light Green: Input jack, gate**
color is ‘#80FF80’

**Blue: Output jack, analog**
color is ‘#0000FF’ or ‘#00f’ or ‘blue’

**Light Blue: Output jack, gate**
color is ‘#8080FF’

**Magenta: LED**
color is #FF00FF
Append object name with `#classname`:

  - `#RedGreenBlueLight (default)`
  - `#RedBlueLight`
  - `#OrangeLight`
  - `#WhiteLight`
  - `#GreenLight`
  - `#RedLight`
  - `#BlueLight`

**Orange: Button - Latching**
color is ‘#FF8000’

**Light Orange: Button - Momentary**
color is ‘#FFC000’

**Light Coral: Switch - 2pos**
color is ‘#FF8080’
If height > width then it's vertical. Otherwise it's horizontal

**Faded Orange: Switch - 3pos**
color is ‘#FFC080’
If height > width then it's vertical. Otherwise it's horizontal

**Medium Grey: AltParamContinuous**
color is ‘#808080’
A continuous range parameter (any value 0.0 to 1.0) that's hidden from the faceplate

**Light Grey: AltParamChoice**
color is ‘#c0c0c0’ (default), ranging up to `#c0c0ff`
A discrete-valued parameter that's hidden from the faceplate

Number of choices is specified with `?number`. 
2 choices is `Name?2`, 3 choices is `Name?3`, etc.
Default is 2 choices if no `?` is provided

To provide names for the choices, append them to the object name using the `@` separator, instead of the `?`.
Example: `Speed@Low@Medium@High`
The number of choices will be deduced from the number of names given (3 in this case)

The default choice can be specified by adding it to the blue color (zero-based, so `c0` means the first choice).
Example: A 3-choice AltParam (`Name?3` or `Name@low@med@high`) with the default choice of 2 (the last choice) would have a color of `#c0c0c2` 

**Yellow: Misc widget/undefined custom element:**
color is ‘#FFFF00’ or ‘#ff0’ or ‘yellow’

-------------

**Knob sizes:**

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

**Button sizes:**

Big button cap (EnOsc, SMR):
Diameter = 8mm
(or anything > 7mm)
Code: radius > 10

Small button cap (Tapo):
Diameter = 5mm
(or anything < 7mm)
Code: radius < 10

------------

**Switch positions:**

A text name for each switch position can be given using the `@` symbol as a separator.

Example:

A Switch 3-pos object (Faded Orange rectangle) with the name:
`Warp@Segment@Cheb@Fold`
The switch will be displayed as "Warp", and the three positions will be "Segment", "Cheb", and "Fold"


------------

**Class names:**

You can force a particular C++ class to be used for the element by appending `#ClassName` to the object name.
This is normally only done for LEDs, but it works for any object. The script does not check if the class name is 
valid and/or if you provided the right parameters to construct the element.

------------

**Element Names:**

Set the name of each object in AI or Inkscape to the display name.
Example: “Scale CV” (without the quotes).

As described above, you can append switch or AltParam position names to the object name using the `@` separator.
Also as described above, you can force a particular class to be used, by appending `#ClassName`.

There are two text elements required. They both must *not* be converted to outlines (must be editable text):
 
 - Text object with the name “slug”. Text content should be a short identifier (e.g. “SMR” or “EnOsc”)
 - Text object with the name “modulename”. Content is full module name (“Spectral Multiband Resonator”)

--------------

AltParam Linking:

AltParams can link to another element so they appear in that element's context menu.
Or they can be unlinked so they appear in the module's context menu only.
Or they can link to a region on the faceplate.

If the center X,Y coordinates match the X,Y of another object, then it's linked to that object's element.
Otherwise, if center X,Y is 0,0, then it's not linked to any other element or region on the faceplate.
Otherwise it's linked to an invisible region on the faceplate given by the object's position and size.

--------------

**Object Order:**

The order of the components in the layer in the SVG file is the order that they will be scrolled through on hardware 
Therefore, make sure the order makes sense to a user.
Generally, go from top-left to bottom-right, but with common-sense groupings applied.

For example, on something like the SMR's six channel sliders and buttons, either go through all buttons then all sliders,
or go button1-slider1-button2-slider2-etc. But don't go button-FreqKnob-slider1-button2-LFOCV-slider2.

------------

**Export from AI settings:**

File > Export > Export As… > select SVG, uncheck “Use Artboards”

Styling: Inline Style

Font: SVG

Images: Link (doesn’t matter)

Object IDs: Layer Names

Decimal: 2

[unchecked: Minify] [unchecked: Responsive] 
