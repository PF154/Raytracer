#ifndef SPHERE_H
#define SPHERE_H

#include "Object.hpp"
#include "Vec.hpp"
#include "Color.hpp"
#include "rt.hpp"

class Sphere: public Object
{
    private: 
        Vec center;
        double radius;
        
    public:
        Sphere(Vec center, double radius, Color color, bool checker, Color color2);

        bool intersect(RAY_T ray, double &t, Vec &int_pt, Vec &normal);
};

#endif