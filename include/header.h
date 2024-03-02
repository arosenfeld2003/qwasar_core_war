#ifndef HEADER_H
#define HEADER_H

#include <stdlib.h>
#include <stdio.h> // printf
#include <string.h> // strcmp
// #include "vm_state.h"
#include "op.h"

typedef struct vm_state {
    int dump_cycle;       // Cycle number to dump memory (-1 if not used)
    int next_champion_id; // Next champion ID to assign with -n
    champion_t champions[MAX_CHAMPIONS]; // Array of champions
    int champion_count;   // Number of loaded champions
    unsigned char *memory;
    int registers[REG_NUMBER];
    int pc; // Program Counter
    int carry; // Carry flag
} vm_state_t;


// shared function prototypes
// VM functions
unsigned char *initialize_vm();
void free_vm(unsigned char *vm);
unsigned char read_memory(unsigned char *vm, size_t address);
void write_memory(unsigned char *vm, size_t address, unsigned char value);
void write_int_to_memory(unsigned char *vm, size_t address, int value);
void assign_program_numbers(champion_t champions[], int num_champions);
void load_programs_into_memory(vm_state_t vm, champion_t *champ, int champ_count);
void load_champion_code(vm_state_t *vm_state, champion_t *champ);
int read_direct_value(const unsigned char *memory, int start_pos);
int handle_cmd(vm_state_t *vm_state, unsigned char cmd);



#endif /* HEADER_H */
