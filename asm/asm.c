#include "../op.h"
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
#define REG_BIN 0b01
#define DIR_BIN 0b10
#define IND_BIN 0b11

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
int make_valid_ptype_byte(inst_t *inst, int opcode);

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
    unsigned char ptype_byte = 0;     /* instruction byte */

    // set opcode based on instruction
    opcode = get_opcode(inst);

    if ((ptype_byte = make_valid_ptype_byte(inst, opcode)) == 0)
        return 0;

    /* write to file */
    write(output_fd, &opcode, 1);
    write(output_fd, &ptype_byte, 1);

    for (int i = 0; i < inst->arg_count; i++) {
        int arg;

        switch (inst->args[i][0]) {
            case 'r':
                arg = my_atoi(inst->args[i] + 1);   /* +1 for 'r' */
                write(output_fd, &arg, REG_SIZE);
                break;
            case '%':
                arg = my_atoi(inst->args[i] + 1);   /* +1 for '%' */
                write(output_fd, &arg, DIR_SIZE);
                break;
            default:
                arg = my_atoi(inst->args[i]);
                write(output_fd, &arg, IND_SIZE);
        }
    }
    return 1;
}

int make_valid_ptype_byte(inst_t *inst, int opcode)
{
    unsigned char ptype_byte = 0;     /* instruction byte */

    for (int i = 0; i < inst->arg_count; i++) {
        char type = T_IND;  /* indirect is default */
        char prefix = inst->args[i][0];
        int byte_pos = arg_num2byte_pos(i);

        /* examine prefix for type and store in pbyte */
        if (prefix == REG_CHAR) {
            type = T_REG;
            ptype_byte |= (REG_BIN << byte_pos);
        }
        else if (prefix == DIRECT_CHAR) {
            type = T_DIR;
            ptype_byte |= (DIR_BIN << byte_pos);
        }
        else
            ptype_byte |= (IND_BIN << byte_pos);

        /* check if not valid */
        if ((type & op_tab[opcode - 1][TYPE_TABLE_INDEX][i]) == 0)
            return 0;
    }
    return ptype_byte;
}

/*
 * purpose: convert argument number to position in pbyte
 *    note: could use formula y = -2x + 6 but switch is more intuitive
 */
int arg_num2byte_pos(int arg_num) {
    switch (arg_num) {
        case 0: return 6;
        case 1: return 4;
        case 2: return 2;
        default: return 0;
    }
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
