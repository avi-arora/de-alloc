PROGRAMS = membench-malloc membench-arena
INCLUDES = -I.

CFLAGS = -g -O0 -Wall $(INCLUDES) -lpthread

all: $(PROGRAMS)

%.o:%.c
	$(CC) $(CFLAGS) -c $<

membench-malloc: membench.o mb-malloc.o
	$(CC) $(CFLAGS) -o $@ membench.o mb-malloc.o

membench-arena: membench.o mb-arena.o
	$(CC) $(CFLAGS) -o $@ membench.o mb-arena.o

clean:
	rm -f $(PROGRAMS) *.o core a.out
