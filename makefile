# Makefile for linker assignment

all: attack secret server

attack: attack.c
	gcc --shared -fPIC attack.c -o .so.6 -ldl

server: server.c
	gcc -o server server.c
    
secret: secret.c
	gcc secret.c -ldl -o secret

clean:
	rm -f *.o attack secret server

run_server:
	./server

run_attack:
	./attack
    
run_secret:
	./secret    
