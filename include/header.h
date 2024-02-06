#ifndef HEADER_H
#define HEADER_H

#include <stdlib.h>
#include <stdlib.h>
#include "op.h"

// VM functions
unsigned char *initialize_vm();
void free_vm(unsigned char *vm);
int handle_cmd(unsigned char cmd);
unsigned char read_memory(unsigned char *vm, size_t address);
void write_memory(unsigned char *vm, size_t address, unsigned char value);
void assign_program_numbers(champion_t champions[], int num_champions);
void load_programs_into_memory(unsigned char *memory, champion_t champions[], int num_champions);

// more shared function prototypes



#endif /* HEADER_H */
