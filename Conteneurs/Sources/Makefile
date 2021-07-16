CFLAGS = --std=c18
CFLAGS = -Wall -Wextra -pedantic -Werror -Wno-unused
CFLAGS += -MD


%.run: %
	./$< > $@

progs = tailles-types adresses-variables adresses-tableaux
runs = tailles-types.run adresses-variables.run adresses-tableaux.run


progs += utilisation-tableau-extensible
runs += utilisation-tableau-extensible.run

progs += utilisation-ensemble-chaines
runs += utilisation-ensemble-chaines.run

all: $(progs) $(runs)


utilisation-tableau-extensible: utilisation-tableau-extensible.o tab_int.o

utilisation-ensemble-chaines: utilisation-ensemble-chaines.o ens_chaines.o

include $(wildcard *.d)

clean:
	$(RM) *~ *.o *.d

mrproper: clean
	$(RM) $(progs) $(runs)
