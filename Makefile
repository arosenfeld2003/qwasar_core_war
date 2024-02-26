CC=gcc
CFLAGS=-Wall -Wextra -Werror -g

OBJ = main.o vm.o asm.o helpers.o

all: corewar

corewar: $(OBJ)
	$(CC) $(CFLAGS) -o corewar $(OBJ)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

vm.o: vm/vm.c vm/vm_utils.c
	$(CC) $(CFLAGS) -c vm/vm.c -o vm.o

asm.o: asm/asm.c
	$(CC) $(CFLAGS) -c asm/asm.c -o asm.o

helpers.o: include/helpers.c
	$(CC) $(CFLAGS) -c include/helpers.c -o helpers.o

tests.o: tests/test_vm.c
	$(CC) $(CFLAGS) -c tests/test_vm.c -o tests.o

clean:
	rm -f *.o corewar
