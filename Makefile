all: make_main open clean
make_main:	
	gcc -Wall -o main main.c -lm
open:
	./main
clean:
	rm -rf *-o main
