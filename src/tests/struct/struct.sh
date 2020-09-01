
rm -r bin/
mkdir bin
clang -o bin/struct src/tests/struct/struct.c
./bin/struct $@

