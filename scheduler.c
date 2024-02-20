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
    char **binary_instructions; // binary instructions in each program
    // int execution_cycles[NUM_INSTRUCTIONS]; // execution cycles for each instruction
} Program;

// Define the function prototypes
// void execute_instruction(Warrior* warrior);
// void schedule(Warrior warriors[], int num_warriors);


// execute the next
// void execute_instruction(Warrior* warrior, unsigned char* memory) {
void execute_instruction(Program *program) {
    int current_instruction_index = program->instruction_index;
    char *binary_instruction = program->binary_instructions[current_instruction_index];
    // simulate execution of binary_instruction
    printf("Program %d executing instruction %d: %s\n", program->program_number,current_instruction_index + 1, binary_instruction);
    // move to next instruction
     program->instruction_index++;  
}

// void schedule(Warrior warriors[], int num_warriors, unsigned char* memory) {
void schedule(Program programs[NUM_PROGRAMS]) {
    int cycle = 1;
    int program_index = 0;
    // Assuming each program has the same num of instructions
    int num_instructions = NUM_INSTRUCTIONS;
    // int current_warrior_index = 0;

    // Main game loop
    while (1) {
        printf("Cycle %d\n", cycle);
        // for (int i = 0; i < NUM_PROGRAMS; i++) {
        Program *program = &programs[program_index];
        int current_instruction_index = program->instruction_index;
        if (current_instruction_index < num_instructions) {
            execute_instruction(program);
        }
        program_index = (program_index + 1) % NUM_PROGRAMS; // Alternate between programs
        // Check if all programs have finished executing
        int all_programs_finished = 1;
        for (int i = 0; i < NUM_PROGRAMS; i++) {
            if (programs[i].instruction_index < num_instructions) {
                all_programs_finished = 0;
                break;
            }
        }
     
        if (all_programs_finished) {
            break; // Exit the loop if all programs have finished executing
        }
        cycle++; // Move to next cycle
    }
}

int main() {
    // Initialize programs with binary instructions
    char *program1_instructions[NUM_INSTRUCTIONS] = {
        "binary_instruction_1",
        "binary_instruction_2",
        "binary_instruction_3",
        "binary_instruction_4"
    };
    char *program2_instructions[NUM_INSTRUCTIONS] = {
        "binary_instruction_1",
        "binary_instruction_2",
        "binary_instruction_3",
        "binary_instruction_4"
    };
    Program programs[NUM_PROGRAMS] = {
        {1, 0, program1_instructions}, // Program 1
        {2, 0, program2_instructions}, // Program 2
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
cycle delta = 5

*/