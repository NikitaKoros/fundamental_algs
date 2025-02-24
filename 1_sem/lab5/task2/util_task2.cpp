#include "util_task2.hpp"
#include <cstddef>
#include <stdexcept>

void Encoder::RC4Init(std::vector<std::byte>& s) const {
    const size_t keyLength = key.size();
    for (size_t i = 0; i < 256; ++i) {
        s[i] = static_cast<std::byte>(i);
    }

    int j = 0;
    for (int i = 0; i < 256; ++i) {
        j = (j + static_cast<int>(s[i]) + static_cast<int>(key[i % keyLength])) % 256;
        std::swap(s[i], s[j]);
    }
}

void Encoder::RC4Transform(std::ifstream& input, std::ofstream& output) const {
    std::vector<std::byte> s(256);
    RC4Init(s);
    
    int i = 0, j = 0;
    char inputChar;
    while (input.get(inputChar)) {
        i = (i + 1) % 256;
        j = (j + static_cast<int>(s[i])) % 256;
        std::swap(s[i], s[j]);
        
        std::byte keyByte = s[(static_cast<int>(s[i]) + static_cast<int>(s[j])) % 256];
        std::byte encryptedByte = static_cast<std::byte>(inputChar) ^ keyByte;
        
        char outputChar = static_cast<char>(encryptedByte);
        output.put(outputChar);
        
        if(!output) {
            throw std::runtime_error("Failed to write data to output file.");
        }
    }
    
    if (!input.eof()) {
        throw std::runtime_error("Error occcured while reading input file.");
    }
}

Encoder::Encoder(const std::vector<std::byte>& key) : key(key) {
    if (key.empty()) {
        throw std::invalid_argument("Encryption key cannot be empty.");
    }
}

void Encoder::SetKey(const std::vector<std::byte>& newKey) {
    if (newKey.empty()) {
        throw std::invalid_argument("Encryption key cannot be empty.");
    }
    key = newKey;
}

void Encoder::Encode(const std::string& inputPath, const std::string& outputPath) {
    std::ifstream inputFile(inputPath, std::ios::binary);
    if (!inputFile) {
        throw std::runtime_error("Failed to open input file.");
    }

    std::ofstream outputFile(outputPath, std::ios::binary);
    if (!outputFile) {
        throw std::runtime_error("Failed to open output file.");
    }

    RC4Transform(inputFile, outputFile);

    inputFile.close();
    outputFile.close();
}
