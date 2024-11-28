#include "util_task3.hpp"
#include <iostream>

int main() {
    LogicalValuesArray a(1);
    LogicalValuesArray b(0);

    std::cout << "a: " << a.GetValue() << ", b: " << b.GetValue() << '\n';

    std::cout << "a & b: " << a.Conjunction(b).GetValue() << '\n';
    std::cout << "a | b: " << a.Disjunction(b).GetValue() << '\n';
    std::cout << "~a: " << a.Invert().GetValue() << '\n';
    std::cout << "a -> b: " << a.Implication(b).GetValue() << '\n';     //??
    std::cout << "a -< b: " << a.Coimplication(b).GetValue() << '\n';

    std::cout << "a == b: " << (LogicalValuesArray::Equals(a, b) ? "true" : "false") << '\n';

    std::cout << "Bit 2 of a: " << a.GetBit(2) << '\n';

    
    char buffer[33];
    a.ToBinaryString(buffer, sizeof(buffer));
    std::cout << "Binary representation of a:  " << buffer << '\n';
    
    a.Invert().ToBinaryString(buffer, sizeof(buffer));
    std::cout << "Binary representation of ~a: " << buffer << '\n';

    return 0;
}