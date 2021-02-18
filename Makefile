all: build
build: epm.c
	gcc -g -o epm epm.c
clean:
	rm -fr epm2 epm.o *~
