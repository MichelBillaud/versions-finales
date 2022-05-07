CFLAGS  =-std=c17 -D_XOPEN_SOURCE=700
CFLAGS +=-Wall -Wextra -pedantic -g

LDFLAGS = -g

STYLE=-A4 -s2  # stroustrup, indentation = 2

sources = test1.c test2.c sim16t.c asm16.c sim16.c
execs   = test1 test2 asm16 sim16
deps   := $(sources:.c=.d)

all: $(deps) $(execs)

test1: test1.o sim16t.o
test2: test2.o sim16t.o
asm16: asm16.o

%.d: %.c
	$(CC) -MM $(CFLAGS) $< -o $@

pretty:
	astyle ${STYLE} *.c *.h	touch *.c *.h

clean:
	$(RM) *.o *~ *.orig *.bak $(deps)

mrproper: clean
	$(RM) $(execs)

include $(wildcard *.d)

