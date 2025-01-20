#ifndef LIGHT_H
#define LIGHT_H

#include "Vec.hpp"
#include "scene.hpp"
#include "Object.hpp"

class Light
{
    private:
        Vec loc;

        // Check if the ray between the light and int_pt intersects another object
        bool shadow_test(SCENE_T scene, Object* obj, Vec int_pt);

    public:
        Light(Vec loc);

        // Calculate the color for a given int_pt
        Color illuminate(RAY_T ray, SCENE_T scene, Object* obj, Vec int_pt, Vec normal);

};

#endif