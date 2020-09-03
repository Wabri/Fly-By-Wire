DEFAULT_COMPILER=clang
ALTERNATIVE_COMPILER=gcc

COMPILER="head -1 .compiler"

all: set_compiler check_compiler
	@ eval $(COMPILER) 

clean:
	@ if test -f .compiler ; \
	    then \
	    rm .compiler ; \
	    echo "Clean default compiler" ; \
	    fi

install:

set_compiler:
	@ if test -f .compiler ; \
	    then echo "Compiler already set" ; \
	    else echo "Compiler set on default "$(DEFAULT_COMPILER) ; \
	    touch .compiler ; echo $(DEFAULT_COMPILER) > .compiler ; \
	    fi

check_compiler: SHELL:=/bin/bash
check_compiler: 
	@ if ! command -v $(DEFAULT_COMPILER) &> /dev/null ; \
	    then \
	    echo "No default compiler found, try with gcc" ; \
	    echo $(ALTERNATIVE_COMPILER) > .compiler ; \
	    fi ; 

