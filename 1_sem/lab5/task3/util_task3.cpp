#include "util_task3.hpp"
#include <stdexcept>

LogicalValuesArray::LogicalValuesArray(unsigned int val) : value(val) {}

unsigned int LogicalValuesArray::GetValue() const {
    return value;
}

void LogicalValuesArray::SetValue(unsigned int val) {
    value = val;
}

LogicalValuesArray LogicalValuesArray::Invert() const {
    return LogicalValuesArray(~value);
}

LogicalValuesArray LogicalValuesArray::Conjunction(const LogicalValuesArray other) const {
    return LogicalValuesArray(value & other.value);
}

LogicalValuesArray LogicalValuesArray::Disjunction(const LogicalValuesArray other) const {
    return LogicalValuesArray(value | other.value);
}

LogicalValuesArray LogicalValuesArray::Implication(const LogicalValuesArray other) const {
    return Invert().Disjunction(other);
}

LogicalValuesArray LogicalValuesArray::Coimplication(
    const LogicalValuesArray other) const {
    return Conjunction(other.Invert());
}

LogicalValuesArray LogicalValuesArray::XOR(const LogicalValuesArray other) const {
    return LogicalValuesArray(Invert().Conjunction(other).value +
                              Conjunction(other.Invert()).value);
}

LogicalValuesArray LogicalValuesArray::Equivalence(const LogicalValuesArray other) const {
    return LogicalValuesArray(Conjunction(other).value +
                              Invert().Conjunction(other.Invert()).value);
}

LogicalValuesArray LogicalValuesArray::PierceArrow(const LogicalValuesArray other) const {
    return Invert().Conjunction(other.Invert());
}

LogicalValuesArray LogicalValuesArray::ShefferStroke(
    const LogicalValuesArray other) const {
    return Conjunction(other).Invert();
}

bool LogicalValuesArray::Equals(const LogicalValuesArray& x,
                                const LogicalValuesArray& y) {
    return x.Equivalence(y).value == 1;
}

bool LogicalValuesArray::GetBit(size_t position) const {
    if (position >= sizeof(unsigned int) * 8) {
        throw std::out_of_range("Position out of range");
    }
    return (value >> position) & 1;
}

void LogicalValuesArray::ToBinaryString(char* buffer, size_t bufSize) {
    if (bufSize < (sizeof(unsigned int) * 8 + 1)) {
        throw std::invalid_argument("Buffer size is too small");
    }
    
    size_t numBits = sizeof (unsigned int) * 8;
    for (size_t i = 0; i < numBits; i++) {
        buffer[i] = GetBit(numBits - 1 - i) ? '1' : '0';
    }
    
    buffer[numBits] = '\0';
}

