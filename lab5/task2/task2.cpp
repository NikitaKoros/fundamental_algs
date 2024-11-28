#include "util_task2.hpp"


int main() {
    try {
        std::vector<std::byte> key = {std::byte{0x1A}, std::byte{0x2B}, std::byte{0x3C}, std::byte{0x4D}, std::byte{0x5E}};

        Encoder encoder(key);

        std::string inputFile = "../examp.txt";
        std::string encryptedFile = "../encr.txt"; // hexdump -C ../encr.txt
        std::string decryptedFile = "../decr.txt"; 

        encoder.Encode(inputFile, encryptedFile);
        std::cout << "File encrypted successfully.\n";

        encoder.Encode(encryptedFile, decryptedFile);
        std::cout << "File decrypted successfully.\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}