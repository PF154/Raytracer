#include "Color.hpp"

// Add two colors per component
Color Color::operator+ (Color other)
{
    Color sum = Color(R + other.R, G + other.G, B + other.B);
    return sum;
}

Color Color::add (Color other)
{
    Color sum = Color(R + other.R, G + other.G, B + other.B);
    return sum;
}

// Add a double to each of the components
Color Color::operator+ (double value)
{
    Color sum = Color(R + value, G + value, B + value);
    return sum;
}

Color Color::add (double value)
{
    Color sum = Color(R + value, G + value, B + value);
    return sum;
}

// Multiply each component by a scalar
Color Color::operator* (double scalar)
{
    Color product = Color(R * scalar, G * scalar, B * scalar);
    return product;
}

Color Color::mult_scalar (double scalar)
{
    Color product = Color(R * scalar, G * scalar, B * scalar);
    return product;
}

// Cap the colors at 1.0
void Color::cap ()
{
    if (R > 1.0) R = 1.0;
    if (G > 1.0) G = 1.0;
    if (B > 1.0) B = 1.0;
}