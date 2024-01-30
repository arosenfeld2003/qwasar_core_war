#ifndef HEADER_H
#define HEADER_H

#include <stdlib.h>
#include <stdlib.h>
#include "op.h"

// Memory management functions
unsigned char *initialize_vm();
void free_vm(unsigned char *vm);
int handle_mnemonic(unsigned char mnem);
unsigned char read_memory(unsigned char *vm, size_t address);
void write_memory(unsigned char *vm, size_t address, unsigned char value);


// more shared function prototypes

#endif /* HEADER_H */
