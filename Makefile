prefix_modules=src/tests/modules/
prefix_strings=src/tests/strings/
prefix_errors=src/tests/errors/
prefix_process=src/tests/process/
bindir=bin/

all: run_mod

# Modules
run_mod: install
	@ ./$(bindir)run
install: clean_mod rev pal mod 
	@ clang mod.o pal.o rev.o -o run
	@ mv run $(bindir)/
mod: pal 
	@ echo "Start compile mod"
	@ clang -c $(prefix_modules)mod.c
	@ echo "Done compile mod"
pal: rev
	@ echo "Start compile pal"
	@ clang -c $(prefix_modules)pal.c
	@ echo "Done compile pal"
rev:
	@ echo "Start compile rev"
	@ clang -c $(prefix_modules)rev.c
	@ echo "Done compile rev"
clean_mod:
	@ echo "Cleaning the garbage"
	@ rm -f mod.o pal.o rev.o $(bindir)run

# Strings
run_str: compile_strings
	@ ./run
compile_strings: strings
	@ clang strings.o -o run
strings:
	@ clang -c $(prefix_strings)strings.c
clean_strings:
	@ rm strings.o run

errors:
	@ clang -c $(prefix_errors)error.c
	@ clang error.o -o run
	@ ./run

process:
	@ clang -c $(prefix_process)process.c
	@ clang process.o -o run
	@ ./run

summers:
	@ clang -c $(prefix_process)summers.c
	@ clang summers.o -o run
	@ ./run 

file_writer:
	@ clang -c $(prefix_process)file_writer.c
	@ clang file_writer.o -o run
	@ ./run ciao.txt
