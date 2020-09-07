CC=clang

PREFIX_GLOBAL=src/
PREFIX_PFC=$(PREFIX_GLOBAL)/pfc/
PREFIX_UTIL=$(PREFIX_GLOBAL)/utility/
BINDIR=bin/

all: clean install 

clean:
	@ rm -rf $(BINDIR)
	@ mkdir $(BINDIR)

install: pfc
	@ $(CC) $(BINDIR)*.o -o run

pfc: utility constants
	@ $(CC) -c $(PREFIX_PFC)pfc.c -o $(BINDIR)pfc.o
	@ $(CC) -c $(PREFIX_PFC)structure.c -o $(BINDIR)structure.o

utility:
	@ $(CC) -c $(PREFIX_UTIL)string.c -o $(BINDIR)string.o

constants:
	@ $(CC) -c $(PREFIX_GLOBAL)constants.c -o $(BINDIR)constants.o
