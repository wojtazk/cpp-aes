#pragma once
#ifndef CPP_AES_FUNCTIONS_H
#define CPP_AES_FUNCTIONS_H

#include <iostream>
#include <string>

#include <cstdint>
#include "lookup_tables.h"

// declare function used for running tests
void runTests();

// key functions
void transpose(uint8_t *array);

void keyExpansion(const uint8_t *input_key, uint8_t *expanded_keys);

void addRoundKey(uint8_t *state, const uint8_t *round_key);

void getInputKey(uint8_t *input_key);

// encryption functions
void subBytes(uint8_t *state);

void shiftRows(uint8_t *state);

void mixColumns(uint8_t *state);

// AES encryption
void encryptionRound(uint8_t *state, uint8_t *round_key);

void encryptionLastRound(uint8_t *state, uint8_t *round_key);

void AES128Encrypt(uint8_t *state, uint8_t *expanded_key);

// decryption functions
void invSubBytes(uint8_t *state);

void invShiftRows(uint8_t *state);

void invMixColumns(uint8_t *state);

// AES decryption
void AES128Decrypt(uint8_t *state, uint8_t *expanded_key);

#endif //CPP_AES_FUNCTIONS_H
