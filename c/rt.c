/* RAYTRACER PROJECT
   Peter Forsberg
   10/8/2024
   This program draws an image of a red sphere in ppm format using raytracting.*/

#include "rt.h"
#include "sphere.h"
#include "plane.h"
#include "light.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* This function takes in a ray, sphere, and light location and returns
   the appropriate color for the final image. */
static COLOR_T trace(RAY_T ray, SCENE_T scene, VP_T light_loc)
{   
    // Default color for the background
    COLOR_T color;
    COLOR_T bg;
    color.R = 0.3;
    color.G = 0.3;
    color.B = 0.5;
    
    // Variables to store data from intersect
    double t;
    VP_T int_pt;
    VP_T normal;

    // If we find an intersection, we calculate the right color and return it
    OBJ_T *curr;
    double closest_t = 1000;
    VP_T closest_int_pt;
    VP_T closest_normal;
    OBJ_T *closest_obj = NULL;


    for (curr = scene.objs; curr != NULL; curr = curr->next)
    {

        if (curr->intersect(ray, curr, &t, &int_pt, &normal)) {
            if (t < closest_t)
            {
                closest_t = t;
                closest_int_pt = int_pt;
                closest_normal = normal;
                closest_obj = curr;
            }
        }
    }
    if (closest_obj)
    {
        color = illuminate(closest_obj, closest_int_pt, closest_normal, ray, light_loc, scene.objs);
    }
    
    return color;
}

/* Takes in a pointer to a scene and a filepath and creates a scene type for later use. */
static void init(SCENE_T *scene, char *path)
{
    // space between control characters (%lf)
    // fp points to a position in a file
    FILE *fp;
    fp = fopen(path, "r");
    
    char type;
    scene->objs = NULL;
    while(fscanf(fp, "%c", &type) != EOF)
    {
        // Create a new object and link it into the scene, allocating space as necessary
        if(type == 's')
        {
            // sphere stuff
            OBJ_T *node;
            node = (OBJ_T*)malloc(sizeof(OBJ_T));
            node->intersect = intersect_sphere;
            node->type = 's';
            node->checker = 0;
            fscanf(fp, "%lf %lf %lf", &(node->sphere.center.x), &(node->sphere.center.y), &(node->sphere.center.z));
            fscanf(fp, "%lf", &(node->sphere.radius));
            fscanf(fp, "%lf %lf %lf", &(node->color.R), &(node->color.G), &(node->color.B));
            node->next = scene->objs;
            scene->objs = node;
        }
        else if (type == 'p')
        {
            // plane stuff
            OBJ_T *node;
            node = (OBJ_T*)malloc(sizeof(OBJ_T));
            node->intersect = intersect_plane;
            node->type = 'p';
            node->checker = 1;
            fscanf(fp, "%lf %lf %lf", &(node->plane.normal.x), &(node->plane.normal.y), &(node->plane.normal.z));
            fscanf(fp, "%lf", &(node->plane.distance));
            fscanf(fp, "%lf %lf %lf", &(node->color.R), &(node->color.G), &(node->color.B));
            fscanf(fp, "%lf %lf %lf", &(node->color_2.R), &(node->color_2.G), &(node->color_2.B));
            node->next = scene->objs;
            scene->objs = node;
        }
        else if (type == 'l')
        {
            // light stuff
            fscanf(fp, "%lf %lf %lf", &(scene->light.loc.x), &(scene->light.loc.y), &(scene->light.loc.z));
        }
    }
}

/* Inside main, we initialize necessary elements of the image, iterate over every pixel
   and output the correct color per pixel. */
int main()
{
    SCENE_T scene;
    init(&scene, "scene1.txt");

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
            ray.origin.x = 0.0;
            ray.origin.y = 0.0;
            ray.origin.z = 0.0;
            ray.dir.x = x3D;
            ray.dir.y = y3D;
            ray.dir.z = z3D;

            // Nomormalize the ray direction vector before we do any more calculations
            ray.dir = normalize(ray.dir);

            // Output the appropriate color to stdout
            COLOR_T color = trace(ray, scene, scene.light.loc);
            fprintf(fp, "%c%c%c", (unsigned char)(color.R*255), (unsigned char)(color.G*255), (unsigned char)(color.B*255));
        }
    }
    return 0;
}