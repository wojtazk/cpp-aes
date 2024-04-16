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