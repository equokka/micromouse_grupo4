# Makefile

# Whenever you run "make" with no arguments, it runs the first definition, and
# thus that is the "default" one. Here we set main as the default.
.PHONY: default
default: server client

# Binaries go in the bin(ary) folder.
client: client.c
	gcc -I. -o ./bin/$@ $^
server: server.c
	gcc -I. -o ./bin/$@ $^
