#include "corewar.h"

/* from op.h
enum parameter_types {
    T_REG = 1,
    T_DIR = 2,
    T_IND = 4,
    T_LAB = 8
};

struct op_s {
    char *mnemonique;                       /* name of operation */
    char nbr_args;                          /* number of args taken */
    args_type_t type[MAX_ARGS_NUMBER];      /* args_type_t is a typedeffed char */
    char code;
    int nbr_cycles;
    int (*inst)(champion_t *, core_t *, code_t, int *);
};
*/

const op_t op_tab[] = {
//mnemonique, nbr_args, args_type, inst num, nbr_cycles, func
    {"live", 1, {T_DIR}, 1, 10, inst_live},
    {"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, inst_ld},
    {"st", 2, {T_REG, T_IND | T_REG}, 3, 5, inst_st},
    {"add", 3, {T_REG, T_REG, T_REG}, 4, 10, inst_add},
    {"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, inst_sub},
    {"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6, inst_and},
    {"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6, inst_or},
    {"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6, inst_xor},
    {"zjmp", 1, {T_DIR}, 9, 20, inst_zjmp},
    {"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, inst_ldi},
    {"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, inst_sti},
    {"fork", 1, {T_DIR}, 12, 800, inst_fork},
    {"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, inst_lld},
    {"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50, inst_lldi},
    {"lfork", 1, {T_DIR}, 15, 1000, inst_lfork},
    {"aff", 1, {T_REG}, 16, 2, inst_aff},
    {0, 0, {0}, 0, 0, 0}
};
