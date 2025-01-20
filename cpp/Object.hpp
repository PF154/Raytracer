#ifndef OBJECT_H
#define OBJECT_H

#include "Color.hpp"
#include "rt.hpp"
#include "Vec.hpp"

class Object
{
    public:
        Color color;
        bool checker;
        Color color2;

        virtual bool intersect(RAY_T ray, double &t, Vec &int_pt, Vec &normal) {return false;}

        Object *next;
};

#endif