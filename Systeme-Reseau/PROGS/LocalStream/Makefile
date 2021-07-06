execs = client-stream  serveur-stream  serveur-stream-monotache

CFLAGS = -std=c18 -Wall -Wextra -pedantic
CFLAGS += -D_XOPEN_SOURCE=700

all: $(execs)



pretty:
	astyle -A3   *.c 

clean:
	$(RM) *~ *.orig *.bak *.o *.d

mrproper: clean
	$(RM) $(execs)

-include $(wikdcard *.d)
