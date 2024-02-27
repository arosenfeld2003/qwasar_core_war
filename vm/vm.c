#include "../include/header.h"
#include "../include/vm_state.h"
#include <fcntl.h> // open
#include <unistd.h> // read, close
#include <stdio.h> // perror
#include <stdlib.h> // malloc, free

unsigned char *initialize_vm() {
    // allocate memory for the VM
    unsigned char *vm = malloc(MEM_SIZE * sizeof(unsigned char));

    // check for allocation
    if (vm == NULL) {
        // handle error
        fprintf(stderr, "Memory allocation for VM has failed.\n");
    } else {
        // delete this later?
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

int handle_cmd(vm_state_t *vm_state, unsigned char cmd) {
    switch (cmd) {
        case 0x01: { // live
            // next 4 bytes represent the player's number
            int player_number = read_direct_value(vm_state->memory, vm->pc + 1);
            printf("Player %d is alive\n", player_number);
            vm_state->pc += 5; // Move past the instruction and its parameter
            printf("cmd LIVE executed\n");
            break;
        }
        case 0x02: { // ld
            // next bytes represent the value and the register number
            int value = read_direct_value(vm_state->memory, vm->pc + 1); // Simplified
            int reg_num = vm_state->memory[vm_state->pc + 5]; // Simplified
            if (reg_num >= 1 && reg_num <= REG_NUMBER) {
                vm_state->registers[reg_num - 1] = value;
                printf("Loaded %d into r%d\n", value, reg_num);
            }
            vm_state->pc += 6; // Adjust based on actual parameter sizes
            printf("cmd LD executed\n");
            break;
        }
        case 0x03:
            // (st)
            // Takes 2 parameters:
            // Stores first parameter (a register) into the second parameter
            // (it can be another register or a number).
            // Ex: st r4, 34
            // stores r4 at the address of Counter + 34 % IDX_MOD;
            // st r3, r8 copies r3 into r8.
            printf("Mnemonic 0x03 executed\n");
            break;
        case 0x04:
            // (add)
            // Takes 3 parameters: 3 registers.
            // Add the first to the second, and store the result to the third.
            // Modifies the carry.
            printf("Mnemonic 0x04 executed\n");
            break;
        case 0x05:
            // (sub)
            // Same as add, but Subtracting. Modifies the carry.
            printf("Mnemonic 0x05 executed\n");
            break;
        case 0x06:
            // (and)
            // Same as add, and sub, but does a binary operation AND
            // between the first and the second,
            // and storing the result in the third parameter. Modifies the carry.
            printf("Mnemonic 0x06 executed\n");
            break;
        case 0x07:
            // (or)
            // Same as and, but performing an OR.
            printf("Mnemonic 0x07 executed\n");
            break;
        case 0x08:
            // (xor)
            // Same as and & or, but performing an XOR.
            printf("Mnemonic 0x08 executed\n");
            break;
        case 0x09:
            // (zjmp)
            // Takes 1 parameter, that must be an index.
            // Jumps to this index if carry is 1.
            // Else, does nothing, but still consume time.
            // Zjmp %23 -> if carry == 1, Counter + 23 % IDX_MOD to Counter
            printf("Mnemonic 0x09 executed\n");
            break;
        case 0x0a:
            // (ldi)
            // Takes 3 parameters.
            // First two are indexes and the third one is a register
            // Ex: ldi 3, %4, r1 ->
            // reads IND_SIZ bytes from address Counter + 3 % IDX_MOD,
            // add 4 to this value (SumResult).
            // REG_SIZE byte are read
            // from the Counter + SumResult % IDX_MOD and copies to r1.
            printf("Mnemonic 0x0a executed\n");
            break;
        case 0x0b:
            // (sti)
            // Takes 3 parameters.
            // The first one is a register.
            // The other two can either be indexes or registers.
            // Ex: sti r2, %4, %5 ->
            // copies the content for r2 into Counter + (4 + 5) % IDX_MOD.
            printf("Mnemonic 0x0b executed\n");
            break;
        case 0x0c:
            // (fork)
            // Takes 1 parameter, an index.
            // Creates a new program, inheriting states from the parent,
            // and starting execution at counter + parameter % IDX_MOD
            printf("Mnemonic 0x0c executed\n");
            break;
        case 0x0d:
            // (lld)
            // Same as ld without the %IDX_MOD. Modifies the carry
            printf("Mnemonic 0x0d executed\n");
            break;
        case 0x0e:
            // (lldi)
            // Same as ldi without the %IDX_MOD. Modifies the carry
            printf("Mnemonic 0x0e executed\n");
            break;
        case 0x0f:
            // (lfork)
            // Same as fork without the %IDX_MOD.
            printf("Mnemonic 0x0f executed\n");
            break;
        case 0x10:
            // (aff)
            // Takes 1 parameter, a register.
            // Displays to stdout the character
            // corresponding to the ASCII code
            // of the content of the register (in base 10).
            // A 256 modulo is applied to this ASCII code.
            // Ex; aff r3 -> outputs '*' if r3 contains 42.
            printf("Mnemonic 0x10b executed\n");
            break;
        default:
            printf("invalid command passed to vm");
    }
    return 0;
}

void assign_program_numbers(champion_t champions[], int num_champions) {
    for (int i = 0; i < num_champions; ++i) {
        champions[i].id = i + 1; // Assign IDs starting from 1
    }
}

void load_champion(const char* file_path, int id, int start_address) {
    // Placeholder for the actual loading logic
    printf("Loading Champion: %s, ID: %d, Start Address: %d\n", file_path, id, start_address);
}

void load_programs_into_memory(vm_state_t vm, champion_t champions[], int num_champions) {
    for (int i = 0; i < num_champions; ++i) {
        int fd = open(champions[i].file_path, O_RDONLY);
        if (fd == -1) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }

        // Allocate memory for the program's code
        champions[i].code = (unsigned char *)malloc(champions[i].size * sizeof(unsigned char));
        if (champions[i].code == NULL) {
            perror("Failed to allocate memory for champion code");
            close(fd);
            exit(EXIT_FAILURE);
        }

        // Read the program into the allocated buffer
        ssize_t bytes_read = read(fd, champions[i].code, champions[i].size);
        if (bytes_read == -1) {
            perror("Error reading file");
            free(champions[i].code);
            close(fd);
            exit(EXIT_FAILURE);
        }

        // Manually copy the program code into the VM's memory at the specified start address
        for (ssize_t j = 0; j < bytes_read; ++j) {
            // handle circular memory (we need to use modulo here)
            // replace with the load_champion function above
            vm.memory[champions[i].start_address + j] = champions[i].code[j];
        }

        // Clean up
        close(fd);
        // Free the allocated code -> is it still needed??
        free(champions[i].code);
        champions[i].code = NULL; // Avoid dangling pointer
    }
}


