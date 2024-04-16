#include "functions.h"

unsigned int test_num = 1;

void decorator(void (*function)()) {
    std::cout << "############ test nr " << test_num++ << " ##############" << std::endl;
    function();
    std::cout << "#####################################\n\n";
}

// test subBytes() and invSubBytes()
void testSubBytes() {
    uint8_t bytes[16] = {0x67, 0x32, 0x25, 0xff, 0x45};

    for (uint8_t byte: bytes) {
        std::cout << "0x" << std::hex << int(byte) << ' ';
    }
    std::cout << std::dec << std::endl;

    subBytes(bytes);

    for (uint8_t byte: bytes) {
        std::cout << "0x" << std::hex << int(byte) << ' ';
    }
    std::cout << std::dec << std::endl;

    invSubBytes(bytes);

    for (uint8_t byte: bytes) {
        std::cout << "0x" << std::hex << int(byte) << ' ';
    }
    std::cout << std::dec << std::endl;
}

// combine all tests
void runTests() {
    decorator(testSubBytes);
}