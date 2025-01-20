#include "Sphere.hpp"
#include "Vec.hpp"
#include "Color.hpp"
#include "rt.hpp"

// Constructor
Sphere::Sphere(Vec center, double radius, Color color, bool checker, Color color2)
{
    this->center = center;
    this->radius = radius;
    this->color = color;
    this->checker = checker;
    this->color2 = color2;
}

/* Returns true if the ray intersects the sphere, false if it does not. Assigns values of
   t, int_pt, and normal to appropriate variables. */
bool Sphere::intersect(RAY_T ray, double &t, Vec &int_pt, Vec &normal)
{
    double A = 1.0;
    double B = 2.0 * (ray.dir * (ray.origin - center)).sum_components();
    double C = ((ray.origin - center) * (ray.origin - center)).sum_components() - (radius * radius);

    // If discriminant is 0, we don't have an intersection
    double disc = (B * B) - (4.0 * A * C);
    if (disc <= 0)
    {
        return false;
    }

    double t1 = (-B + sqrt(disc)) / (2 * A);
    double t2 = (-B - sqrt(disc)) / (2 * A);

    // Now we want to pick the smaller positive intersection point
    if (t1 <= 0)
    {
        if (t2 > 0)
        {
            t = t2;
        } 
        else
        {
            return false;
        }
    }
    else if (t2 <= 0)
    {
        t = t1;
    }
    else
    {
        // t should be the smallest of the two if both are positive
        if (t1 < t2)
        {
            t = t1;
        }
        else
        {
            t = t2;
        }
    }

    // Calculate intersection point
    int_pt = ray.origin + (ray.dir * t);

    // Calculate the normal vector
    Vec center_to_int = int_pt - center;
    center_to_int.normalize();
    normal = center_to_int;

    return true;
}