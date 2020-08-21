
rm -r bin/
mkdir bin
clang -o bin/files src/tests/files/files.c
./bin/files $@

