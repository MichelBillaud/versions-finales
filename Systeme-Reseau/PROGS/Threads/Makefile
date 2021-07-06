execs = leger_mutex leger leger_sem

CFLAGS = -std=c18 -Wall -Wextra -pedantic
CFLAGS += -D_XOPEN_SOURCE=700
CFLAGS += -pthread
CFLAGS += -MMD

all: $(execs)

pretty:
	astyle -A3  *.c *.h

clean:
	$(RM) *~ *.orig *.bak *.o *.d

mrproper: clean
	$(RM) $(execs)

-include *.d
