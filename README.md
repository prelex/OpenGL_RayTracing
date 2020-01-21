# OpenGL_RayTracing

After reading the chapter on ray tracing from the book *Mathematics for 3D Game Programming and Computer Graphics* by Eric Lengyel, I wanted to try and create a very simple OpenGL program to apply some of the concepts.

This program is a simple application of determining whether a ray strikes a triangle in a 3D scene. It features a ray emanating from the camera's position along the direction in which the camera is facing, and a single triangle. If the ray intersects the triangle, the the triangle will get brighter and a red "laser dot" will be seen on the triangle, corresponding to the position where the ray strikes the triangle.

**Controls:** Use W, A, S and D to move, and the mouse to change the direction the camera is facing.
