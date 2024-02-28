#include "header.h"

void parse_arguments(int argc, char** argv, vm_state_t *vm_state) {
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
