#include <iostream>
#include "encryption.h"

// test subBytes()
void testSubBytes() {
    uint8_t bytes[16] = {0x67, 0x32, 0x25, 0xff, 0x45};
    subBytes(bytes);

    for (unsigned char byte: bytes) {
        std::cout << "0x" << std::hex << int(byte) << ' ';
    }

    std::cout << std::dec << std::endl;
}

void runTests() {
    testSubBytes();
}