/* RAYTRACER C++
   Peter Forsberg
   12/6/24
   This program takes in a scene file containing information about planes, spheres, and a light and
   creates a raytraced image.
*/


#include <iostream>
#include <stdio.h>
#include "Vec.hpp"
#include "scene.hpp"
#include "Sphere.hpp"
#include "Color.hpp"
#include "Plane.hpp"
#include "Light.hpp"
#include "Object.hpp"

/* This function takes in a ray, light, and scene and returns the appropriate 
   color for pixel associated with the given ray.*/
static Color trace(RAY_T ray, Light light, SCENE_T scene)
{
    // Default color for the background
    Color color = Color(0.3, 0.3, 0.5);
    
    // Variables to store data from intersect
    double t;
    Vec int_pt;
    Vec normal;

    // Variables to keep track of closest object so far
    Object *curr;
    double closest_t = 1000;
    Vec closest_int_pt;
    Vec closest_normal;
    Object* closest_obj = NULL;

    // If we find an intersection, we store it's information
    for (curr = scene.objs; curr != NULL; curr = curr->next)
    {

        if (curr->intersect(ray, t, int_pt, normal)) {
            if (t < closest_t)
            {
                closest_t = t;
                closest_int_pt = int_pt;
                closest_normal = normal;
                closest_obj = curr;
            }
        }
    }

    // If we found an intersection, return the appropriate color
    if (closest_obj)
    {
        color = light.illuminate(ray, scene, closest_obj, closest_int_pt, closest_normal);
    }
    
    return color;
}

/* Takes in a scene and light by reference and assigns them the appropriate
   information from the scene file. */
static void init(SCENE_T &scene, Light &scene_light)
{
    FILE *fp;
    fp = fopen("scene1.txt", "r");
    char type;
    scene.objs = NULL;
    while(fscanf(fp, "%c", &type) != EOF)
    {
        if(type == 's')
        {
            // Read necessary info for sphere
            double ctr_x, ctr_y, ctr_z;
            fscanf(fp, "%lf %lf %lf", &ctr_x, &ctr_y, &ctr_z);

            double rad;
            fscanf(fp, "%lf", &rad);

            double R, G, B;
            fscanf(fp, "%lf %lf %lf", &R, &G, &B);

            Sphere *node = new Sphere(Vec(ctr_x, ctr_y, ctr_z), rad, Color(R, G, B), false, Color(0.0 ,0.0, 0.0));

            // Link into scene
            node->next = scene.objs;
            scene.objs = node;
        }
        else if (type == 'p')
        {
            // Read necessary info for plane
            double nml_x, nml_y, nml_z;
            fscanf(fp, "%lf %lf %lf", &nml_x, &nml_y, &nml_z);

            double dist;
            fscanf(fp, "%lf", &dist);

            double R, G, B;
            fscanf(fp, "%lf %lf %lf", &R, &G, &B);

            double R2, G2, B2;
            fscanf(fp, "%lf %lf %lf", &R2, &G2, &B2);

            Plane *node = new Plane(Vec(nml_x, nml_y, nml_z), dist, Color(R, G, B), true, Color(R2, G2, B2));

            // Link into scene
            node->next = scene.objs;
            scene.objs = node;
        }
        else if (type == 'l')
        {
            // Read necessary info for plane
            double light_x, light_y, light_z;
            fscanf(fp, "%lf %lf %lf", &light_x, &light_y, &light_z);
            scene_light = Light(Vec(light_x, light_y, light_z));
        }
    }
}

int main()
{
    SCENE_T scene;
    // Initialize light to 0,0,0, this will be changed in init
    Light scene_light = Light(Vec(0.0, 0.0, 0.0));
    init(scene, scene_light);

    // Image size settings
    scene.pixel_size = 1.0/480;
    scene.start_x = -(640/480.0)/2.0;
    scene.start_y = 0.5;

    FILE *fp;
    fp = fopen("img.ppm", "w");

    // Init ppm file header
    fprintf(fp, "P6\n");
    fprintf(fp, "640 480\n");
    fprintf(fp, "255\n");

    // Iterate over every pixel
    for (int y = 0; y <= 479; y++)
    {   
        for (int x = 0; x <= 639; x++)
        {   
            // Calculate coordinates corresponding to where each ray should point
            double x3D = scene.start_x + (x * scene.pixel_size);
            double y3D = scene.start_y - (y * scene.pixel_size);
            double z3D = 1.0;

            // Set up a ray from the center of the screen to the previously calculated point
            RAY_T ray;
            ray.origin = Vec(0.0, 0.0, 0.0);
            ray.dir = Vec(x3D, y3D, z3D);

            // Nomormalize the ray direction vector before we do any more calculations
            ray.dir.normalize();

            // Calculate the appropriate color and output it to file
            Color color = trace(ray, scene_light, scene);
            fprintf(fp, "%c%c%c", (unsigned char)(color.getR()*255), (unsigned char)(color.getG()*255), (unsigned char)(color.getB()*255));
        }
    }
    return 0;
}