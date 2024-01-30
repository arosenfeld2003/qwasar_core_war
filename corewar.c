#include "include/op.h"
#include "instructions.c"
#include <stdio.h>
#include <stdlib.h>

/*
 * corewar.c
 */

static char *USAGE = "usage: ./corewar [-dump nbr_cycle] [[-n prog_number] "
                     "[-a load_address] prog_name] ...";

int main(int argc, char **argv) {
    int registers[REG_NUMBER][REG_SIZE] = {};
    char *next_cmd = NULL;
    int carry_flag = 0;                                 /* bool: 1: game over */

    // handle options & args
    if (argc == 1) {        /* no args */
        printf("%s\n", USAGE);
        exit(2);
    }

    // array to track players alive...
    int players_alive[MAX_CHAMPIONS] = {0};

    // for now just assign a number for the program -> this will be done by VM
    //

    // open file
    // read into memory
    // assign "programs" name/number

    // use assembler to covert file
    // layout in memory

    // main loop through memory
    int i = 0;
    while (carry_flag == 0) {
        if (i >= REG_NUMBER)                                /* stay in bounds */
            i = i % REG_NUMBER;

        // run instructions
        // handle_cmd(registers[i]);

        printf("The program NBR_OF_PROGRAM(NAME_OF_PROGRAM) is alive.");
        i++;
    }

    /* game over */
    printf("The player NBR_OF_PROGRAM(NAME_OF_PROGRAM) is done.");

    return 0;
}

//int main() {
//    // allocate memory for the VM
//    unsigned char *vm = malloc(MEM_SIZE * sizeof(unsigned char));
//
//    // check for allocation
//    if (vm == NULL) {
//        fprintf(stderr, "Memory allocation for VM has failed.\n");
//    } else {
//        printf("Memory allocation for VM successful");
//    }
//
//    // initialize memory to 0 (for now) -> maybe another value is better?
//    for (int i = 0; i < MEM_SIZE; i++) {
//        vm[i] = 0;
//    }
//
//    // CORE VM LOGIC HERE
//    // generate program number ->
//
//    // free the VM
//
//    free(vm);
//    printf("Memory allocation for VM freed...");
//
//    return 0;
//}

//// TODO
//int handle_cmd(int cmd)
//{
//    switch (cmd) {
//
//    }
//}
