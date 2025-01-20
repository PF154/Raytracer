#ifndef VP_H
#define VP_H

typedef struct {
    double x;
    double y;
    double z;
} VP_T;

VP_T normalize(VP_T vec);

double dot(VP_T vec1, VP_T vec2);

VP_T vp_subtract(VP_T vec1, VP_T vec2);

#endif