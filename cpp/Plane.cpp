#include "Plane.hpp"
#include "rt.hpp"
#include "Color.hpp"
#include "Vec.hpp"

// Constructor
Plane::Plane(Vec normal, double distance, Color color, bool checker, Color color2)
{
    this->normal = normal;
    this->distance = distance;
    this->color = color;
    this->checker = checker;
    this->color2 = color2;
}

/* Returns true if the ray intersects the plane, false if it does not. Assigns values of
   t, int_pt, and normal to appropriate variables. */
bool Plane::intersect(RAY_T ray, double &t, Vec &int_pt, Vec &normal)
{
    double dp = this->normal.dot(ray.dir);

    if (dp == 0)
    {
        return false;
    }
    

    t = -(this->normal.dot(ray.origin) + this->distance) / dp;
    if (t < 0)
    {
        return false;
    }

    int_pt = ray.origin + (ray.dir * t);
    normal = this->normal;

    return true;
}