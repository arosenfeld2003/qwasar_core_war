#include <stdio.h>
#include <stdlib.h>

// #define NUM_WARRIORS 2
// #define MAX_CYCLES 1000
// #define MAX_WARRIORS 10
// #define MEM_SIZE 1000
#define NUM_PROGRAMS 3
#define NUM_INSTRUCTIONS 7

// Warrior struct

typedef struct {
    int program_number;
    int instruction_index;
    int execution_cycles[NUM_INSTRUCTIONS]; // execution cycles for each instruction
} Program;

// Define the function prototypes
// void execute_instruction(Warrior* warrior);
// void schedule(Warrior warriors[], int num_warriors);


// execute the next
// void execute_instruction(Warrior* warrior, unsigned char* memory) {
void execute_instruction(Program *program) {
    int current_instruction_index = program->instruction_index;
    int cycles_to_execute = program->execution_cycles[current_instruction_index];
    // Simulate execution by waiting for the specified number of cycles
    // This could involve updating program state, registers, etc.
    printf("Program %d executing instruction %d for %d cycles\n", program->program_number,current_instruction_index + 1, cycles_to_execute);
    // Move to the next instruction
    program->instruction_index++;
}

// void schedule(Warrior warriors[], int num_warriors, unsigned char* memory) {
void schedule(Program programs[NUM_PROGRAMS]) {
    int cycle = 1;
    // int current_warrior_index = 0;

    // Main game loop
    while (1) {
        printf("Cycle %d\n", cycle);
        for (int i = 0; i < NUM_PROGRAMS; i++) {
            Program *program = &programs[i];
            int execution_instruction_index = program->instruction_index;
            if (current_instruction_index < NUM_INSTRUCTIONS) {
                int execution_cycles = program->execution_cycles[current_instruction_index];
                // check if the instructions tarts execution on this cycle
                if (execution_cycles  == cycle) {
                    execute_instruction(program);
                }
            }
        }
        // Check if all programs have finished executing
        int all_programs_finished = 1;
        for (int i = 0; i < NUM_PROGRAMS; i++) {
            if (programs[i].instruction_index < NUM_INSTRUCTIONS) {
                all_programs_finished = 0;
                break;
            }
        }
        if (all_programs_finished) {
            break;
        }
        cycle++;
    }
}

int main() {
    // Initialize warriros ane memory
    Program programs[NUM_PROGRAMS] = {
         {1, 0, {1, 5, 1, 1, 2, 0, 0}}, // Program 1
        {2, 0, {3, 1, 5, 1, 0, 0, 0}}, // Program 2
        {3, 0, {3, 2, 3, 2, 0, 0, 0}}  // Program 3
    };

    schedule(programs);
    return 0;
};

//OK, for the scheduler . . . 
// the instruction (eg "sti r2, 23, %34") needs to be converted to a scheduler input array
// based on the OpTab in op.c, we get the cycles; the scheduler input array looks like this:
// {1, 0, {0x0b, 25, 0x02, 0x00, 0x17, 0x00, 0x00, 0x00, 0x22}}
// assembler output is binary; vm parses binary
// assembler => scheduler, output goes to vm?
// counter tracks the place in register in vm
// tony created a shell file script to generatae binary output; takes in x and gives binary
// use instruction number . . . sti 0b78 on page 7 . . .will give binary; one line of champion
// op.h has cycles 1536; the programs run in parallel
// each champ will have its own counter
/* vm needs mult counters?
MARS executes timesharing; single instruction of P1, then single instruction of P2


*/