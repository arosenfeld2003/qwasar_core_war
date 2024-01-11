#include "op.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * corewar.c
 */

static char *USAGE = "usage: ./corewar [-dump nbr_cycle] [[-n prog_number] "
                     "[-a load_address] prog_name] ...";

int main(int argc, char **argv)
{
    int registers[REG_NUMBER][REG_SIZE] = {};
    char *next_cmd = NULL;
    int carry_flag = 0;                                 /* bool: 1: game over */

    // handle options & args
    if (argc == 1) {        /* no args */
        printf("%s\n", USAGE);
        exit(2);
    }

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
        handle_cmd(registers[i]);

        printf("The program NBR_OF_PROGRAM(NAME_OF_PROGRAM) is alive.");
        i++;
    }

    /* game over */
    printf("The player NBR_OF_PROGRAM(NAME_OF_PROGRAM) is done.");

    return 0;
}

// TODO
int handle_cmd(int cmd)
{
    switch (cmd) {

    }
}
