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

    double sum3(const double values[3]) {
        return values[0] + values[1] + values[2];
    }
};
