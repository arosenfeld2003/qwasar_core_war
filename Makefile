#
# Makefile for corewar
#

PROG = corewar
OPTS = -Wall -Wextra -g #-Werror 

corewar: corewar.o op.o
	cc $(OPTS) corewar.o op.o -o $(PROG)

corewar.o: corewar.c corewar.h
	cc $(OPTS) -c $(PROG).c

op.o: op.c op.h
	cc $(OPTS) -c op.c

clean:
	rm *.o

fclean: clean
	rm -f $(PROG) a.out
