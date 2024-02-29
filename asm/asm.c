//#include "op.h"
#include "asm_utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // for exit

/*
 * asm.c
 *  Assembler for corewar warrior programs
 */

#define USAGE "usage: ./asm <program>"
#define MAX_LINE_LENGTH 1024
#define LDELIMS " \t\n"         /* label delims */
#define OPDELIMS " \t\n,"       /* operand delims */
#define BYTE 8                  /* byte size */
#define REG_CHAR 'r'            /* TODO put in op.h? */
#define TYPE_TABLE_INDEX 2      /* where type table is in op_tab */

// TEMP OP codes; use op.h
#define OP_LIVE 1
#define OP_LD 2
#define OP_ST 3

typedef struct {
    char *label;
    char *name;
    char *args[3];
    int arg_count;           /* operand count */
} inst_t;

void parse_program(FILE *input_file, FILE *output_file);
void parse_line(char *line, inst_t *inst);
void output_inst(inst_t *inst);
void write_instruction(FILE *output_file, inst_t *inst);
int get_opcode(inst_t *inst);
int validate_args(inst_t *inst, int opcode);

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
                && inst->operand_count < MAX_ARGS_NUMBER) {
            inst->operands[inst->operand_count++] = strdup(token);
        }
    }
    // TEST
    output_inst(inst);
    printf("*********\n");
}

int write_instruction(FILE *output_file, inst_t *inst)
{
    int opcode;  /* in base 10 despite encoded in hex */
    int param;              /* value of a parameter */

    // set opcode based on instruction
    opcode = get_opcode(inst);

    // validate 
    if (validate_args(inst, opcode) == 0)
        return 0;

    // write to file?
    write(output_file, opcode, 1);
    //fwrite(&opcode, sizeof(opcode), 1, output_file);

    switch (opcode) {  // TODO refactor to functions
        case OP_LIVE:
            param_byte = 0b01000000;
            write(output_fd, &param_byte, 1);
            prog_num = my_atoi(inst->operands[0]);
            write(output_fd, &prog_num, 4);
            break;
        case OP_LD:
            

            if (inst->operands[1][0] == '%') {
                param = my_atoi(inst->operands[0] + 1); /* skip % */
                

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
        case OP_ADD:  // 3 registers
            for (int i = 0; i < inst->operand_count; i++)
                // TODO does atoi pad with 0's?
                write(champ_fd, atoi(inst->operands[i][1]), DIR_SIZE); /* skips 'r' */
        case OP_SUB:  // 3 registers
            for (int i = 0; i < inst->operand_count; i++)
                // TODO does atoi pad with 0's?
                write(champ_fd, atoi(inst->operands[i][1]), DIR_SIZE); /* skips 'r' */
        case OP_AND:  // 3 reisters
            for (int i = 0; i < inst->operand_count; i++)
                // TODO does atoi pad with 0's?
                write(champ_fd, atoi(inst->operands[i][1]), DIR_SIZE); /* skips 'r' */
        case OP_OR:  // 3 registers
            for (int i = 0; i < inst->operand_count; i++)
                // TODO does atoi pad with 0's?
                write(champ_fd, atoi(inst->operands[i][1]), DIR_SIZE); /* skips 'r' */
        case OP_XOR: // 3 registers
                // TODO does atoi pad with 0's?
                write(champ_fd, atoi(inst->operands[i][1]), DIR_SIZE); /* skips 'r' */

        case OP_ZJMP:  // 1 index
        case OP_LDI:
        case OP_STI:
        case OP_FORK:
        case OP_LLD:
        case OP_LLDI:
        case OP_LFORK:
        case OP_AFF:
        default:
            return;     
    }
}

int validate_args(inst_t *inst, int opcode)
{
    for (int i = 0; i < inst->arg_count; i++) {
        char type = T_IND;  /* indirect is default */
        char prefix = inst->args[i][0];

        /* examine prefix for type */
        if (prefix == REG_CHAR)
            type = T_REG;
        else if (prefix == DIRECT_CHAR)
            type = T_DIR;

        /* check if not valid */
        if ((type & op_tab[opcode - 1][TYPE_TABLE_INDEX][i]) == 0)
            return 0;
    }
    return 1;
}

/*
 * return: index plus 1 for the opcode
 */
int get_opcode(inst_t *inst)
{
    for (int i = 0; op_tab[i][0] != NULL; i++) {
        if (my_strcmp(optab[i][0], inst->name) == 0)
            return i + 1;
    }
    return -1; // bad instruction
}

void output_inst(inst_t *inst)
{
    printf("Label: %s\n", inst->label);
    printf("Instruction: %s\n", inst->instruction);
    for (int i = 0; i < inst->operand_count; i++)
        printf("Operand %d: %s\n", i, inst->operands[i]);
}
