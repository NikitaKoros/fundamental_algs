#include "util_task1.hpp"
#include <climits>
int main() {
    BinaryInt a(-0), b(-1);

    std::cout << "a: " << a << "\n";
    std::cout << "b: " << b << "\n";

    BinaryInt c = a + b;
    std::cout << "a + b: " << c << "\n";

    BinaryInt d = a - b;
    std::cout << "a - b: " << d << "\n";

    BinaryInt e = a * b;
    std::cout << "a * b: " << e << "\n";

    ++a;
    std::cout << "++a: " << a << "\n";

    b--;
    std::cout << "b--: " << b << "\n";

    auto [high, low] = a.SplitBits();
    std::cout << "High bits of a: " << high << "\n";
    std::cout << "Low bits of a: " << low << "\n";

    return 0;
}
