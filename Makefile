# Makefile

# Whenever you run "make" with no arguments, it runs the first definition, and
# thus that is the "default" one. Here we set main as the default.
.PHONY: default
default: main

# Binaries go in the bin(ary) folder.
main: main.c
	gcc -I. -o ./bin/$@ $^

# This definition depends on "main" and thus will run it (compiling ./bin/main)
# and only then run the commands below.
run: main
	./bin/main
