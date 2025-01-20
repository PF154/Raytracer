#include "vp.h"
#include "math.h"

// Outputs a normalized version of the input vector
VP_T normalize(VP_T vec)
{
    double len = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
    
    VP_T normalized;
    normalized.x = vec.x / len;
    normalized.y = vec.y / len;
    normalized.z = vec.z / len;

    return normalized;
}

// Computes dot product of two vectors
double dot(VP_T vec1, VP_T vec2)
{
    return (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
}

// Returns difference between two VP_T obects
VP_T vp_subtract(VP_T vec1, VP_T vec2)
{
    VP_T difference;
    difference.x = vec1.x - vec2.x;
    difference.y = vec1.y - vec2.y;
    difference.z = vec1.z - vec2.z;

    return difference;
}