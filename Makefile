CC=gcc
CFLAGS=-Wall -Wextra -Werror -g

OBJ = main.o vm.o vm_utils.o asm.o helpers.o instructions.o
TEST_OBJ = tests.o vm.o vm_utils.o helpers.o  instructions.o # tests use vm and helpers


all: corewar

corewar: $(OBJ)
	$(CC) $(CFLAGS) -o corewar $(OBJ)

# rule for the test executable
test: $(TEST_OBJ)
	$(CC) $(CFLAGS) -o test $(TEST_OBJ)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

vm.o: vm/vm.c vm/vm_utils.c
	$(CC) $(CFLAGS) -c vm/vm.c -o vm.o

vm_utils.o: vm/vm_utils.c
	$(CC) $(CFLAGS) -c vm/vm_utils.c -o vm_utils.o

asm.o: asm/asm.c
	$(CC) $(CFLAGS) -c asm/asm.c -o asm.o

helpers.o: include/helpers.c include/instructions.c
	$(CC) $(CFLAGS) -c include/helpers.c -o helpers.o

instructions.o: include/instructions.c
	$(CC) $(CFLAGS) -c include/instructions.c -o instructions.o

tests.o: tests/test_vm.c
	$(CC) $(CFLAGS) -c tests/test_vm.c -o tests.o

clean:
	rm -f *.o corewar test
