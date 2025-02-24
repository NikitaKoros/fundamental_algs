#include <iostream>

#include "util_task4.hpp"

int main() {
    Complex c1(12.3, 45.6);
    Complex c2(-65.4, -32.1);

    std::cout << "Complex number 1: ";
    c1.print();
    std::cout << "\nComplex number 2: ";
    c2.print();

    Complex sum = c1 + c2;
    std::cout << "\n\nSum: ";
    sum.print();

    Complex diff = c1 - c2;
    std::cout << "\nDifference: ";
    diff.print();

    Complex product = c1 * c2;
    std::cout << "\nProduct: ";
    product.print();

    try {
        Complex quotient = c1 / c2;
        std::cout << "\nQuotient: ";
        quotient.print();
    } catch (const std::runtime_error& e) {
        std::cout << "\nDivision error: " << e.what();
    }

    std::cout << "\n\nModulus of c1: " << c1.modulus();
    std::cout << "\nArgument of c1: " << c1.argument() << " radians\n";

    return 0;
}
