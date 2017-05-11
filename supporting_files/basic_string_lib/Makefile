PROGRAMS = string_test
INCLUDES = -I.

CFLAGS = -g -O0 -Wall $(INCLUDES)

all: $(PROGRAMS)

%.o:%.c
	$(CC) $(CFLAGS) -c $<

string_test: string_test.o stringlib.o
	$(CC) $(CFLAGS) -o $@ string_test.o stringlib.o

clean:
	rm -f $(PROGRAMS) *.o core a.out
