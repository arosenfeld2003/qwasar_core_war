#include "../../include/header.h"
#include "../../include/vm_state.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> // open
#include <unistd.h> // read, close

/*
 * corewar.c
 */

static char *USAGE = "usage: ./corewar [-dump nbr_cycle] [[-n prog_number] "
                     "[-a load_address] prog_name] ...";

int main(int argc, char **argv) {
    unsigned char *vm = initialize_vm()
    vm_state_t vm_state = {.dump_cycle = -1, .champion_count = 0};
    int next_id = 1; // Default starting ID
    int next_start_address = 0; // Default starting address
    parse_arguments(argc, argv, vm_state); // modifies vm_state
    load_programs_into_memory(vm, vm_state->champions, vm_state->champion_count);
    int live_count = 0;

    // execution loop for game - runs until one champion wins or CYCLE_TO_DIE is reached
    for (int cycle = 0; cycle < CYCLE_TO_DIE; cycle++) {
        // for each program, load into memory
        for (int i = 0; i < MEM_SIZE; i++) {
            unsigned char inst = memory[i];
            // execute if we have an inst
            if (inst) {
                handle_cmd(vm_state, inst);
                if (strcmp(*inst, "live") == 0) {
                    live_count++;
                }
            }
        }
        // decrease live_count by cycle_delta units: should this happen outside the loop?
        if (live_count >= NBR_LIVE) {
            CYCLE_TO_DIE = CYCLE_DELTA - CYCLE_DELTA;
        }
    }
    return 0;
}


