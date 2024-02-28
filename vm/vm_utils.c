#include "../include/header.h"
#include <stdio.h>
#include <string.h>

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


/*
 * Helper function to write a 4-byte integer to VM memory
 * Big Endian Format:
 * https://developer.arm.com/documentation/ddi0333/h/programmer-s-model/memory-formats/legacy-big-endian-format
 * */
void write_int_to_memory(unsigned char *vm, size_t address, int value) {
    for (int i = 0; i < 4; ++i) {
        write_memory(vm, address + 3 - i, (value >> (i * 8)) & 0xFF);
    }
}

void parse_arguments(int argc, char **argv, vm_state_t *vm_state) {
    vm_state->dump_cycle = -1;  // Default: no memory dump
    vm_state->champion_count = 0;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-dump") == 0 && (i + 1 < argc)) {
            vm_state->dump_cycle = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-n") == 0 && (i + 2 < argc)) {
            // -n is followed by prog_number, then champion_file_name
            int prog_number = atoi(argv[++i]);
            char* file_path = argv[++i];

            if (vm_state->champion_count < MAX_CHAMPIONS) {
                champion_t *champ = &vm_state->champions[vm_state->champion_count++];
                champ->id = prog_number;
                champ->file_path = file_path;
                // TODO: start_address might be different if multiple programs
                champ->start_address = 0; // Default start address, to be assigned later
            }
        } else if (strcmp(argv[i], "-a") == 0 && (i + 1 < argc)) {
            // -a option to specify next champion's load address
            // we need logic to apply to next loaded champion
            int address = atoi(argv[++i]);
            if (vm_state->champion_count > 0) {
                // apply address to the last added champion (assuming -a follows -n)
                vm_state->champions[vm_state->champion_count - 1].start_address = address;
            }
        } else {
            // assume all other args are champion file names without specified ID
            if (vm_state->champion_count < MAX_CHAMPIONS) {
                champion_t *champ = &vm_state->champions[vm_state->champion_count++];
                champ->id = vm_state->champion_count;  // Assign ID based on order added
                champ->file_path = argv[i];
                champ->start_address = 0; // TODO: start someplace not 0?
            }
        }
    }
}

// load a single .cor file
// vm_state_t and champion_t are defined and include file_path

void load_champion(vm_state_t vm, champion_t *champ, int champ_count) {
    FILE *file = fopen(champ->file_path, "rb"); // Open in binary mode
    if (!file) {
        perror("Failed to open champion file");
        exit(EXIT_FAILURE);
    }

    // Assuming size is set by another process or read from the .cor file
    champ->code = (unsigned char*)malloc(champ->size);
    if (champ->code == NULL) {
        perror("Memory allocation failed for champion code");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fread(champ->code, sizeof(unsigned char), champ->size, file);
    fclose(file);

    // copy champion code into vm_memory at start_address
    load_programs_into_memory(vm, champ, champ_count);
}

// TODO: needs refactor
void load_programs_into_memory(vm_state_t vm, champion_t *champ, int num_champions) {
    int pc = champ->start_address;
    for (int i = 0; i < champ_count; ++i) {
        vm.pc++ = champ->code[i];
    }
}

/*
 * Explanation of bit manipulation:
 * value << 8: shift the current value 8 bits to the left.
 * memory[start_pos + i]: fetch the current byte from memory.
 * |: bitwise OR operation combines shifted value with current byte.
 * e.g. 4-byte int in memory as 0x01 0x02 0x03 0x04:
 * Value starts as 0... so the initially we append 8 "0's" by shifting left
 * First iteration: value = 0x00 | 0x01 = 0x01
 * Second iteration: value = 0x0100 | 0x02 = 0x0102
 * Third iteration: value = 0x010200 | 0x03 = 0x010203
 * Fourth iteration: value = 0x01020300 | 0x04 = 0x01020304
 */

int read_direct_value(const unsigned char *memory, int start_pos) {
    int value = 0;
    for (int i = 0; i < 4; ++i) { // 4-byte integers
        // read and accumulate each byte
        value = (value << 8) | memory[start_pos + i];
    }
    return value;
}

