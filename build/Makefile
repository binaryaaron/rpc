all: client server

client:
	gcc -Wall -ansi -L. -lsrpc -o client test_client.c

server:
	gcc -Wall -ansi -L. -lsrpc -o server test_server.c

clean:
	rm server
	rm client

tests:
	gcc -Wall -ansi -L. -I../src -lsrpc -o test marshalling_test.c


