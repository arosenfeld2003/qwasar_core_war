#ifndef VM_STATE_H
#define VM_STATE_H

// #include "champion.h" // We need to define champion_t in another header
//#include "header.h"

typedef struct vm_state {
    int dump_cycle;       // Cycle number to dump memory (-1 if not used)
    int next_champion_id; // Next champion ID to assign with -n
    champion_t champions[MAX_CHAMPIONS]; // Array of champions
    int champion_count;   // Number of loaded champions
    unsigned char memory[MEM_SIZE];
    int registers[REG_NUMBER];
    int pc; // Program counter
    int carry; // Carry flag
} vm_state_t;

// VM functions
unsigned char *initialize_vm();
void free_vm(unsigned char *vm);
unsigned char read_memory(unsigned char *vm, size_t address);
void write_memory(unsigned char *vm, size_t address, unsigned char value);
void write_int_to_memory(unsigned char *vm, size_t address, int value);
void assign_program_numbers(champion_t champions[], int num_champions);
void load_programs_into_memory(unsigned char *vm, champion_t *champ);
void load_champion_code(vm_state_t *vm_state, champion_t *champ);
int read_direct_value(unsigned char *memory, int start_pos);

#endif
