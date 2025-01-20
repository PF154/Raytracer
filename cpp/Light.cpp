#include "Light.hpp"
#include "Color.hpp"
#include "Object.hpp"

Light::Light(Vec loc)
{
    this->loc = loc;
}

/* This function returns false if the ray from the light to the int_pt does
   not intersect anything else, true if it does. */
bool Light::shadow_test(SCENE_T scene, Object* obj, Vec int_pt)
{
    // Create ray from int_pt to light
    Vec shadow_vec = loc - int_pt;
    shadow_vec.normalize();
    // Vec shadow_vec = loc.sub(int_pt);

    RAY_T shadow_ray;
    shadow_ray.dir = shadow_vec;
    shadow_ray.origin = int_pt;

    // Iterate over every object in the linked list
    Object *curr;
    for (curr = scene.objs; curr != NULL; curr = curr->next)
    {
        // If our object is not the one we are illuminating, check if it's blocking light
        if (curr != obj)
        {
            double t;
            Vec int_pt2;
            Vec normal;
            // Return true if object intersects ray
            if (curr->intersect(shadow_ray, t, int_pt2, normal)) 
            {
                return true;
            }
        }
    }
    
    // Return false if there is no shadow
    return false;
}


/* This function takes a ray, scene, object index, intersection point, and normal vector
   and returns the appropriate color at the intersection point. */
Color Light::illuminate(RAY_T ray, SCENE_T scene, Object* obj, Vec int_pt, Vec normal)
{
    // Use the secondary color if we are using checkering
    Color obj_color = obj->color;
    if (obj->checker && (int)(int_pt.sum_floor_components()) & 1)
    {
        obj_color = obj->color2;
    }

    Vec diff = int_pt - loc;
    double dL = diff.len();

    double atten = 1/(0.002 * dL * dL + 0.02 * dL + .2);

    // We start with the ambeint value of the color. This is what it get's if there is no direct light
    Color color = obj_color * 0.1;

    // If the intersect point is not in shadow, then add diffuse and specular lighting
    if (!shadow_test(scene, obj, int_pt))
    {
        // Light vector L points from int_pt to light
        Vec L = loc - int_pt;

        // We want an angle theta between our normal vector and our light vector
        // Then we want the cosine of that angle
        // We'll use dot product to do this, normalizing the normal and L vectors first
        L.normalize();

        double dp = L.dot(normal);

        // If dp is greater than zero, the point should recieve diffuse lighting
        if(dp > 0)
        {
            // We add diffuse lighting to the color with intensity based on dot product
            color = color + ((obj_color * dp) * atten);
            // color = color.add(obj_color.mult_scalar(dp) * atten);

            // Create vector R, a ray reflected around the normal
            Vec R = L - (normal * 2 * dp);
            // Vec R = L_norm.sub(normal.scalar_mult(2 * dp));

            // We add specular highlighting based on the value of dp2
            R.normalize();
            double dp2 = R.dot(ray.dir);
            if (dp2 > 0)
            {
                color = color + (pow(dp2, 200) * atten);
                // color = color.add(pow(dp2, 200) * atten);
            }
        }
    }

    // We cap the colors in case they exceed the max value
    color.cap();

    return color;
}