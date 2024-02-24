#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAMPIONS 4

typedef struct {
    char *champions[MAX_CHAMPIONS];
    int champion_count;
    int dump_cycle;
} vm_state_t;

void parse_arguments(int argc, char** argv, vm_state_t *vm_state) {
    // Initialize dump_cycle to -1; no dump
    vm_state->dump_cycle = -1;
    // Initialize champs to 0
    vm_state->champion_count = 0;

    for (int i = 1; i < argc; i++) {
        
    }
}


int main() {
    char input[] = "  lorem,ipsum  ";
    printf("Last word: %s\n", last_word(input));
    return 0;
}