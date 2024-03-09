#include "header.h"
#include <stdio.h>

void inst_live(struct vm_state *vm, struct champion *champ, const int args[], int args_num) {
    int player_num = args[0];
    if (player_num >= 1 && player_num <= MAX_CHAMPIONS) {
        printf("Player %d is alive.\n", player_num);
        champ->is_alive = 1;
    } else {
        printf("Player not found: %d\n", player_num);
    }
}

void inst_ld(struct vm_state *vm, struct champion *champ, const int args[], int args_num) {
    int value = args[0];
    int register_dest = args[1];

    if (register_dest < 1 || register_dest > REG_NUMBER) {
        printf("Error: Invalid register number in 'ld' instruction.\n");
        return;
    }
    champ->state.registers[register_dest - 1] = value;
    champ->state.pc += 6;
}

void inst_st(struct vm_state *vm, struct champion *champ, const int args[], int args_num) {
    int register_source = args[0];
    int index1 = args[1];
    int index2 = args[2];

    int source_register_value = read_register(champ, register_source);
    int arg1 = get_arg_value(vm, index1);
    int arg2 = get_arg_value(vm, index2);
    int sum_result = (arg1 + arg2) % IDX_MOD;

    write_memory(vm, champ->state.pc + sum_result, source_register_value);
}

void inst_zjmp(struct vm_state *vm, struct champion *champ, const int args[], int args_num) {
// void zjmp(champion_t *champion, int index) {
    int index = args[0];
    if (champ->state.carry == 1) {
        champ->state.pc = (champ->state.pc + index) % IDX_MOD;
    }
}

(struct vm_state *vm, struct champion *champ, const int args[], int args_num)void
// void inst_sti(champion_t *champion, int register_source, int index1, int index2) {
    int source_register_value = read_register(champion, register_source);
    int arg1 = get_arg_value((vm_state_t *) champion, index1);
    int arg2 = get_arg_value((vm_state_t *) champion, index2);
    int sum_result = (arg1 + arg2) % IDX_MOD;
    write_memory((vm_state_t *) champion, champion->state.pc + sum_result, source_register_value);
}

void fork(vm_state_t *vm_state, champion_t *champion, int index) {
    int new_counter = champion->state.pc + index % IDX_MOD;
    create_new_program(vm_state, champion, new_counter);
}

void lld(champion_t *champion, int index1, int register_dest) {
    int arg1 = get_arg_value((vm_state_t *) champion, index1);
    write_register(champion, register_dest, arg1);
    update_carry_flag(champion, arg1);
}

void lldi(champion_t *champion, int index1, int index2, int register_dest) {
    int arg1 = get_arg_value((vm_state_t *) champion, index1);
    int arg2 = get_arg_value((vm_state_t *) champion, index2);
    int sum_result = arg1 + arg2;
    int value = read_memory((vm_state_t *) champion, champion->state.pc + sum_result);
    write_register(champion, register_dest, value);
    update_carry_flag(champion, value);
}

void lfork(vm_state_t *vm_state, champion_t *champion, int index) {
    int new_counter = champion->state.pc + index;
    create_new_program(vm_state, champion, new_counter);
}

void aff(champion_t *champion, int register_source) {
    int ascii_code = read_register(champion, register_source);
    char output_char = (char)(ascii_code % 256);
    printf("%c", output_char);
}