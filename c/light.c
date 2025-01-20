#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "vp.h"
#include "rt.h"

/* This function takes in a light location, intersect point, list of objects
    and current object, and returns a 1 if a shadow should be cast (0 otherwise). */
static int shadow_test(VP_T light_loc, VP_T int_pt, OBJ_T *objs, OBJ_T* obj)
{
    // Create ray from int_pt to light
    VP_T shadow_vec = vp_subtract(light_loc, int_pt);

    RAY_T shadow_ray;
    shadow_ray.dir = normalize(shadow_vec);
    shadow_ray.origin = int_pt;

    // Iterate over every object in the linked list
    OBJ_T *curr;
    for (curr = objs; curr != NULL; curr = curr->next)
    {
        // If our object is not the one we are illuminating, check if it's blocking light
        if (curr != obj)
        {
            double t;
            VP_T int_pt2;
            VP_T normal;
            if (curr->intersect(shadow_ray, curr, &t, &int_pt2, &normal)) 
            {
                return 1;
            }
        }
    }
    
    return 0;
}

/* This function takes a point in 3D space and calculates the appropriate lighting for it
   based on its object color, normal, and light location and adds specular highlighting based
   on the direction of the input ray. */
COLOR_T illuminate(OBJ_T *obj, VP_T int_pt, VP_T normal, RAY_T ray, VP_T light_loc, OBJ_T *objs)
{
    // printf("Input color: %lf, %lf, %lf\n", obj_color.R, obj_color.G, obj_color.B);

    COLOR_T obj_color = obj->color;
    if (obj->checker && ((int)floor(int_pt.x) + (int)floor(int_pt.y) + (int)floor(int_pt.z)) & 1)
    {
        obj_color = obj->color_2;
    }

    VP_T diff = vp_subtract(int_pt, light_loc);
    double dL = sqrt(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);

    double atten = 1/(0.002 * dL * dL + 0.02 * dL + .2);

    // We start with the ambeint value of the color. This is what it get's if there is no direct light
    COLOR_T color;
    color.R = 0.1 * obj_color.R;
    color.G = 0.1 * obj_color.G;
    color.B = 0.1 * obj_color.B;

    // If the intersect point is not in shadow, then add diffuse and specular lighting
    if (!shadow_test(light_loc, int_pt, objs, obj))
    {
        // Light vector L points from int_pt to light
        VP_T L;
        L.x = light_loc.x - int_pt.x;
        L.y = light_loc.y - int_pt.y;
        L.z = light_loc.z - int_pt.z;

        // We want an angle theta between our normal vector and our light vector
        // Then we want the cosine of that angle
        // We'll use dot product to do this, normalizing the normal and L vectors first
        VP_T L_norm = normalize(L);

        double dp = dot(L_norm, normal);

        // If dp is greater than zero, the point should recieve diffuse lighting
        if(dp > 0)
        {
            // We add diffuse lighting to the color with intensity based on dot product
            color.R += dp * obj_color.R * atten;
            color.G += dp * obj_color.G * atten;
            color.B += dp * obj_color.B * atten;

            // Create vector R, a ray reflected around the normal
            VP_T R;
            R.x = L_norm.x - normal.x * 2 * dp;
            R.y = L_norm.y - normal.y * 2 * dp;
            R.z = L_norm.z - normal.z * 2 * dp;

            // We add specular highlighting based on the value of dp2
            double dp2 = dot(normalize(R), ray.dir);
            if (dp2 > 0)
            {
                color.R += pow(dp2, 200) * atten;
                color.G += pow(dp2, 200) * atten; 
                color.B += pow(dp2, 200) * atten;
            }
        }
    }

    // We cap the colors in case they exceed the max value
    if (color.R > 1.0) color.R = 1.0;
    if (color.G > 1.0) color.G = 1.0;
    if (color.B > 1.0) color.B = 1.0;

    return color;
}