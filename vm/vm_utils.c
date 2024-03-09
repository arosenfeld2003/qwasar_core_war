#include "../include/header.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h> // read, close
#include <fcntl.h> // open

// read one byte from VM memory
unsigned char read_memory(vm_state_t *vm_state, size_t address) {
    if (address >= MEM_SIZE) {
        fprintf(stderr, "Read Memory Error: Address %zu out of bounds\n", address);
        exit(EXIT_FAILURE);
    }
    return vm_state->memory[address];
}


// write a byte to VM memory
void write_memory(vm_state_t *vm_state, size_t address, unsigned char value) {
    vm_state->memory[address] = value;
}

/*
 * Helper function to write a 4-byte integer to VM memory
 * Big Endian Format:
 * https://developer.arm.com/documentation/ddi0333/h/programmer-s-model/memory-formats/legacy-big-endian-format
 * */
void write_int_to_memory(vm_state_t *vm_state, size_t address, int value) {
    for (int i = 0; i < 4; i++) {
        write_memory(vm_state, address + 3 - i, (value >> (i * 8)) & 0xFF);
    }
}

void write_register(int reg_num, int value, vm_state_t *vm) {
    if (reg_num >= 1 && reg_num <= REG_NUMBER) {
        vm->champions[vm->current_champion_index].state.registers[reg_num - 1] = value;
    } else {
        printf("Error: Invalid register number in 'write_register'.\n");
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

// params: pointers to vm_state_t and the champion
void load_champion(vm_state_t *vm, champion_t *champ) {
    champ->state.pc = 0; // Reset program counter
    champ->state.carry = 0;  // Reset carry flag
    // Initialize registers if needed (e.g., set to 0)

    int fd = open(champ->file_path, O_RDONLY);
    // error handling
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Allocate memory for the program's code
    champ->code = (unsigned char *)malloc(champ->size * sizeof(unsigned char));
    if (champ->code == NULL) {
        perror("Failed to allocate memory for champion code");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Read the program into the allocated buffer
    ssize_t bytes_read = read(fd, champ->code, champ->size);
    if (bytes_read == -1) {
        perror("Error reading file");
        free(champ->code);
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Copy directly into VM memory using the provided champ
    for (ssize_t i = 0; i < bytes_read; ++i) {
        int address = (champ->start_address + i) % MEM_SIZE;
        vm->memory[address] = champ->code[i];
    }

    // Clean up: free the allocated code
    close(fd);
    free(champ->code);
    champ->code = NULL; // Avoid dangling pointer
}

void load_programs_into_memory(vm_state_t *vm, champion_t champions[], int num_champions) {
    for (int i = 0; i < num_champions; ++i) {
        load_champion(vm, &champions[i]); // Pass by reference
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

