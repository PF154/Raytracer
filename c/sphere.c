#include <math.h>
#include <stdio.h>

#include "rt.h"
#include "vp.h"

/* Detects if there is an intersection between ray and the sphere.
   If there is an intersection, the function returns 1 and fills t, int_pt, and normal
   with their respective values. If there is no intersection, the funciton returns 0. */
int intersect_sphere(RAY_T ray, OBJ_T *obj, double *t, VP_T *int_pt, VP_T *normal)
{
    // Values for quadratic calculation
    double A = 1.0;
    double B = 2.0 * (ray.dir.x * (ray.origin.x - obj->sphere.center.x) + 
                      ray.dir.y * (ray.origin.y - obj->sphere.center.y) +
                      ray.dir.z * (ray.origin.z - obj->sphere.center.z));
    double C = (ray.origin.x - obj->sphere.center.x) * (ray.origin.x - obj->sphere.center.x) +
               (ray.origin.y - obj->sphere.center.y) * (ray.origin.y - obj->sphere.center.y) +
               (ray.origin.z - obj->sphere.center.z) * (ray.origin.z - obj->sphere.center.z) - 
               obj->sphere.radius * obj->sphere.radius;

    // Check discriminant to see if we actually have two intersections.
    // If we only have 1 or zero, then return zero; We didn't find anything.
    double disc = (B * B) - (4.0 * A * C);
    if (disc <= 0)
    {
        return 0;
    }

    // If we make it here, we have an intersection.
    double t1 = (-B + sqrt(disc)) / (2 * A);
    double t2 = (-B - sqrt(disc)) / (2 * A);
    
    // Now we want to pick the smaller positive intersection point
    if (t1 <= 0)
    {
        if (t2 > 0)
        {
            *t = t2;
        } 
        else
        {
            return 0;
        }
    }
    else if (t2 <= 0)
    {
        *t = t1;
    }
    else
    {
        // t should be the smallest of the two
        if (t1 < t2)
        {
            *t = t1;
        }
        else
        {
            *t = t2;
        }
    }

    
    // Calculate intersection point
    (*int_pt).x = ray.origin.x + *t * ray.dir.x;
    (*int_pt).y = ray.origin.y + *t * ray.dir.y;
    (*int_pt).z = ray.origin.z + *t * ray.dir.z;

    // Calculate the normal vector
    VP_T center_to_int;
    center_to_int.x = (*int_pt).x - obj->sphere.center.x;
    center_to_int.y = (*int_pt).y - obj->sphere.center.y;
    center_to_int.z = (*int_pt).z - obj->sphere.center.z;
    *normal = normalize(center_to_int);

    return 1;

}