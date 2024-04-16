#include "functions.h"

unsigned int test_num = 1;

void decorator(void (*function)()) {
    std::cout << "############ test no " << test_num++ << " ##############" << std::endl;
    function();
    std::cout << "#####################################\n\n";
}

void print_bytes(uint8_t *bytes) {
    for (int i = 0; i < 16; i++) {
        std::cout << "0x" << std::hex << int(bytes[i]) << ' ';
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
void textMixColumns() {
    uint8_t bytes[16] = {0xdb, 0xf2, 0x01, 0xc6,
                         0x13, 0x0a, 0x01, 0xc6,
                         0x53, 0x22, 0x01, 0xc6,
                         0x45, 0x5c, 0x01, 0xc6};

    print_bytes(bytes);
    mixColumns(bytes);
    print_bytes(bytes); // expected: 0x8e 0x9f 0x01 0xc6 0x4d 0xdc 0x01 0xc6 0xa1 0x58 0x01 0xc6 0xbc 0x9d 0x01 0xc6
}

// combine all tests
void runTests() {
    decorator(testSubBytes);
    decorator(testShiftRows);
    decorator(textMixColumns);
}