CFLAGS = -std=c17 -D_XOPEN_SOURCE=700
CFLAGS += -Wall -Wextra -Werror -Wno-unused
CFLAGS += -MMD

progs = assembleur decoupage 
progs += test-table-des-symboles essai-prog

all: $(progs)

test-table-des-symboles:  test-table-des-symboles.o table-des-symboles.o

assembleur: assembleur.o table-des-symboles.o

clean:
	$(RM) *~ *.o *.d *.bak *.orig

mrproper: clean
	$(RM) $(progs)

-include $(wildcard *.d)
