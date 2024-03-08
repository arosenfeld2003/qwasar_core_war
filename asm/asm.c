#include "../op.h"
#include "asm_utils.h"
#include "hash_table.h"
#include "../corewar.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // for exit
#include <fcntl.h>
#include <unistd.h>

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

typedef struct {
    char *name;
    char *comment;
} head_t;

void parse_program(int input_fd, int output_fd);
void parse_line(char *line, inst_t *inst, int pass_num, int *offset, htable **ht_labels, head_t *head_ptr);
void output_inst(inst_t *inst);
int write_instruction(int output_fd, inst_t *inst, htable **ht_labels);
int get_opcode(inst_t *inst);
int make_valid_ptype_byte(inst_t *inst, int opcode);
int is_valid_label(char *label);
int has_arg_types(char *inst_name);
int arg_num2byte_pos(int arg_num);
char *fd_gets(int fd, char* buf, size_t n);

static char line[1024]; //temp

int main(int argc, char **argv)
{
    if (argc !=  2) {
        fprintf(stderr, "%s\n", USAGE);
        return 1;
    }

    // open file
    int input_fd = open(argv[1], O_RDONLY);
    if (input_fd == -1) {
        perror("Error opening file");    // TODO remove
        return 1;
    }
    // create output file
    int output_fd = open("a.cor", O_WRONLY | O_CREAT | O_TRUNC,
            S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); // overwrites if file exists
    if (output_fd == 0) {
        perror("Error creating output file"); // TODO remove
        return 1;
    }

    parse_program(input_fd, output_fd);

    close(input_fd);
    close(output_fd);
    // TODO free any mallocs
    return 0;
}

void parse_program(int input_fd, int output_fd)
{
    char line[MAX_LINE_LENGTH];
    int offset = 0;                         /* for label byte offset */
    head_t header = {};

    htable *ht_labels;                      /* table for labels */
    ht_create(&ht_labels, 0);                 /* create label hash table */

    //while (fgets(line, MAX_LINE_LENGTH, input_fd)) { /* first pass */
    while (fd_gets(input_fd, line, sizeof(line))) {
        inst_t inst = {};

        parse_line(line, &inst, 1, &offset, &ht_labels, &header);
        free_inst(&inst);
    }

    lseek(input_fd, 0, SEEK_SET);  /* reset to top of file */
    write(output_fd, header.name, my_strlen(header.name));
    printf("DEBUG: header name: %s\n", header.name);
    write(output_fd, header.comment, my_strlen(header.comment));
    printf("DEBUG: header comment: %s\n", header.comment);

    //while (fgets(line, MAX_LINE_LENGTH, input_fd)) { /* second pass */
    while (fd_gets(input_fd, line, sizeof(line))) {
        // Skip lines starting with #
        if (line[0] == '#') {
            continue;
        }
        inst_t inst = {};

        parse_line(line, &inst, 2, &offset, &ht_labels, &header);
        if (inst.name)
            write_instruction(output_fd, &inst, &ht_labels);
        free_inst(&inst);
    }
    ht_free(&ht_labels);
    
}

void parse_line(char *line, inst_t *inst, int pass_num, int *offset, htable **ht_labels, head_t *head_ptr)
{
    char *token;
    int table_index, num_args;
    char *saveptr;  // required by strtok_r to use internally

    token = strtok_r(line, LDELIMS, &saveptr); // returns ptr to 1st token

    // parse .name/.comment
    if (token && my_strcmp(token, NAME_CMD_STRING) == 0) {
        token = strtok_r(NULL, "\n", &saveptr); // get next item
        head_ptr->name = my_strdup(token);
        token = strtok_r(NULL, LDELIMS, &saveptr);
    }
    else if (token && my_strcmp(token, COMMENT_CMD_STRING) == 0) {
        token = strtok_r(NULL, "\n", &saveptr);
        head_ptr->comment = my_strdup(token);
        token = strtok_r(NULL, LDELIMS, &saveptr);
    }
    
    // check for label
    int tok_len = my_strlen(token);
    if (token && token[tok_len - 1] == LABEL_CHAR) {
        token[tok_len - 1] = '\0';          /* eliminate ':' */
        if (pass_num == 1) {
            if (!is_valid_label(token))
                exit(2);
            ht_add(ht_labels, token, *offset);
        }
        else
            inst->label = my_strdup(token);  // store label name
        token = strtok_r(NULL, LDELIMS, &saveptr); // pass NULL to continue line
    }

    if (token) {
        inst->name = my_strdup(token);  // store instruction to struct
        table_index = get_opcode(inst) - 1;
        num_args = op_tab[table_index].nbr_args;

        // parse operands
        while ((token = strtok_r(NULL, OPDELIMS, &saveptr)) != NULL
                && inst->arg_count < num_args) {
            if (pass_num == 1) {
                (*offset)++;    /* instruction byte */
                if (has_arg_types(inst->name))
                    (*offset)++;            /* ptype byte */
                inst->args[inst->arg_count] = my_strdup(token);
                switch (inst->args[inst->arg_count][0]) {
                    case REG_CHAR: *offset += REG_SIZE; break;
                    case DIRECT_CHAR: *offset += DIR_SIZE; break;
                    default:  *offset += IND_SIZE;
                }
            }
            else if (pass_num == 2)
                inst->args[inst->arg_count] = my_strdup(token);
            inst->arg_count++;
        }
    }
    // TEST
    if (pass_num == 2) {
        output_inst(inst);
        printf("*********\n");
    }
}

