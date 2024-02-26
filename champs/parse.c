#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAMPIONS 4

typedef struct {
    char *champions[MAX_CHAMPIONS];
    int champion_count;
    int dump_cycle;
} vm_state_t;



//int main(int argc, char** argv) {
//    vm_state_t vm_state;
//    parse_arguments(argc, argv, &vm_state);
//    printf("Dump cycle: %d\n", vm_state.dump_cycle);
//    printf("Champ count: %d\n", vm_state.champion_count);
//    for (int i = 0; i < vm_state.champion_count; i++) {
//        printf("CHamp file %d: %s\n", i+1, vm_state.champions[i]);
//    }
//    return 0;
//}