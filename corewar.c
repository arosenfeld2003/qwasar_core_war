#include "include/header.h"
#include "instructions.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * corewar.c
 */

static char *USAGE = "usage: ./corewar [-dump nbr_cycle] [[-n prog_number] "
                     "[-a load_address] prog_name] ...";

// VM TO LOAD PROGRAMS - MVP
unsigned char memory[MEM_SIZE];

int main(int argc, char **argv) {
    initialize_vm();
    int live_count = 0;


    // MVP execution loop for game - runs until one champion wins or CYCLE_TO_DIE is reached
    for (int cycle = 0; cycle < CYCLE_TO_DIE; cycle++) {
        // for each program, load into memory
        for (int i = 0; i < MEM_SIZE; i++) {
            unsigned char inst = memory[i];
            // execute if we have an inst
            if (inst) {
                handle_cmd(inst);
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



//    int registers[REG_NUMBER][REG_SIZE] = {};
//    int counter = 0;
//    int carry_flag = 0;



//    // handle options & args
//    if (argc == 1) {        /* no args */
//        printf("%s\n", USAGE);
//        exit(2);
//    }
//
//    // array to track players alive...
//    int players_alive[MAX_CHAMPIONS] = {0};
//
//    for (int counter = 0; counter < MEM_SIZE; counter++) {
//        // get the instruction from the
//        unsigned char instruction = memory[counter];
//        // Decode and execute instruction -> For MVP, just directly call handle_cmd function
//        handle_cmd[instruction]
//    }
//
//    // open file
//    // read into memory
//    // assign "programs" name/number
//
//    // use assembler to covert file
//    // layout in memory
//
//    // main loop through memory
//    int i = 0;
//    while (carry_flag == 0) {
//        if (i >= REG_NUMBER)                                /* stay in bounds */
//            i = i % REG_NUMBER;
//
//        // run instructions
//        // handle_cmd(registers[i]);
//
//        printf("The program NBR_OF_PROGRAM(NAME_OF_PROGRAM) is alive.");
//        i++;
//    }
//
//    /* game over */
//    printf("The player NBR_OF_PROGRAM(NAME_OF_PROGRAM) is done.");

    return 0;
}



