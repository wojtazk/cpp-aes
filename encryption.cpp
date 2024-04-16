#include <iostream>
#include "functions.h"

void addRoundKey() {
    std::cout << "hello there" << std::endl;
}

// Substitute 16 bytes by the values in the S-box lookup table
void subBytes(uint8_t *state) {
    for (int i = 0; i < 16; i++) {
        state[i] = sbox[state[i]];
    }
}

void shiftRows(uint8_t *state) {
    uint8_t tmp, tmp2;

    // first row 0-3 -> no shift

    // second row 4-7 -> shift left by 1 byte
    tmp = state[4];
    state[4] = state[5];
    state[5] = state[6];
    state[6] = state[7];
    state[7] = tmp;

    // third row 8-11 -> shift left by 2 bytes
    tmp = state[8];
    tmp2 = state[9];
    state[8] = state[10];
    state[9] = state[11];
    state[10] = tmp;
    state[11] = tmp2;

    // fourth row 12-15 -> shift left by 3 bytes
    tmp = state[15];
    state[15] = state[14];
    state[14] = state[13];
    state[13] = state[12];
    state[12] = tmp;
}