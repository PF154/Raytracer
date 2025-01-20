#ifndef SCENE_H
#define SCENE_H

#include "Object.hpp"

typedef struct {
    Object *objs;
    double start_x;
    double start_y;
    double pixel_size;
} SCENE_T;

#endif