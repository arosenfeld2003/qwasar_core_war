
/*
 * inst.c
 *  Instructions handling for corewar.c
 */


/*
 * Takes 1 parameter: 4 bytes that represent the player's number. Indicates the
 * player is alive.
 */
int inst_live()
{

}

/*
 * Takes 2 parameters: loads the first parameter to the second parameter. Second   
 * parameter is a register. Ex: ld 34, r3 loads the REG_SIZE bytes starting from
 * the Counter + 34 % IDX_MOD into r3.
 */
int inst_ld()
{

}

/*
 * Takes 2 parameters: Stores first parameter (a register) into the second
 * parameter (it can be another register or a number). Ex: st r4, 34 stores r4
 * at the address of Counter + 34 % IDX_MOD; st r3, r8 copies r3 into r8.
 */
int inst_st()
{

}

/*
 * Takes 3 parameters: 3 registers. Add the first to the second, and store the 
 * result to the third. Modifies the carry.
 */
int inst_add()
{

}

/*
 * Same as add, but Subtracting. Modifies the carry.
 */
int inst_sub()
{

}

/*
 * Same as add, and sub, but does a binary operation AND between the first and
 * the second, and storing the result in the third parameter. Modifies the carry.
 */
int inst_and()
{

}

/*
 * Same as and, but performing an OR.
 */
int inst_or()
{

}

/*
 * Same as and and or, but performing an XOR.
 */
int inst_xor()
{

}

