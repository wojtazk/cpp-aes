#include <iostream>
#include "lookup_tables.h"

void addRoundKey() {
    std::cout << "hello there" << std::endl;
}

// Substitute 16 bytes by the values in the S-box lookup table
void subBytes(uint8_t *state) {
    for (int i = 0; i < 16; i++) {
        state[i] = sbox[state[i]];
    }
}