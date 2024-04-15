#pragma once
#ifndef CPP_AES_ENCRYPTION_H
#define CPP_AES_ENCRYPTION_H

#include <cstdint>

// encryption functions
void addRoundKey();

void subBytes(uint8_t *state);

void shiftRows();

void mixColumns();

#endif //CPP_AES_ENCRYPTION_H
