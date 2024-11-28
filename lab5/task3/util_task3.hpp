#ifndef TASK_3
#define TASK_3

#include <iostream>
#include <cstring>
#include <bitset>

class LogicalValuesArray {
   private:
    unsigned int value;

   public:
   LogicalValuesArray(unsigned int val = 0);
   unsigned int GetValue() const;
   void SetValue(unsigned int);
   LogicalValuesArray Invert() const;
   LogicalValuesArray Conjunction(const LogicalValuesArray) const;
   LogicalValuesArray Disjunction(const LogicalValuesArray) const;
   LogicalValuesArray Implication(const LogicalValuesArray) const;
   LogicalValuesArray Coimplication(const LogicalValuesArray) const;
   LogicalValuesArray XOR(const LogicalValuesArray) const;
   LogicalValuesArray Equivalence(const LogicalValuesArray) const;
   LogicalValuesArray PierceArrow(const LogicalValuesArray) const;
   LogicalValuesArray ShefferStroke(const LogicalValuesArray) const;
   static bool Equals(const LogicalValuesArray&, const LogicalValuesArray&);
   bool GetBit(size_t) const;
   void ToBinaryString(char*, size_t);
};

#endif
