#ifndef TASK1_HPP
#define TASK1_HPP

#include <cmath>
#include <iostream>

class Complex {
   private:
    double real;
    double imag;

   public:
    Complex(double r = 0.0, double i = 0.0);
    
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;

    double modulus() const;
    double argument() const;

    void print() const;
};

#endif
