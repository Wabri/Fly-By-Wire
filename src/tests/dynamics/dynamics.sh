
rm -r bin/
mkdir bin
clang -o bin/dynamics src/tests/dynamics/dynamics.c
./bin/dynamics $@

