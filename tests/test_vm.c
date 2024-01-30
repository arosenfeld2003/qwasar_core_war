#include "../src/vm/main.c"
#include <stdio.h>
#include <assert.h>

void test_initialization() {
    unsigned char *vm = initialize_vm();
    assert(vm != NULL);
    free_vm(vm);
}

int test() {
    test_initialization();
    // more tests
    printf("All tests passed successfully.\n");
    return 0;
}