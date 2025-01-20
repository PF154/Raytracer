#ifndef COLOR_H
#define COLOR_H

class Color
{
    private:
        double R;
        double G;
        double B;

    public:
        // If no arguments are given, default to 0.0, 0.0, 0.0
        Color() : R(0.0), G(0.0), B(0.0) {};

        Color(double Red, double Green, double Blue)
        {
            this->R = Red;
            this->G = Green;
            this->B = Blue;
        }

        // Getters for color components
        inline double getR() {return R;}
        inline double getG() {return G;}
        inline double getB() {return B;}
        
        Color operator + (Color);
        Color add(Color);
        Color operator + (double);
        Color add(double);
        Color operator * (double);
        Color mult_scalar(double);

        void cap (void);

};

#endif