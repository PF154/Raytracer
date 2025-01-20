#ifndef VEC_H
#define VEC_H

#include <math.h>

class Vec
{
    private:
        double x;
        double y;
        double z;

    public:

        // Constructors, initialize values to 0.0 if none are provided
        Vec()  : x(0.0), y(0.0), z(0.0) {};

        Vec(double x, double y, double z);

        void set(double x, double y, double z);

        void normalize();

        inline double dot(Vec other)
        {
            return (this->x * other.x) + (this->y * other.y) + (this->z * other.z);
        }

        inline double len()
        {
            return sqrt(x*x + y*y + z*z);
        }

        Vec operator + (Vec);
        Vec add(Vec);
        Vec operator - (Vec);
        Vec sub(Vec);
        Vec operator * (Vec);
        Vec mult(Vec);
        Vec operator * (double);
        Vec scalar_mult(double);
        Vec operator / (double);
        Vec scalar_divide(double);

        double sum_components();
        double sum_floor_components();

};

#endif