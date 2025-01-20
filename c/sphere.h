#ifndef SPHERE_H
#define SPHERE_H

#include "rt.h"
#include "vp.h"

int intersect_sphere(RAY_T ray, OBJ_T *obj, double *t, VP_T *int_pt, VP_T *normal);

#endif