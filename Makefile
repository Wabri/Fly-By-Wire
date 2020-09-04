DEFAULT_COMPILER=clng
ALTERNATIVE_COMPILER=clang

PREFIX_PFC=src/pfc/
PREFIX_BIN=bin/

EVAL_COMPILER="head -1 .compiler"

all: clean check_compiler install

clean:
	@ if test -f .compiler ; \
	    then \
	    rm .compiler ; \
	    echo "Clean default compiler" ; \
	    fi
	@ rm -rf run $(PREFIX_BIN)
	@ mkdir $(PREFIX_BIN)

install: check_compiler pfc

check_compiler: SHELL:=/bin/bash
check_compiler: 
	@ rm -f .compiler;
	@ if test -f .compiler ; \
	    then echo "Compiler already set" ; \
	    else echo "Try with default compiler: "$(DEFAULT_COMPILER) ; \
	    touch .compiler ; echo $(DEFAULT_COMPILER) > .compiler ; \
	    fi
	@ if ! command -v $(DEFAULT_COMPILER) &> /dev/null ; \
	    then \
	    echo "The default compiler is not found." ; \
	    echo "Try with the alternative "$(ALTERNATIVE_COMPILER) ; \
	    echo $(ALTERNATIVE_COMPILER) > .compiler ; \
	    fi ; 

pfc: check_compiler
	@ $(eval $(head -1 .compiler)) -c $(PREFIX_PFC)pfc.c -o $(PREFIX_BIN)pfc.o
	@ $(eval $(head -1 .compiler)) -c $(PREFIX_PFC)structure.c -o $(PREFIX_BIN)structure.o
	@ clang $(PREFIX_BIN)*.o -o run
