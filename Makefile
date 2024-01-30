CC = gcc
CFLAGS = -Wall -Wextra -Werror

# VM source files without the main VM program file
VM_UTILS = src/vm/vm.c src/vm/vm_utils.c src/common/utils.c

# VM main program file
VM_MAIN = src/vm/main.c

# VM test program
TEST_VM = tests/test_vm.c

all: vm assembler test_vm

vm:
	$(CC) $(CFLAGS) -o corewar $(VM_MAIN) $(VM_UTILS) -I include

assembler:
	$(CC) $(CFLAGS) -o asm src/assembler/main.c src/assembler/assembler.c src/assembler/assembler_utils.c src/common/utils.c -I include

test_vm:
	$(CC) $(CFLAGS) -o test_vm $(TEST_VM) $(VM_UTILS) -I include

clean:
	rm -f corewar asm test_vm

.PHONY: all clean vm assembler test_vm
