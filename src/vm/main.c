#include <stdio.h>
#include <stdlib.h>
#include "../../include/op.h"

int handle_mnemonic(unsigned char mnem) {
    switch (mnem) {
        case 0x01:
            printf("Mnemonic 0x01 executed\n");
            break;
            // Add cases for other mnemonics
    }
    return 0;
}

unsigned char *initialize_vm() {
    // allocate memory for the VM
    unsigned char *vm = malloc(MEM_SIZE * sizeof(unsigned char));

    // check for allocation
    if (vm == NULL) {
        fprintf(stderr, "Memory allocation for VM has failed.\n");
    } else {
        printf("Memory allocation for VM successful.");
    }

    // initialize memory to 0 (for now)
    for (int i = 0; i < MEM_SIZE; i++) {
        vm[i] = 0;
    }

    return vm;
}

void free_vm(unsigned char *vm) {
    free(vm);
    printf("Memory allocation for VM freed.");
}

int main() {
    unsigned char *vm = initialize_vm();

    // Example: Hardcode 'live' command in the memory for testing
    vm[0] = 0x01;


    // CORE VM LOGIC HERE
    for (int i = 0; i < MEM_SIZE; i++) {
        unsigned char mnem = vm[i];
        if (mnem == 0) continue; // skip empty cells
        handle_mnemonic(mnem);
    }

    // free the VM
    free_vm(vm);

    return 0;
}