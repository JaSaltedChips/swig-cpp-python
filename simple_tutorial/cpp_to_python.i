%module rechner

%{
#include "calculator.cpp"
%}

class Calculator {
public:
    double add(double a, double b);
    double multiply(double a, double b);
    double power(double base, double exponent);
    double squareRoot(double value);
};
