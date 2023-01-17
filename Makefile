TARGET = as16
DEPS	= as.y
OBJS	= as.o
CFLAGS	= -I. -g -Wall
LIBS	= -lm
YACC	= yacc
YFLAGS	= -d

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

y.tab.c: as.y
	$(YACC) $(YFLAGS) as.y

as.o:	y.tab.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm $(TARGET) $(OBJS) a.out y.tab.* y.output
