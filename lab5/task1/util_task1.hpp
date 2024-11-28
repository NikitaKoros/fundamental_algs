#ifndef TASK_1
#define TASK_1

#include <bitset>
#include <iostream>
#include <utility>

class BinaryInt {
private:
    int value;

    static int Add(int, int);
    static int Subtract(int, int);
    static int Multiply(int, int);

public:
    BinaryInt();
    BinaryInt(int);

    BinaryInt operator-() const;
    
    BinaryInt& operator++();
    BinaryInt operator++(int);
    BinaryInt& operator--();
    BinaryInt operator--(int);
    
    BinaryInt& operator+=(const BinaryInt&);
    BinaryInt& operator-=(const BinaryInt&);
    BinaryInt& operator*=(const BinaryInt&);
    
    BinaryInt operator+(const BinaryInt&) const;
    BinaryInt operator-(const BinaryInt&) const;
    BinaryInt operator*(const BinaryInt&) const;
    
    BinaryInt& operator<<=(int);
    BinaryInt operator<<(int) const;
    BinaryInt& operator>>=(int);
    BinaryInt operator>>(int) const;
    
    std::pair<BinaryInt, BinaryInt> SplitBits() const;
    
    friend std::ostream& operator<<(std::ostream&, const BinaryInt&);
};

#endif

