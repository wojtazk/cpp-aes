#include "functions.h"

// [b0, b1, b2, b3] -> [S(b0), S(b1), S(b2), S(b3)]
inline void subWord(uint8_t *word) {
    for (int i = 0; i < 4; i++) {
        word[i] = sbox[word[i]];
    }
}

// [b0, b1, b2, b3] -> [b1, b2, b3, b0]
inline void rotWord(uint8_t *word) {
    uint8_t tmp = word[0];
    word[0] = word[1];
    word[1] = word[2];
    word[2] = word[3];
    word[3] = tmp;
}

// function for transposing 4 x 4 matrix (16 bytes array in this case)
void transpose(uint8_t *array) {
    uint8_t transposed_array[16];

    for (int i = 0; i < 4; i++) {
        int tmp = i * 4;
        transposed_array[i + 0] = array[tmp];
        transposed_array[i + 4] = array[tmp + 1];
        transposed_array[i + 8] = array[tmp + 2];
        transposed_array[i + 12] = array[tmp + 3];
    }

    for (int i = 0; i < 16; i++) {
        array[i] = transposed_array[i];
    }
}

// key expansion
// aes 128 bit -> 10 rounds
// 11 keys total -> 128 bits * 11 = 176 bytes
void keyExpansion(const uint8_t *input_key, uint8_t *expanded_keys) {
    // first 128 bits (16 bytes) -> original key
    for (int i = 0; i < 16; i++) {
        expanded_keys[i] = input_key[i];
    }

    int generated_key_bytes = 16;
    int rcon_round = 0;
    uint8_t prev_word[4];

    while (generated_key_bytes < 176) {
        // get previous word
        for (int i = 0; i < 4; i++) {
            prev_word[i] = expanded_keys[generated_key_bytes - 4 + i];
        }

        // w_i+4 = g(w_i+3) ^ w_i
        // w_i+5 = w_i+4    ^ w_i+1
        // w_i+6 = w_i+5    ^ w_i+2
        // w_i+7 = w_i+6    ^ w_i+3

        // if it is the first word of a new expanded key (every 16th byte) -> apply g()
        if (generated_key_bytes % 16 == 0) {
            rotWord(prev_word);
            subWord(prev_word);
            prev_word[0] = prev_word[0] ^ rcon[rcon_round++];
        }

        // XOR current word with the 4 words older word
        for (int i = 0; i < 4; i++) {
            expanded_keys[generated_key_bytes + i] = expanded_keys[generated_key_bytes - 16 + i] ^ prev_word[i];
        }

        generated_key_bytes += 4;
    }

    // transpose expanded keys
    for (int i = 0; i < 176; i += 16) {
        transpose(expanded_keys + i);
    }
}

void addRoundKey(uint8_t *state, const uint8_t *round_key) {
    for (int i = 0; i < 16; i++)
        state[i] = state[i] ^ round_key[i];
}

// get the key from user
void getInputKey(uint8_t *input_key) {
    std::string input_key_str;
    std::cout << "provide the key:";
    std::getline(std::cin, input_key_str);

    // convert input_key_str to array of 16 bytes (only first 16 bytes of input string will be converted)
    int i = 0;
    for (uint8_t ch: input_key_str) {
        input_key[i] = ch;
        i++;

        if (i == 16)
            break;
    }

    // print input key in hex
    std::cout << "key in HEX: ";
    for (int j = 0; j < 16; j++) {
        std::cout << std::hex << int(input_key[j]) << ' ';
    }
    std::cout << std::dec << '\n';
}