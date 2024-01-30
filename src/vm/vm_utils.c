#include "../../include/header.h"
#include <stdio.h>

// read one byte from VM memory
unsigned char read_memory(unsigned char *vm, size_t address) {
    if (address >= MEM_SIZE) {
        fprintf(stderr, "Read Memory Error: Address %zu out of bounds\n", address);
        // handle memory out of bounds error: for now, exit program.
        exit(EXIT_FAILURE);
    }
    return vm[address];
}

// write a byte to VM memory
void write_memory(unsigned char *vm, size_t address, unsigned char value) {
    if (address >= MEM_SIZE) {
        fprintf(stderr, "Write Memory Error: Address %zu out of bounds\n", address);
        // handle memory out of bounds error: for now, exit program
        exit(EXIT_FAILURE);
    }
    vm[address] = value;
}