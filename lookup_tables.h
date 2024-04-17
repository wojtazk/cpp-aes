#pragma once
#ifndef CPP_AES_LOOKUP_TABLES_H
#define CPP_AES_LOOKUP_TABLES_H

extern uint8_t sbox[256];
extern uint8_t inv_sbox[256];

extern uint8_t multiply_by_2[256];
extern uint8_t multiply_by_3[256];

extern uint8_t multiply_by_9[256];
extern uint8_t multiply_by_11[256];
extern uint8_t multiply_by_13[256];
extern uint8_t multiply_by_14[256];

extern uint8_t rcon[16];

#endif //CPP_AES_LOOKUP_TABLES_H
