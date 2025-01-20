#ifndef PLANE_H
#define PLANE_H

#include "Vec.hpp"
#include "Color.hpp"
#include "rt.hpp"
#include "Object.hpp"

class Plane : public Object
{
    private:
        Vec normal;
        double distance;

    public:
        Plane(Vec normal, double distance, Color color, bool checker, Color color2);

        bool intersect(RAY_T ray, double &t, Vec &int_pt, Vec &normal);
};

#endif