CC=gcc

PREFIX_GLOBAL=src/
PREFIX_PFC=$(PREFIX_GLOBAL)/pfc/
PREFIX_TRANS=$(PREFIX_GLOBAL)/transducer/
PREFIX_FMAN=$(PREFIX_GLOBAL)/fman/
PREFIX_UTIL=$(PREFIX_GLOBAL)/utility/
BINDIR=bin/
LOGDIR=log/
TMPDIR=tmp/

run: all
	@ echo "Run"
	@ ./run

all: clean install 

clean:
	@ echo "Clean temporary files and directories"
	@ rm -rf $(BINDIR) $(LOGDIR) $(TMPDIR)

install: precompile main
	@ echo "Package binaries on run"
	@ $(CC) $(BINDIR)*.o -o run -lm

main: precompile pfc transducer fman constants
	@ echo "Compile main"
	@ $(CC) -c $(PREFIX_GLOBAL)main.c -o $(BINDIR)main.o

pfc: precompile utility constants 
	@ echo "Compile pfc"
	@ $(CC) -c $(PREFIX_PFC)pfc.c -o $(BINDIR)pfc.o
	@ $(CC) -c $(PREFIX_PFC)structure.c -o $(BINDIR)structure.o

transducer: precompile utility constants
	@ echo "Compile transducer"
	@ $(CC) -c $(PREFIX_TRANS)transducer.c -o $(BINDIR)transducer.o

fman: precompile
	@ echo "Compile failure manager"
	@ $(CC) -c $(PREFIX_FMAN)fman.c -o $(BINDIR)fman.o

utility: precompile
	@ echo "Compile utilities"
	@ $(CC) -c $(PREFIX_UTIL)string.c -o $(BINDIR)string.o
	@ $(CC) -c $(PREFIX_UTIL)angles.c -o $(BINDIR)angles.o
	@ $(CC) -c $(PREFIX_UTIL)connection.c -o $(BINDIR)connection.o

constants: precompile
	@ echo "Compile constants"
	@ $(CC) -c $(PREFIX_GLOBAL)constants.c -o $(BINDIR)constants.o

precompile:
	@ echo "Create binaries and logs directory"
	@ mkdir $(BINDIR)
	@ mkdir $(LOGDIR)
	@ mkdir $(TMPDIR)
