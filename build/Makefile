all: client server

client:
	gcc -Wall -std=gnu99 -I../src -L. -lsrpc -o client test_client.c

server:
	gcc -Wall -std=gnu99 -I../src -L. -lsrpc -o server test_server.c

clean:
	rm test
	rm server
	rm client

tests:
	gcc -Wall -std=gnu99 -I../src -L. -lsrpc marshalling_test.c -o test


