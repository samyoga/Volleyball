CFLAGS = -lgraph -lm
default: build
build: main
run: main.o
	gcc main.c -lgraph -lm -o main
	./main
ball: ball.o
	gcc ball.c -lgraph -lm -o ball
	./ball