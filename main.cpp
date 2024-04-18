#include "functions.h"

int main(int argc, char *argv[]) {
    // FIXME: if you want to run test uncomment the next line
    runTests();

    // if arg count is less than 3 -> no input and output files specified
    if (argc < 4) {
        throw std::invalid_argument("You have to specify input and output files, and an encryption or decryption flag");
    }

    // get encryption/decryption flag, input and output files from args
    std::string flag = argv[1], input_file = argv[2], output_file = argv[3];
    std::cout << flag << ' ' << input_file << ' ' << output_file << '\n';

    // get the key from user
    uint8_t input_key[16];  // key is 128 bits (16 bytes)
    getInputKey(input_key);

    // create expanded keys
    uint8_t expanded_keys[176];  // 11 keys total -> 128 bits * 11 = 176 bytes
    keyExpansion(input_key, expanded_keys);

    return EXIT_SUCCESS;
}
