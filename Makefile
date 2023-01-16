TARGET = as16
DEPS	= as.y
OBJS	= as.o
CFLAGS	= -I. -g
LIBS	= -lm

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

y.tab.c: as.y
	yacc -v -d as.y

as.o:	y.tab.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm $(TARGET) a.out *.o y.tab.c y.tab.h y.output
