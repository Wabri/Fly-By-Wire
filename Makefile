CC=clang

PREFIX_PFC=src/pfc/
PREFIX_UTIL=src/utility/
BINDIR=bin/

all: clean install 

clean:
	@ rm -rf $(BINDIR)
	@ mkdir $(BINDIR)

install: pfc
	@ $(CC) $(BINDIR)*.o -o run

pfc: utility
	@ $(CC) -c $(PREFIX_PFC)pfc.c -o $(BINDIR)pfc.o
	@ $(CC) -c $(PREFIX_PFC)structure.c -o $(BINDIR)structure.o

utility:
	@ $(CC) -c $(PREFIX_UTIL)string.c -o $(BINDIR)string.o
