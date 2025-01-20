#include "Vec.hpp"

Vec::Vec(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

// Add two vectors per component
Vec Vec::operator+ (Vec other)
{
    Vec sum = Vec(x + other.x, y + other.y, z + other.z);
    return sum;
}

Vec Vec::add(Vec other)
{
    Vec sum = Vec(x + other.x, y + other.y, z + other.z);
    return sum;
}

// Subtract two vectors per component
Vec Vec::operator- (Vec other)
{
    Vec difference = Vec(x - other.x, y - other.y, z - other.z);
    return difference;
}

Vec Vec::sub(Vec other)
{
    Vec difference = Vec(x - other.x, y - other.y, z - other.z);
    return difference;
}

// Multiply two vectors per component
Vec Vec::operator* (Vec other)
{
    Vec product = Vec(x * other.x, y * other.y, z * other.z);
    return product;
}

Vec Vec::mult(Vec other)
{
    Vec product = Vec(x * other.x, y * other.y, z * other.z);
    return product;
}

// Multiply each component of the vector by a scalar
Vec Vec::operator* (double scalar)
{
    Vec product = Vec(x * scalar, y * scalar, z * scalar);
    return product;
}

Vec Vec::scalar_mult(double scalar)
{
    Vec product = Vec(x * scalar, y * scalar, z * scalar);
    return product;
}

// Divide two vectors by component
Vec Vec::operator/ (double scalar)
{
    Vec quotient = Vec(x / scalar, y / scalar, z / scalar);
    return quotient;
}

Vec Vec::scalar_divide(double scalar)
{
    Vec quotient = Vec(x / scalar, y / scalar, z / scalar);
    return quotient;
}

// Set vector with provided values
void Vec::set(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vec::normalize()
{
    double length = this->len();
    this->x = this->x / length;
    this->y = this->y / length;
    this->z = this->z / length;
}

double Vec::sum_components()
{
    return (x + y + z);
}

double Vec::sum_floor_components()
{
    return (double) (floor(x) + floor(y) + floor(z));
}