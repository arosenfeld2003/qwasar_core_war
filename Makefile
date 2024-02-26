CC = gcc
CFLAGS = -Wall -Wextra -Werror

# VM source files without the main VM program file
VM_UTILS = src/vm/vm.c src/vm/vm_utils.c

# COREWAR main program file
COREWAR_MAIN = corewar.c

# VM test program with its own main
TEST_VM = tests/test_vm.c

all: vm assembler

vm:
	$(CC) $(CFLAGS) -o corewar $(COREWAR_MAIN) $(VM_UTILS) -I include

assembler:
	$(CC) $(CFLAGS) -o asm src/assembler/main.c src/asm/asm.c

test_vm:
	$(CC) $(CFLAGS) -o test_vm $(TEST_VM) $(VM_UTILS) -I include

clean:
	rm -f corewar asm tests/test_vm

.PHONY: all clean vm assembler test_vm
