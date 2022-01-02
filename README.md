EasyPaint
=========

EasyPaint is a simple graphics painting program. This program is like MS Paint, but nice, lightweight and cross-platform. The Makefile in this fork is specifically for MacOS, but it can be adapted for any OS since QT is a cross-platform framework.

![Screenshot](/res/Screenshot.png)

EasyPaint is a part of QtDesktop project and [Razor-qt's](https://github.com/Razor-qt) [3rd party applications](https://github.com/Razor-qt/razor-qt/wiki/3rd-party-applications).

Changes
-------
* Uses GNU make
* Ported to QT 6
* Pretty UI
* Supports alpha in colors

Installing
----------

Install EasyPaint (simplified as paint.app for easier path & spotlight) using brew and GNU make

    brew install qt
    make clean macbundle

I've also provided paint.app in releases, but `brew install qt` is currently mandatory.

Usage tip
---------

Use Command + Control + Shift + 4 to screengrab into your clipboard, then Command + V to paste. Couple with Command + N for a quick new canvas if required. 

Wishlist
--------
It's my first project but I intend to do as many of these as possbile.

* Escape button should deselect
* Some way to use simple transform features on the selection
  * Rotation
  * Scaling
  * Tilting
* ~~Alpha in color picker~~
  * ~~Alpha should affect fill operations~~
  * ~~Color Picker should show blended color~~
  * Brush should not be dotty in alpha mode
* Delete button should set the selection to color 2
* Add visual grid option, with custom grid unit
  * A smart default grid unit should be chosen
* Versatile selection movement (arrows, shift, alt, control)
  * Selection is visible while moving
  * Arrows, move pixel at a time
  * Arrows and Shift, move based on flat 'grid unit' size (no need for velocity)
  * Shift and mouse, move snapped to axis
  * Control and mouse, move copy
  * Control Shift and mouse, axis-snapped move copy
  * Alt and mouse, 'drag move' copy (redraw the edge pixels as the selection is dragged)
  * Alt Shift and mouse, axis-snapped 'drag move' copy
* Arrowhead options for line tool
* Line tool should snap to horizontal and vertical axis if shift is pressed
* Default canvas and window size should be smarter
* New canvas size should be prefilled based on the active view
* Command A should select all
* Rotate should function on selection, not canvas
* Pencil and Eraser should have a 'grid unit' size option
* Vertical and Horizontal mirror options (on selection)
* Bundle separate scripts to convert multipage PDF -> PNG and back (convenience only)
  * Consider making it a tool instead of conveience scripts (tool to save into multiple files with open and dest prompts)
  * Tool to export to PDF with configurable ghostscript parts, optimised defaults
* Info about modifier button actions in hover tooltips
* Info about page <-> DPI <-> A4 in both PDF export and new.. options
* Control click with selection makes custom selection area polygon
* Tool to recolor to sharp black and white from selection
* Tool to recolor black to custom from selection
* Option to crop canvas to selection in Canvas size tool
* Canvas size changes should reflect in undo history
* Display canvas in fullscreen, preferences for 'fill' (shortest edge), 'fit' (longest), 'resize' (stretch), or '100% center' (black border aligned center)
  * Consider allowing current brush primary and secondary pair while in fullscreen
  * Consider allowing text shortcut while in fullscreen
* Tool to play gif in fullscreen
* ~~Color picker selection should reflect in undo history~~
  * ~~Changing color using swatches should also add to undo history~~
  * bug: Changing colors before using the canvas adds to undo history but can't be undone until some change is made to the canvas - mIsEdited?
  * unchecked: Transparent background handling - if a png with no background is loaded, what happens to fill and blended brush
* Better icons and toolbar frames - remove pencil from icons, hovering changes color and displays multiline tooltip with shortcut and modifier options
* Better tabs - left align and square
* Better default for brush size, based on DPI
* Rework the curve tool to be usable
* bug: Closing, clicking save, then canceling should not close without saving
* Right click should be meaningful on swatch, color picker and fill
* Ellipse and Rect tools should observe Shift for perfect shapes and swatches for fill
  * Swatches should contain a 'no fill' option that makes certain instruments behave differently
  * Eraser and delete should default to white if 'no fill' is selected
* Command click on swatches should allow for color choosing to swatch color
  * Shift click on swatch should replace/blend all secondary color with swatch color
* Tool to 'grow' canvas, by padding edges
* Button to swap swatch color

License
-------

EasyPaint by [Gr1N](https://github.com/Gr1N/EasyPaint) was originally distributed under the [MIT license](http://www.opensource.org/licenses/MIT).
I haven't spent enough time on licensing and naming to be sure that this repo is A-OK. Please let me know if there's anything I should fix.
