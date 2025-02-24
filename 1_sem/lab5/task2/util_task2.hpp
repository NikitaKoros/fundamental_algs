#ifndef TASK_2
#define TASK_2

#include <cstddef>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

class Encoder {
   private:
    std::vector<std::byte> key;
    
    void RC4Init(std::vector<std::byte>&) const;
    void RC4Transform(std::ifstream&, std::ofstream&) const;

   public:
    Encoder(const std::vector<std::byte>&);
    void SetKey(const std::vector<std::byte>&);
    void Encode(const std::string&, const std::string&);
};

#endif
