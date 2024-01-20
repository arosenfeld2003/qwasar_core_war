/*
 * import `get_arg_value`, `read_memory`, `write_register, write_memory`, `update_carry_flag`, and `create_new_program`
 * */


// Function to check if carry is 1 and perform a conditional jump
void zjmp(int carry, int index) {
    if (carry == 1) {
        counter = (counter + index) % IDX_MOD; // Jump to index if carry is 1
    }
}

// Function to perform load indirect operation
void ldi(int index1, int index2, int register_dest) {
    int arg1 = get_arg_value(index1); // Get value at index1
    int arg2 = get_arg_value(index2); // Get value at index2
    int sum_result = (arg1 + arg2) % IDX_MOD; // Calculate sum modulo IDX_MOD
    int value = read_memory(counter + sum_result); // Read memory at counter + sum_result
    write_register(register_dest, value); // Write value to destination register
}

// Function to perform store indirect operation
void sti(int register_source, int index1, int index2) {
    int source_register_value = read_register(register_source); // Read value from source register
    int arg1 = get_arg_value(index1); // Get value at index1
    int arg2 = get_arg_value(index2); // Get value at index2
    int sum_result = (arg1 + arg2) % IDX_MOD; // Calculate sum modulo IDX_MOD
    write_memory(counter + sum_result, source_register_value); // Write source register value to memory
}

// Function to create a new program using fork operation
void fork(int index) {
    int new_counter = counter + index % IDX_MOD; // Calculate new counter value
    create_new_program(new_counter); // Create a new program with the new counter value
}

// Function to perform long load operation
void lld(int index1, int register_dest) {
    int arg1 = get_arg_value(index1); // Get value at index1
    write_register(register_dest, arg1); // Write value to destination register
    update_carry_flag(arg1); // Update the carry flag
}

// Function to perform long load indirect operation
void lldi(int index1, int index2, int register_dest) {
    int arg1 = get_arg_value(index1); // Get value at index1
    int arg2 = get_arg_value(index2); // Get value at index2
    int sum_result = arg1 + arg2; // Calculate sum
    int value = read_memory(counter + sum_result); // Read memory at counter + sum_result
    write_register(register_dest, value); // Write value to destination register
    update_carry_flag(value); // Update the carry flag
}

// Function to create a new program using long fork operation
void lfork(int index) {
    int new_counter = counter + index; // Calculate new counter value
    create_new_program(new_counter); // Create a new program with the new counter value
}

// Function to display a character to stdout
void aff(int register_source) {
    int ascii_code = read_register(register_source); // Read value from source register
    char output_char = (char)(ascii_code % 256); // Apply modulo 256 to get ASCII character
    printf("%c", output_char); // Display the character
}

