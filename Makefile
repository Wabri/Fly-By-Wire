run: all
	@ echo "Run"
	@ ./run

all: clean install 

clean:
	@ echo "Clean temporary files and directories"
	@ rm -rf bin/ log/ tmp/

install: precompile main
	@ echo "Package binaries on run"
	@ clang bin/*.o -o run -lm

main: pfc transducer fman wes pfcds config
	@ echo "Compile main"
	@ clang -c src/main.c -o bin/main.o

pfc: utility config 
	@ echo "Compile pfc"
	@ clang -c src/pfc.c -o bin/pfc.o
	@ clang -c src/structure.c -o bin/structure.o

transducer: utility config
	@ echo "Compile transducer"
	@ clang -c src/transducer.c -o bin/transducer.o

fman: config
	@ echo "Compile failure manager"
	@ clang -c src/fman.c -o bin/fman.o

wes: config
	@ echo "Compile wes"
	@ clang -c src/wes.c -o bin/wes.o

pfcds: precompile
	@ echo "Compile pfc disconnect switch"
	@ clang -c src/pfcds.c -o bin/pfcds.o

utility: precompile
	@ echo "Compile utilities"
	@ clang -c src/string.c -o bin/string.o
	@ clang -c src/angles.c -o bin/angles.o
	@ clang -c src/connection.c -o bin/connection.o

config: precompile
	@ echo "Compile constants"
	@ clang -c src/config.c -o bin/config.o

precompile:
	@ echo "Create binaries and logs directory"
	@ mkdir bin/
	@ mkdir log/
	@ mkdir tmp/
