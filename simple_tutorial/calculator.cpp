// math_example.cpp
#include <cmath>

class Calculator {
public:
    double add(double a, double b) {
        return a + b;
    }
    
    double multiply(double a, double b) {
        return a * b;
    }
    
    double power(double base, double exponent) {
        return pow(base, exponent);
    }
    
    double squareRoot(double value) {
        return sqrt(value);
    }
};
