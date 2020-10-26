# Fast3D
##### A quick and simple console 3D renderer.
---

In order to view a model, open it in Blender, triangulate it, then export it by using the provided script in `Blender Models/blender_export.py`. Make sure the object is at (0, 0, 0) (as the center of the screen is considered to be (0, 0)), and also looking down the Z axis. The resulting text file can be used as input.

When the program is run, use W, A, S, D to rotate the model and Q to quit.

Curses is used in order to refresh the console repeatedly.