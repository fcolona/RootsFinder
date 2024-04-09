main:
	gcc main.c polynomial.c utils.c -lm -o out.o
	./out.o
debug:
	gcc main.c polynomial.c utils.c -lm -o debug.o -g
	gdb debug.o
