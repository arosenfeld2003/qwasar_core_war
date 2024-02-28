#include "../include/header.h"
#include <stdio.h>
#include <assert.h>

void test_mem_initialization() {
    unsigned char *vm = initialize_vm();
    assert(vm != NULL);
    free_vm(vm);
}

void test_read_write() {
    unsigned char *vm = initialize_vm();
    vm_state_t vm_state;
    vm_state.memory = vm;
    write_memory(vm_state.memory, 10, 0xAA); // Write a byte
    assert(read_memory(vm_state.memory, 10) == 0xAA); // Read the same byte and check
    printf("VM read/write have executed successfully.");
    free_vm(vm);
}

void test_live_instruction() {
    unsigned char *vm = initialize_vm();
    vm_state_t vm_state;
    vm_state.memory = vm;
    vm_state.pc = 0; // Start at the beginning of memory
    write_memory(vm_state.memory, 0, 0x01); // Write the opcode for 'live'
    write_int_to_memory(vm_state.memory, 1, 1234); // Write the champion number (e.g., 1234)
    unsigned char cmd = read_memory(vm_state.memory, vm_state.pc);
    printf("%d\n", cmd);
    handle_cmd(&vm_state, cmd);
    // pc should have advanced by 5 bytes, and 'live' action was was called
    assert(vm_state.pc == 5);
    printf("Test for 'live' instruction passed.\n");
    free_vm(vm_state.memory);
}

void test_ld_instruction() {
    unsigned char *vm = initialize_vm();
    vm_state_t vm_state;
    vm_state.memory = vm;
    vm_state.pc = 0; // Reset or set the PC for this test
    write_memory(vm_state.memory, 0, 0x02); // Write the opcode for 'ld'
    write_int_to_memory(vm_state.memory, 1, 5678); // Write the value to be loaded
    write_memory(vm_state.memory, 5, 1); // register 1
    unsigned char cmd = read_memory(vm_state.memory, vm_state.pc);
    printf("%d\n", cmd);
    handle_cmd(&vm_state, cmd);
    // Verify the value was loaded into the correct register and PC was updated
    assert(vm_state.registers[0] == 5678); // registers 0-indexed?
    assert(vm_state.pc == 6);
    printf("Test for 'ld' instruction passed.\n");
    free_vm(vm_state.memory);
}

int main() {
    test_mem_initialization();
    test_read_write();
    test_live_instruction();
    test_ld_instruction();
    printf("All tests passed successfully.\n");
    return 0;
}