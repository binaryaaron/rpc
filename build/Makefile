all: client server

client:
	gcc -g -Wall -std=gnu99 -I../src -L. -lsrpc -o client test_client.c

server:
	gcc -g -Wall -std=gnu99 -I../src -L. -lsrpc -o server test_server.c

clean:
	rm test
	rm server
	rm client

tests:
	gcc -g -Wall -std=gnu99 -I../src -L. -lsrpc -Wextra -DEBUG marshalling_test.c -o test
	gcc -g -Wall -std=gnu99 -I../src -L. -lsrpc -Wextra -DEBUG exampleServer.c -o server
	gcc -g -Wall -std=gnu99 -I../src -L. -lsrpc -Wextra -DEBUG exampleClient.c -o client


