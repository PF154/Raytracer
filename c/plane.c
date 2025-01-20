#include <math.h>

#include "rt.h"
#include "vp.h"

/* Takes in a ray and object and determines whether there is an intersection point.
    If so, fills values into t (distance), int_pt, and normal and returns 1.
    If not, returns 0.*/
int intersect_plane(RAY_T ray, OBJ_T *obj, double *t, VP_T *int_pt, VP_T *normal)
{
    double dp = dot(obj->plane.normal, ray.dir);

    if (dp == 0)
    {
        return 0;
    }
    
    *t = - (dot(obj->plane.normal, ray.origin) + obj->plane.distance) / dp;
    if (*t < 0)
    {
        return 0;
    }

    (*int_pt).x = ray.origin.x + *t * ray.dir.x;
    (*int_pt).y = ray.origin.y + *t * ray.dir.y;
    (*int_pt).z = ray.origin.z + *t * ray.dir.z;

    *normal = obj->plane.normal;

    return 1;
}