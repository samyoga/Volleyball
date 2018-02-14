CFLAGS = -lgraph -lm
default: build
build: main
run: main.o
	gcc main.c -lgraph -lm -o main
	./main

