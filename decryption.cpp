#include "functions.h"

void invSubBytes(uint8_t *state) {
    for (int i = 0; i < 16; i++) {
        state[i] = inv_sbox[state[i]];
    }
}

void invShiftRows(uint8_t *state) {
    uint8_t tmp, tmp2;

    // first row 0-3 -> no shift

    // second row 4-7 -> shift right by 1 byte or shift left by 3 bytes
    tmp = state[7];
    state[7] = state[6];
    state[6] = state[5];
    state[5] = state[4];
    state[4] = tmp;

    // third row 8-11 -> shift right by 2 bytes or left by 2 bytes
    tmp = state[8];
    tmp2 = state[9];
    state[8] = state[10];
    state[9] = state[11];
    state[10] = tmp;
    state[11] = tmp2;

    // fourth row 12-15 -> shift right by 3 bytes or shift left by 1 byte
    tmp = state[12];
    state[12] = state[13];
    state[13] = state[14];
    state[14] = state[15];
    state[15] = tmp;
}

void invMixColumns(uint8_t *state) {
    uint8_t a[4];

    // d -> unmixed byte, a -> column bytes, ^ -> bit-wise XOR
    // d0 = 14*a0 ^ 11*a1 ^ 13*a2 ^ 9*a3
    // d1 = 9*a0  ^ 14*a1 ^ 11*a2 ^ 13*a3
    // d2 = 13*a0 ^ 9*a1  ^ 14*a2 ^ 11*a3
    // d3 = 11*a0 ^ 13*a1 ^ 9*a2  ^ 14*a3

    // first column - [0, 4, 8, 12] and so on
    for (int i = 0; i < 4; i++) {
        // get current column bytes
        a[0] = state[i];
        a[1] = state[i + 4];
        a[2] = state[i + 8];
        a[3] = state[i + 12];

        // un-mix bytes
        state[i] = multiply_by_14[a[0]] ^ multiply_by_11[a[1]] ^ multiply_by_13[a[2]] ^ multiply_by_9[a[3]];
        state[i + 4] = multiply_by_9[a[0]] ^ multiply_by_14[a[1]] ^ multiply_by_11[a[2]] ^ multiply_by_13[a[3]];
        state[i + 8] = multiply_by_13[a[0]] ^ multiply_by_9[a[1]] ^ multiply_by_14[a[2]] ^ multiply_by_11[a[3]];
        state[i + 12] = multiply_by_11[a[0]] ^ multiply_by_13[a[1]] ^ multiply_by_9[a[2]] ^ multiply_by_14[a[3]];
    }
}