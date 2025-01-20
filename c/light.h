#ifndef LIGHT_H
#define LIGHT_H

#include "rt.h"
#include "vp.h"

COLOR_T illuminate(OBJ_T *obj, VP_T int_pt, VP_T normal, RAY_T ray, VP_T light_loc, OBJ_T *objs);

#endif