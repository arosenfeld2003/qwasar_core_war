#
# Makefile for corewar
#

PROG = corewar
OPTS = -Wall -Wextra -g #-Werror 

corewar: corewar.o
	cc $(OPTS) corewar.o -o $(PROG)

corewar.o: corewar.c op.h
	cc $(OPTS) -c $(PROG).c

clean:
	rm *.o

fclean: clean
	rm -f $(PROG) a.out
