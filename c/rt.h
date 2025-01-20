#ifndef RT_H
#define RT_H

#include "vp.h"

typedef struct {
    VP_T origin;
    VP_T dir;
} RAY_T;

typedef struct {
    double R;
    double G;
    double B;
} COLOR_T;

typedef struct {
    VP_T center;
    double radius;
    COLOR_T color;
} SPHERE_T;

typedef struct {
    VP_T normal;
    double distance;
} PLANE_T;

typedef struct {
    VP_T loc;
} LIGHT_T;

typedef struct OBJ {
    union {
        SPHERE_T sphere;
        PLANE_T plane;
    };
    char type;
    COLOR_T color;
    int checker;
    COLOR_T color_2;
    int (*intersect) (RAY_T ray, struct OBJ *obj, double *t, VP_T *int_pt, VP_T *normal);
    struct OBJ *next;
} OBJ_T;

typedef struct {
    OBJ_T *objs;
    LIGHT_T light;
    double start_x;
    double start_y;
    double pixel_size;
} SCENE_T;

#endif