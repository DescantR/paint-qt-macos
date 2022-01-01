EasyPaint
=========

EasyPaint is a simple graphics painting program. This program is like MS Paint, but nice, lightweight and cross-platform. The Makefile in this fork is specifically for MacOS, but it can be adapted for any OS since QT is a cross-platform framework.

EasyPaint is a part of QtDesktop project and [Razor-qt's](https://github.com/Razor-qt) [3rd party applications](https://github.com/Razor-qt/razor-qt/wiki/3rd-party-applications).

Changes
-------
* Uses GNU make
* Ported to QT 6

Installing
----------

Install EasyPaint (simplified as paint.app for easier path & spotlight) using brew and GNU make

    brew install qt
    make clean macbundle

I've also provided paint.app, but `brew install qt` is currently mandatory.

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
* Alpha in color picker
  * Alpha should affect fill operations
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
* Tool to recolor to sharp black and white from selection
* Tool to recolor black to custom from selection
* Option to crop canvas to selection in Canvas size tool
* Canvas size changes should reflect in undo history
* Color picker selection should reflect in undo history
  * Changing color using swatches should also add to undo history
  * bug: Changing colors before using the canvas adds to undo history but can't be undone until some change is made to the canvas - mIsEdited?
* bug: Closing, clicking save, then canceling should not close without saving
* Right click should be meaningful on swatch, color picker and fill
* Ellipse and Rect tools should observe Shift for perfect shapes and swatches for fill
  * Swatches should contain a 'no fill' option that makes certain instruments behave differently
  * Eraser and delete should default to white if 'no fill' is selected

License
-------

EasyPaint by [Gr1N](https://github.com/Gr1N/EasyPaint) was originally distributed under the [MIT license](http://www.opensource.org/licenses/MIT).
I haven't spent enough time on licensing and naming to be sure that this repo is A-OK. Please let me know if there's anything I should fix.
