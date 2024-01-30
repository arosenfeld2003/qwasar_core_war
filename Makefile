# https://www.gnu.org/software/make/manual/make.html

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: vm assembler

vm:
	$(CC) $(CFLAGS) -o corewar src/vm/main.c src/vm/vm.c src/vm/vm_utils.c src/common/utils.c -I include

assembler:
	$(CC) $(CFLAGS) -o asm src/assembler/main.c src/assembler/assembler.c src/assembler/assembler_utils.c src/common/utils.c -I include

test_vm:
	$(CC) $(CFLAGS) -o test_vm tests/test_vm.c

clean:
	rm -f corewar asm test_vm

.PHONY:
	all clean vm assembler test_vm

