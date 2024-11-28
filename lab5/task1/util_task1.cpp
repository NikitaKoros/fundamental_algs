#include "util_task1.hpp"

BinaryInt::BinaryInt() : value(0) {}
BinaryInt::BinaryInt(int v) : value(v) {}

int BinaryInt::Add(int a, int b) {
    while (b != 0) {
        int carry = a & b; // вычисляем перенос
        a = a ^ b; // складываем без учета переноса
        b = carry << 1; 
    }
    return a;
}

int BinaryInt::Subtract(int a, int b) { //TODO  const
    return Add(a, Add(~b, 1));
}

int BinaryInt::Multiply(int a, int b) {
    int result = 0;
    bool negative = (a < 0) ^ (b < 0);
    a = a < 0 ? Add(~a, 1) : a;
    b = b < 0 ? Add(~b, 1) : b;
    
    while( b != 0) {
        if (b & 1) {
            result = Add(result, a);
        }
        a <<= 1;
        b >>= 1;
    }
    return negative ? Add(~result, 1) : result;
}


BinaryInt BinaryInt::operator-() const {
    return BinaryInt(Add(~value, 1));
}

BinaryInt& BinaryInt::operator++() {
    value = Add(value, 1);
    return *this;
}

BinaryInt BinaryInt::operator++(int) {
    BinaryInt tmp = *this;
    value = Add(value, 1);
    return tmp;
}

BinaryInt& BinaryInt::operator--() {
    value = Subtract(value, 1);
    return *this;
}

BinaryInt BinaryInt::operator--(int) {
    BinaryInt tmp = *this;
    value = Subtract(value, 1);
    return tmp;
}

BinaryInt& BinaryInt::operator+=(const BinaryInt& other) {
    value = Add(value, other.value);
    return *this;
}

BinaryInt BinaryInt::operator+(const BinaryInt& other) const {
    return BinaryInt(Add(value, other.value));
}

BinaryInt& BinaryInt::operator-=(const BinaryInt& other) {
    value = Subtract(value, other.value);
    return *this;
}

BinaryInt BinaryInt::operator-(const BinaryInt& other) const {
    return BinaryInt(Subtract(value, other.value));
}

BinaryInt& BinaryInt::operator*=(const BinaryInt& other) {
    value = Multiply(value, other.value);
    return *this;
}

BinaryInt BinaryInt::operator*(const BinaryInt& other) const {
    return BinaryInt(Multiply(value, other.value));
}

BinaryInt& BinaryInt::operator<<=(int shift) {
    value <<= shift;
    return *this;
}

BinaryInt BinaryInt::operator<<(int shift) const {
    return BinaryInt(value << shift);
}

BinaryInt& BinaryInt::operator>>=(int shift) {
    value >>= shift;
    return *this;
}

BinaryInt BinaryInt::operator>>(int shift) const {
    return BinaryInt(value >> shift);
}

std::pair<BinaryInt, BinaryInt> BinaryInt::SplitBits() const {
    int halfSize = sizeof(int) * 4;
    int high = value & (~0 << halfSize);
    int low = value & ((1 << halfSize) - 1);
    return {BinaryInt(high), BinaryInt(low)};
}

std::ostream& operator<<(std::ostream& os, const BinaryInt& b) {
    os << std::bitset<sizeof(int) * 8>(b.value);
    return os;
}
