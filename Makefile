CC=gcc
CFLAGS=-Wall -Wextra -Werror -g

OBJ = main.o vm.o asm.o helpers.o
TEST_OBJ = tests.o vm.o helpers.o  # tests use vm and helpers


all: corewar

corewar: $(OBJ)
	$(CC) $(CFLAGS) -o corewar $(OBJ)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

vm.o: vm/vm.c vm/vm_utils.c
	$(CC) $(CFLAGS) -c vm/vm.c -o vm.o

asm.o: asm/asm.c
	$(CC) $(CFLAGS) -c asm/asm.c -o asm.o

helpers.o: include/helpers.c include/instructions.c
	$(CC) $(CFLAGS) -c include/helpers.c -o helpers.o

tests.o: tests/test_vm.c
	$(CC) $(CFLAGS) -c tests/test_vm.c -o tests.o

# rule for the test executable
tests: $(TEST_OBJ)
	$(CC) $(CFLAGS) -o tests $(TEST_OBJ)

clean:
	rm -f *.o corewar tests
