#include "../include/header.h"
#include "../include/vm_state.h"
#include <stdio.h>
#include <assert.h>

void test_initialization() {
    unsigned char *vm = initialize_vm();
    assert(vm != NULL);
    free_vm(vm);
}

void test_read_write() {
    unsigned char *vm = initialize_vm();
    write_memory(vm, 10, 0xAA); // Write a byte
    assert(read_memory(vm, 10) == 0xAA); // Read the same byte and check
    printf("VM read/write have executed successfully.");
    free_vm(vm);
}

void test_live_instruction() {
    vm_state_t vm;
    vm.pc = 0; // Start at the beginning of memory
    write_memory(vm.memory, 0, 0x01); // Write the opcode for 'live'
    write_int_to_memory(vm.memory, 1, 1234); // Write the champion number (e.g., 1234)
    unsigned char cmd = read_memory(vm.memory, vm.pc);
    printf("%d\n", cmd);
    handle_cmd(&vm, cmd);
    // The PC should have advanced by 5 bytes, and you might check if the 'live' action was performed
    assert(vm.pc == 5);
    printf("Test for 'live' instruction passed.\n");
}

void test_ld_instruction() {
    vm_state_t vm;
    vm.pc = 0; // Reset or set the PC for this test
    write_memory(vm.memory, 0, 0x02); // Write the opcode for 'ld'
    write_int_to_memory(vm.memory, 1, 5678); // Write the value to be loaded
    write_memory(vm.memory, 5, 1); // register 1
    unsigned char cmd = read_memory(vm.memory, vm.pc);
    printf("%d\n", cmd);
    handle_cmd(&vm, cmd);
    // Verify the value was loaded into the correct register and PC was updated
    assert(vm.registers[0] == 5678); // registers 0-indexed?
    assert(vm.pc == 6);
    printf("Test for 'ld' instruction passed.\n");
}

int main() {
    test_initialization();
    test_read_write();
    test_live_instruction();
    test_ld_instruction();
    printf("All tests passed successfully.\n");
    return 0;
}