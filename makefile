CC = gcc

all: myshell execx writef 

myshell: myshell.c
	$(CC) myshell.c -o myshell

execx: execx.c
	$(CC) execx.c -o execx

writef: writef.c
	$(CC) writef.c -o writef

clean:
	rm -rf *o all
