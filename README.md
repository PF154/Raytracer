# Raytracer

This project contains two implementations of a raytraced image generator made for CSCI 312 - Principles of Programming with Dr. Timothy Davis. Each program reads a file named "scene1.txt" to get information about scene geometry. They can handle spheres, planes, checkered planes, and a single light source.

# Usage

Files should be compiled with gcc/g++. Custom scene files can be written in the format:

Geometry type: s/p/l (char)
Location (for sphere) / Normal Vector (for planes) : x, y, z (floats)
Scale: float
Color: r, g, b (floats, 0.0 <= r, g, b <= 1.0)
Color 2: (for planes, format same as Color)

Examples can be seen in c/scene1.txt
