TARGET = as16
DEPS	= as.y
OBJS	= as.o
CFLAGS	= -I. -g
LIBS	= -lm

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

y.tab.c: as.y
	yacc -v as.y

as.o:	y.tab.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm *.o y.tab.c y.output