int write_instruction(int output_fd, inst_t *inst, htable **ht_labels)
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
    if (has_arg_types(inst->name))
        write(output_fd, &ptype_byte, 1);

    for (int i = 0; i < inst->arg_count; i++) {
        int arg, offset = 1;

        switch (inst->args[i][0]) {
            case REG_CHAR:
                arg = my_atoi(inst->args[i] + offset);   /* +1 for 'r' */
                write(output_fd, &arg, REG_SIZE);
                break;
            case DIRECT_CHAR: {
                if (inst->args[i][1] && inst->args[i][1] == LABEL_CHAR) {
                    int index = ht_find_index(ht_labels, &inst->args[i][2]);
                    if (index == -1)
                        exit(1);
                    arg = (*ht_labels)->list[index]->value;
                    printf("DEBUG: label: %s; offset: %d\n", &inst->args[i][2], arg);
                }
                else
                    arg = my_atoi(inst->args[i] + offset);   /* +1 for '%' */
                write(output_fd, &arg, DIR_SIZE);
                break;
            }
            case LABEL_CHAR: {
                int index = ht_find_index(ht_labels, &inst->args[i][1]);
                if (index == -1)
                    exit(1);
                arg = (*ht_labels)->list[index]->value;
                write(output_fd, &arg, IND_SIZE);
                printf("DEBUG: label: %s; offset: %d\n", &inst->args[i][1], arg);
                break;
            }
            default:
                arg = my_atoi(inst->args[i]);
                write(output_fd, &arg, IND_SIZE);
        }
    }
    return 1;
}

void free_inst(inst_t *inst) {
    free(inst->label);
    free(inst->name);
    for (int i = 0; i < inst->arg_count; i++) {
        free (inst->args[i]);
    }
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
        if ((type & op_tab[opcode - 1].type[i]) == 0)
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
    for (int i = 0; op_tab[i].mnemonique != NULL; i++) {
        if (my_strcmp(op_tab[i].mnemonique, inst->name) == 0)
            return i + 1;
    }
    return -1; // bad instruction
}

void output_inst(inst_t *inst)
{
    printf("Label: %s\n", inst->label);
    printf("Instruction: %s\n", inst->name);
    for (int i = 0; i < inst->arg_count; i++)
        printf("Operand %d: %s\n", i, inst->args[i]);
}

int is_valid_label(char *label)
{
    char *valid_chars = LABEL_CHARS;
    int valid_len = my_strlen(LABEL_CHARS); 
    int label_len = my_strlen(label); 
    int is_valid;

    for (int i = 0; i < label_len-1; i++) {
        is_valid = 0;
        for (int j = 0; i < valid_len; j++) {
            if (label[i] == valid_chars[j]) {
                is_valid = 1;
                break;
            }
        }
        if (is_valid == 0)
            return 0;
    }
    return 1;
}

/*
 * purpose: used to determine if instruction needs ptypes byte
 */
int has_arg_types(char *inst_name)
{
    return (
        my_strcmp(inst_name, "live") != 0 &&
        my_strcmp(inst_name, "zjmp") != 0 &&
        my_strcmp(inst_name, "fork") != 0 &&
        my_strcmp(inst_name, "lfork") != 0
    );
}

char *fd_gets(int fd, char* buf, size_t n) {
    if (n == 0 || buf == NULL) return NULL; // Invalid input

    size_t i = 0;
    while (i < n - 1) {
        char c;
        ssize_t read_size = read(fd, &c, 1);

        if (read_size == 0) { // End of file
            if (i == 0) return NULL; // No data read
            break;
        } else if (read_size < 0) { // Error
            return NULL;
        }

        buf[i++] = c;
        if (c == '\n') break; // Newline is read, stop
    }

    buf[i] = '\0'; // Null-terminate the string
    return buf;
}
