#include "core.h"
#include <stdlib.h>

Core* initializeCore() {
    Core* core = malloc(sizeof(Core));
    if (core == NULL) {
        // handle memory alloc error
        exit(1);
    }

    for (int i = 0; i < CORE_SIZE; i++) {
        core->memmory[i].opcode = DAT; // start with all cells as DAT
        core->memory[i].operandA = 0;
        core->memory[i].operandB = 0;
    }

    return core;
}

// deallocate core, load warriors, etc...