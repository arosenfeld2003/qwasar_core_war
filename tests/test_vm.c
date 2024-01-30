#include "../include/header.h"
#include <stdio.h>
#include <assert.h>

void test_handle_mnemonic(unsigned char *vm) {
    // Hardcode some commands here for testing...
    vm[0] = 0x01;
    vm[1] = 0x02;
    vm[2] = 0x03;
    vm[3] = 0x04;
    vm[4] = 0x05;
    vm[5] = 0x06;
    vm[6] = 0x07;
    vm[7] = 0x08;
    vm[8] = 0x09;
    vm[9] = 0x0a;
    vm[10] = 0x0b;
    vm[11] = 0x0c;
    vm[12] = 0x0d;
    vm[13] = 0x0e;
    vm[14] = 0x0f;
    vm[15] = 0x10;

    // test core VM logic -> maybe a better way to be DRY without repeating this code
    for (int i = 0; i < MEM_SIZE; i++) {
        unsigned char mnem = vm[i];
        if (mnem == 0) continue; // skip empty cells
        handle_mnemonic(mnem);
    }
}

void test_initialization() {
    unsigned char *vm = initialize_vm();
    assert(vm != NULL);
    test_handle_mnemonic(vm);
    free_vm(vm);
}

void test_read_write() {
    unsigned char *vm = initialize_vm();
    write_memory(vm, 10, 0xAA); // Write a byte
    assert(read_memory(vm, 10) == 0xAA); // Read the same byte and check
    printf("VM read/write have executed successfully.");
    free_vm(vm);
}

int main() {
    test_initialization();
    test_read_write();
    // more tests
    printf("All tests passed successfully.\n");
    return 0;
}