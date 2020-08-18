
rm -r bin/
mkdir bin
clang -o bin/args src/tests/args/args.c
./bin/args $@

