#include "header.h"

void parse_arguments(int argc, char** argv, vm_state_t *vm_state) {
    // Initialize dump_cycle to -1; no dump
    vm_state->dump_cycle = -1;
    // Initialize champs to 0
    vm_state->champion_count = 0;

    for (int i = 1; i < argc; i++) {
        // Check argv for -dump
        if(strcmp(argv[i], "-dump") == 0) {
            // If there's an argument after -dump
            if (i + 1 < argc) {
                vm_state->dump_cycle = atoi(argv[i+1]);
                i++;
            } else {
                printf("Error: -dump option requires number of cycles\n");
                exit(1);
            }
        } else {
            // Check if there's room to store champion files
            if (vm_state->champion_count < MAX_CHAMPIONS) {
                vm_state->champions[vm_state->champion_count++] = *argv[i];
            } else{
                printf("Error: Too many champion files\n");
                exit(1);
            }
        }
    }
}
