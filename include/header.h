#ifndef HEADER_H
#define HEADER_H

#include <stdlib.h>
#include <stdio.h> // printf
#include <string.h> // strcmp
#include "op.h"

typedef struct vm_state {
    int dump_cycle;       // Cycle number to dump memory (-1 if not used)
    int next_champion_id; // Next champion ID to assign with -n
    champion_t champions[MAX_CHAMPIONS]; // Array of champions
    int champion_count;   // Number of loaded champions
    int current_champion_index;
    unsigned char *memory;
    int cycle_count;
} vm_state_t;


// shared function prototypes
// VM functions
unsigned char *initialize_vm();
void free_vm(unsigned char *vm);
int read_memory(vm_state_t *vm_state, int address);
int get_arg_value(vm_state_t *vm_state, int index);
void update_carry_flag(champion_t *champion, int value);
void write_memory(vm_state_t *vm_state, int address, int value);
int read_register(champion_t *champion, int register_number);
void write_register(champion_t *champion, int register_dest, int value);
void create_new_program(vm_state_t *vm_state, champion_t *champion, int new_counter);
void write_int_to_memory(vm_state_t *vm_state, size_t address, int value);
void assign_program_numbers(champion_t champions[], int num_champions);
void load_champion(vm_state_t *vm, champion_t *champ);
void load_programs_into_memory(vm_state_t *vm, champion_t champions[], int num_champions);
int read_direct_value(const unsigned char *memory, int start_pos);
int handle_cmd(vm_state_t *vm_state, unsigned char cmd);

#endif /* HEADER_H */
