CC=gcc

PREFIX_GLOBAL=src/
PREFIX_PFC=$(PREFIX_GLOBAL)/pfc/
PREFIX_UTIL=$(PREFIX_GLOBAL)/utility/
BINDIR=bin/
LOGDIR=logs/

all: clean install 

clean:
	@ rm -rf $(BINDIR) $(LOGDIR)
	@ mkdir $(BINDIR)
	@ mkdir $(LOGDIR)

install: main
	@ $(CC) $(BINDIR)*.o -o run -lm

main: pfc constants
	@ $(CC) -c $(PREFIX_GLOBAL)main.c -o $(BINDIR)main.o

pfc: utility constants
	@ $(CC) -c $(PREFIX_PFC)pfc.c -o $(BINDIR)pfc.o
	@ $(CC) -c $(PREFIX_PFC)structure.c -o $(BINDIR)structure.o

utility:
	@ $(CC) -c $(PREFIX_UTIL)string.c -o $(BINDIR)string.o
	@ $(CC) -c $(PREFIX_UTIL)angles.c -o $(BINDIR)angles.o

constants:
	@ $(CC) -c $(PREFIX_GLOBAL)constants.c -o $(BINDIR)constants.o

