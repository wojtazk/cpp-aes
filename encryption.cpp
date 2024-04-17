#include "functions.h"

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

void mixColumns(uint8_t *state) {
    uint8_t a[4];

    // d -> mixed byte, a -> column bytes, ^ -> bit-wise XOR
    // d0 = 2*a0 ^ 3*a1 ^ 1*a2 ^ 1*a3
    // d1 = 1*a0 ^ 2*a1 ^ 3*a2 ^ 1*a3
    // d2 = 1*a0 ^ 1*a1 ^ 2*a2 ^ 3*a3
    // d3 = 3*a0 ^ 1*a1 ^ 1*a2 ^ 2*a3

    // first column - [0, 4, 8, 12] and so on
    for (int i = 0; i < 4; i++) {
        // get current column bytes
        a[0] = state[i];
        a[1] = state[i + 4];
        a[2] = state[i + 8];
        a[3] = state[i + 12];

        // mix bytes
        state[i] = multiply_by_2[a[0]] ^ multiply_by_3[a[1]] ^ a[2] ^ a[3];
        state[i + 4] = a[0] ^ multiply_by_2[a[1]] ^ multiply_by_3[a[2]] ^ a[3];
        state[i + 8] = a[0] ^ a[1] ^ multiply_by_2[a[2]] ^ multiply_by_3[a[3]];
        state[i + 12] = multiply_by_3[a[0]] ^ a[1] ^ a[2] ^ multiply_by_2[a[3]];
    }
}