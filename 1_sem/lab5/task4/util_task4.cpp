#include "util_task4.hpp"

Complex::Complex(double r, double i) : real(r), imag(i) {}

Complex Complex::operator+(const Complex &other) const {
    return Complex(real + other.real, imag + other.imag);
}

Complex Complex::operator-(const Complex &other) const {
    return Complex(real - other.real, imag - other.imag);
}

Complex Complex::operator*(const Complex &other) const {
    return Complex(real * other.real - imag * other.imag,
                   real * other.imag + imag * other.real);
}

Complex Complex::operator/(const Complex &other) const {
    double denom = other.real * other.real + other.imag * other.imag;
    if (denom == 0) {
        throw std::runtime_error("Division by zero");
    }

    return Complex((real * other.real + imag * other.imag) / denom,
                   (imag * other.real - real * other.imag) / denom);
}

double Complex::modulus() const {
    return std::sqrt(real * real + imag * imag);
}

double Complex::argument() const {
    return std::atan2(imag, real);
}

void Complex::print() const {
    std::cout << real << (imag >= 0 ? " + " : " - ") << std::abs(imag) << "i";
}
