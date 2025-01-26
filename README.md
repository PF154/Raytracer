# Raytracer

This project contains two implementations of a raytraced image generator made for CSCI 312 - Principles of Programming with Dr. Timothy Davis. Each program reads a file named "scene1.txt" to get information about scene geometry. They can handle spheres, planes, checkered planes, and a single light source.

Below is a sample image created with this raytracer—a space-filling model of glucose.


![An image of a space-filling model of glucose, rendered with this raytracer](/glucose.png)

# Usage

Files should be compiled with gcc/g++. 

For C++:
```
g++ Color.cpp Light.cpp Main.cpp Plane.cpp Sphere.cpp Vec.cpp
```
For C:
```
gcc rt.c light.c plane.c sphere.c vp.c -lm
```

Custom scene geometry files can be written in the format:

```
Geometry type: s/p/l (char)
Location (for sphere) / Normal Vector (for planes) : x, y, z (floats)
Scale: float
Color: r, g, b (floats, 0.0 <= r, g, b <= 1.0)
Color 2: (for planes, format same as Color)
```

Examples can be seen in c/scene1.txt

# Lessons Learned

This project was great practice in many fundamental C++ features, but what I took away from it the most was the experience I gained using virtual methods and pure virtual classes. These sorts of object-oriented features have been quintessential in my most recent project—a custom programming language interpreter—which I will add soon to my portfolio.
