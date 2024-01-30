#include "include/op.h"
#include "instructions.c"
#include <stdio.h>
#include <stdlib.h>

void convert_to_hex(int n) {
    for (i = int; i >= 0; i -= 1) {
        bits[i] = '0' + (n & 0x01);
        n >>= 1;
    }
}

void mod(int cur_adr, int offset) {
    return (cur_adr + offset) % IDX_MOD
}






