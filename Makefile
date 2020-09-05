CC=clang

PREFIX_PFC=src/pfc/
BINDIR=bin/

all: clean install 

clean:
	@ rm -rf $(BINDIR)
	@ mkdir $(BINDIR)

install: pfc
	@ $(CC) $(BINDIR)*.o -o run

pfc: 
	@ $(CC) -c $(PREFIX_PFC)pfc.c -o $(BINDIR)pfc.o
	@ $(CC) -c $(PREFIX_PFC)structure.c -o $(BINDIR)structure.o

