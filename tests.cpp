#include "functions.h"

unsigned int test_num = 1;

void decorator(void (*function)()) {
    std::cout << "############ test no " << test_num++ << " ##############" << std::endl;
    function();
    std::cout << "#####################################\n\n";
}

void print_bytes(uint8_t *bytes) {
    for (int i = 0; i < 16; i++) {
        std::cout << "" << std::hex << int(bytes[i]) << ' ';
        if ((i + 1) % 4 == 0)
            std::cout << '\n';
    }
    std::cout << std::dec << std::endl;
}

// test subBytes() and invSubBytes()
void testSubBytes() {
    uint8_t bytes[16] = {0x67, 0x32, 0x25, 0xff, 0x45};

    print_bytes(bytes);
    subBytes(bytes);
    print_bytes(bytes);
    invSubBytes(bytes);
    print_bytes(bytes);
}

// test shiftRows() and invShiftRows()
void testShiftRows() {
    uint8_t bytes[16] = {0x00, 0x01, 0x02, 0x03,
                         0x10, 0x11, 0x12, 0x13,
                         0x20, 0x21, 0x22, 0x23,
                         0x30, 0x31, 0x32, 0x33};

    print_bytes(bytes);
    shiftRows(bytes);
    print_bytes(bytes);  // expected: 0x00 0x01 0x02 0x03 0x11 0x12 0x13 0x10 0x22 0x23 0x20 0x21 0x33 0x30 0x31 0x32
    invShiftRows(bytes);
    print_bytes(bytes);
}

// test mixColumns() and invMixColumns()
void testMixColumns() {
    uint8_t bytes[16] = {0xdb, 0xf2, 0x01, 0xc6,
                         0x13, 0x0a, 0x01, 0xc6,
                         0x53, 0x22, 0x01, 0xc6,
                         0x45, 0x5c, 0x01, 0xc6};

    print_bytes(bytes);
    mixColumns(bytes);
    print_bytes(bytes); // expected: 0x8e 0x9f 0x01 0xc6 0x4d 0xdc 0x01 0xc6 0xa1 0x58 0x01 0xc6 0xbc 0x9d 0x01 0xc6
    invMixColumns(bytes);
    print_bytes(bytes);
}

void testKeyExpansion() {
    uint8_t key[16] = {0};

    uint8_t expanded_keys[176];
    keyExpansion(key, expanded_keys);

    for (int i = 0; i < 176; i += 16) {
        uint8_t bytes[16];
        for (int j = 0; j < 16; j++) {
            bytes[j] = expanded_keys[i + j];
        }
        print_bytes(bytes);
    }

    // you can check here if this is correct: https://www.cryptool.org/en/cto/aes-step-by-step
}

void testAddRoundKey() {
    uint8_t state[16] = {0b00000001, 0b11111110};
    uint8_t key[16] = {0b10000001, 0b11111111};

    print_bytes(state);
    print_bytes(key);
    addRoundKey(state, key);
    print_bytes(state);
    print_bytes(key);
    addRoundKey(state, key);
    print_bytes(state);
    print_bytes(key);
}

void testRound() {
    uint8_t state[16] = {0x00, 0x03, 0x0f, 0x3f,
                         0x00, 0x03, 0x0f, 0x3f,
                         0x01, 0x07, 0x1f, 0x7f,
                         0x01, 0x07, 0x1f, 0x7f};

    uint8_t key[16] = {0};
    uint8_t expanded_key[176];
    keyExpansion(key, expanded_key);

    print_bytes(state);
    addRoundKey(state, expanded_key);  // initial round key addition
    print_bytes(state);
    encryptionRound(state, expanded_key + 16);
    print_bytes(state);

    std::cout << "used subkey: \n";
    print_bytes(expanded_key + 16);
}

void testAES128Encryption() {
    uint8_t state[16] = {0x00, 0x03, 0x0f, 0x3f,
                         0x00, 0x03, 0x0f, 0x3f,
                         0x01, 0x07, 0x1f, 0x7f,
                         0x01, 0x07, 0x1f, 0x7f};
    uint8_t key[16] = {0};
    uint8_t expanded_key[176];
    keyExpansion(key, expanded_key);

    print_bytes(state);
    AES128Encrypt(state, expanded_key);
    print_bytes(state);  // encrypted state
    AES128Decrypt(state, expanded_key);
    print_bytes(state);  // decrypted state
}

// combine all tests
void runTests() {
    decorator(testSubBytes);
    decorator(testShiftRows);
    decorator(testMixColumns);
    decorator(testKeyExpansion);
    decorator(testAddRoundKey);
    decorator(testRound);
    decorator(testAES128Encryption);
}