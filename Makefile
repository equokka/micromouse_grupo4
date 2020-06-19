# Documentation:
#
# .PHONY: <targets> : phony targets are not built into files
# https://www.gnu.org/software/make/manual/html_node/Phony-Targets.html
#
#  -I<dir>          : gcc will include the given directory's header files
# https://www.rapidtables.com/code/linux/gcc/gcc-i.html
#
#  -o <file>        : gcc will output to this file
# https://www.rapidtables.com/code/linux/gcc/gcc-o.html
#
#  $@               : make replaces this with the target, ie. "server"
#  $^               : make replaces this with the prerequisites, ie. "server.c"
# https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html


# Whenever you run "make" with no arguments, it runs the first definition, and
# thus that is the "default" one. So here we make a phony definition that
# depends on server and client, thus building both of them by default.
.PHONY: default
default: server client

# Binaries go in the bin(ary) folder.
client: client.c
	gcc -I. -o ./bin/$@ $^
server: server.c
	gcc -pthread -I. -o ./bin/$@ $^
