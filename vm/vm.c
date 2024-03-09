#include "../include/header.h"
#include <fcntl.h> // open
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
    // current champion's state
    champion_state_t *current_state = &vm_state->champions[vm_state->current_champion_index].state;

    switch (cmd) {
        case 0x01: { // live
            // next 4 bytes represent the player's number
            int player_number = read_direct_value(vm_state->memory, vm_state->cycle_count + 1);
            printf("Player %d is alive\n", player_number);
            current_state->pc += 5;  // Update current champion's PC
            vm_state->cycle_count += 5; // Move past the instruction and its parameter
            printf("cmd LIVE executed\n");
            break;
        }
        case 0x02: { // ld
            int param_types = op_tab[1].type[0] | op_tab[1].type[1]; // combine flags
            int value = 0;

            // Parameter 1: Direct or Indirect fetch
            if (param_types & T_DIR) {
                value = read_direct_value(vm_state->memory, vm_state->cycle_count + 1);
            } else if (param_types & T_IND) {
                // ... (Indirect calculation and fetch)
            } else {
                // Invalid addressing mode - handle error!
            }

            // Parameter 2: Register
            int reg_num = vm_state->memory[vm_state->cycle_count + 5];

            // Load value into current champion register, update the PC
            current_state->registers[reg_num - 1] = value;
            current_state->pc += 6;

            printf("ld instruction executed\n");
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