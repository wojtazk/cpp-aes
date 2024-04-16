#pragma once
#ifndef CPP_AES_FUNCTIONS_H
#define CPP_AES_FUNCTIONS_H

#include <iostream>
#include <string>

#include <cstdint>
#include "lookup_tables.h"

// declare function used for running tests
void runTests();

// encryption functions
void addRoundKey();

void subBytes(uint8_t *state);

void shiftRows(uint8_t *state);

void mixColumns();

// decryption functions
void invSubBytes(uint8_t *state);

void invShiftRows();

void invMixColumns();

#endif //CPP_AES_FUNCTIONS_H
