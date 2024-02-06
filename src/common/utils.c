#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parse_arguments(int argc, char **argv, vm_state_t *vm_state) {
    vm_state->dump_cycle = -1;  // Default: no memory dump
    vm_state->champion_count = 0;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-dump") == 0 && (i + 1 < argc)) {
            vm_state->dump_cycle = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-n") == 0 && (i + 2 < argc)) {
            // -n -> prog_number, then champion_file_name
            int prog_number = atoi(argv[++i]);
            char* file_path = argv[++i];

            if (vm_state->champion_count < MAX_CHAMPIONS) {
                champion_t *champ = &vm_state->champions[vm_state->champion_count++];
                champ->id = prog_number;
                champ->file_path = file_path;
                // start_address default to 0 initially
                champ->start_address = 0; // possibly assigned later
            }
        } else if (strcmp(argv[i], "-a") == 0 && (i + 1 < argc)) {
            // -a -> next champion's load address
            int address = atoi(argv[++i]);
            if (vm_state->champion_count > 0) {
                // Apply the address to the last added champion (-a follows -n)
                vm_state->champions[vm_state->champion_count - 1].start_address = address;
            }
        } else {
            // Assume any other argument is a champion file name
            if (vm_state->champion_count < MAX_CHAMPIONS) {
                champion_t *champ = &vm_state->champions[vm_state->champion_count++];
                champ->id = vm_state->champion_count;  // Assign ID based on order added
                champ->file_path = argv[i];
                champ->start_address = 0; // Default start address, to be assigned later
            }
        }
    }
}
