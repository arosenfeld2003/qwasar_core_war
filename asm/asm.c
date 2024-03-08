//#include "op.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // for exit

/*
 * asm.c
 *  Assembler for corewar warrior programs
 */

#define USAGE "usage: ./asm <program>"
#define MAX_LINE_LENGTH 1024
#define MAX_INST_LENGTH 3
#define LDELIMS " \t\n"         /* label delims */
#define OPDELIMS " \t\n,"       /* operand delims */

// TEMP OP codes; use op.h
#define OP_LIVE 1
#define OP_LD 2
#define OP_ST 3

typedef struct {
    char *label;
    char *instruction;
    char *operands[MAX_INST_LENGTH]; // Changed from 3
    int operand_count;
} inst_t;

void parse_program(FILE *input_file, FILE *output_file);
void parse_line(char *line, inst_t *inst);
void output_inst(inst_t *inst);
void write_instruction(FILE *output_file, inst_t *inst);
int get_opcode(inst_t *inst);

int main(int argc, char **argv)
{
    if (argc !=  2) {
        fprintf(stderr, "%s\n", USAGE);
        return 1;
    }

    // open file
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        perror("Error opening file");
        return 1;
    }
    
    // create output file
    FILE *output_file = fopen("a.cor", "w"); // overwrites if file exists
    if (output_file == NULL) {
        perror("Error creating output file"); 
        return 1;
    }

    // TODO: write header for output

    parse_program(input_file, output_file);

    fclose(input_file);
    fclose(output_file);
    // TODO free any mallocs
    return 0;
}

void parse_program(FILE *input_file, FILE *output_file)
{
    char line[MAX_LINE_LENGTH];

    while (fgets(line, MAX_LINE_LENGTH, input_file)) {
        // Skip lines starting with #
        if (line[0] == '#') {
                continue;
        }

        inst_t inst = {};

        // TEST
        //printf("Line from file: %s", line); // no \n bc line has it

        parse_line(line, &inst);
        write_instruction(output_file, &inst);
        //free_inst() // TODO
    }
}

void parse_line(char *line, inst_t *inst)
{
    char *token;
    char *saveptr;  // required by strtok_r to use internally

    // TODO parse .name/.comment

    token = strtok_r(line, LDELIMS, &saveptr); // returns ptr to 1st token
    if (token && token[strlen(token) - 1] == ':') { // label found
        inst->label = strdup(token);  // store label name
        token = strtok_r(NULL, LDELIMS, &saveptr); // pass NULL to continue line
    }

    if (token) {
        inst->instruction = strdup(token);  // store instruction to struct

        // parse operands
        while ((token = strtok_r(NULL, OPDELIMS, &saveptr)) != NULL
                && inst->operand_count < MAX_INST_LENGTH) {
            inst->operands[inst->operand_count++] = strdup(token);
        }
    }
    // TEST
    //output_inst(inst);
    //printf("*********\n");
}

void write_instruction(FILE *output_file, inst_t *inst)
{
    int opcode;  /* in base 10 despite encoded in hex */
    int param;              /* value of a parameter */

    // set opcode based on instruction
    opcode = get_opcode(inst);

    // write to file?
    fwrite(&opcode, sizeof(opcode), 1, output_file);

    switch (opcode) {  // TODO refactor to functions
        case OP_LIVE:
            param = atoi(inst->operands[0] + 1); /* bypass % */
            fwrite(&param, sizeof(param), 1, output_file);
            break;
        case OP_LD:
        case OP_ST:       // TODO ST is similar but needs r check on 1st param
            // handle first param
            if (inst->operands[0][0] == '%') {
                param = atoi(inst->operands[0] + 1); /* bypass * % */
                fwrite(&param, sizeof(param), 1, output_file);
            }
            else {
                param = atoi(inst->operands[0]);    /* indirect value */
                fwrite(&param, sizeof(param), 1, output_file);
            }
            // handle 2nd param
            fwrite(&(inst->operands[1][1]), 1, 1, output_file);  /* skips 'r' */
            break;
        default:
            return;     
    }
}

int get_opcode(inst_t *inst)
{
    if (strcmp(inst->instruction, "live") == 0)
        return OP_LIVE;
    if (strcmp(inst->instruction, "ld") == 0)
        return OP_LD;
    if (strcmp(inst->instruction, "st") == 0)
        return OP_ST;
    return -1;       // bad instruction
}

void output_inst(inst_t *inst)
{
    printf("Label: %s\n", inst->label);
    printf("Instruction: %s\n", inst->instruction);
    for (int i = 0; i < inst->operand_count; i++)
        printf("Operand %d: %s\n", i, inst->operands[i]);
}
