CFLAGS = -lgraph
default: build
build: main
run: main.o
	gcc main.c -lgraph -o main
	./main