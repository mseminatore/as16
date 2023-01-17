TARGET = as16
DEPS	= as.y
OBJS	= as.o
CFLAGS	= -I. -g -Wall
LIBS	= -lm
YACC	= yacc
YFLAGS	= -d

all: $(TARGET) disasm

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

y.tab.c: as.y
	$(YACC) $(YFLAGS) as.y

as.o:	y.tab.c
	$(CC) $(CFLAGS) -c -o $@ $<

disasm:	disasm.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm $(TARGET) $(OBJS) disasm disasm.o a.out y.tab.* y.output
