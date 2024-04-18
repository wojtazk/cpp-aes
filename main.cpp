#include "functions.h"
#include <fstream>

int main(int argc, char *argv[]) {
    // FIXME: if you want to run test uncomment the next line
    //runTests();

    // if arg count is less than 3 -> no input and output files specified
    if (argc < 4) {
        std::cerr << "You have to specify input and output files, and an encryption or decryption flag" << std::endl;
        return EXIT_FAILURE;

    }

    // get encryption/decryption flag, input and output files from args
    std::string flag = argv[1], input_file_name = argv[2], output_file_name = argv[3];
    //std::cout << flag << ' ' << input_file_name << ' ' << output_file_name << '\n';

// determine if user wants to encrypt or decrypt
    bool encrypt = false, decrypt = false;
    if (flag == "-e") {
        encrypt = true;
    } else if (flag == "-d") {
        decrypt = true;
    } else {
        std::cerr << "invalid flag, specify '-e' or '-d'" << std::endl;
        return EXIT_FAILURE;
    }
    //std::cout << encrypt << ' ' << decrypt << std::endl;


    // get the key from user
    uint8_t input_key[16] = {0};  // key is 128 bits (16 bytes)
    getInputKey(input_key);

    // create expanded keys
    uint8_t expanded_keys[176];  // 11 keys total -> 128 bits * 11 = 176 bytes
    keyExpansion(input_key, expanded_keys);

    // open input file for reading
    std::ifstream input_file(input_file_name, std::ios::in | std::ios::binary);
    if (!input_file) {
        std::cerr << "Error opening file: " << input_file_name << std::endl;
        return EXIT_FAILURE;
    }

    // open output file for writing
    std::ofstream output_file(output_file_name, std::ios::binary);
    if (!output_file) {
        std::cerr << "Error opening file: " << output_file_name << std::endl;
        return EXIT_FAILURE;
    }

    char byte;
    uint8_t state[16] = {};

    int i = 0;
    while (input_file.read(&byte, 1)) {
        state[i] = byte;
        i++;

        if (i == 16) {
            transpose(state);

            if (encrypt)
                AES128Encrypt(state, expanded_keys);
            else if (decrypt)
                AES128Decrypt(state, expanded_keys);

            transpose(state);

            for (uint8_t output_byte: state) {
                output_file << output_byte;
            }

            i = 0;
            std::fill(state, state + 16, 0);
        }
    }


    // used only for encryption
    // writes 'odd' bytes and writes additional bytes so the file size is multiple of 16 bytes
    if (i > 0) {
        // add n bytes with value n at the end
        // these are added bytes to make file size a multiple of 16 bytes
        uint8_t added_bytes = 16 - i;
        for (int j = i; j < 16; j++)
            state[j] = added_bytes;

        transpose(state);

        if (encrypt)
            AES128Encrypt(state, expanded_keys);
        else if (decrypt)
            AES128Decrypt(state, expanded_keys);

        transpose(state);

        for (uint8_t output_byte: state) {
            output_file << output_byte;
        }
    }


    input_file.close();
    output_file.close();
    return EXIT_SUCCESS;
}
