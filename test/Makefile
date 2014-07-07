#Makefile

CC = g++
CFLAGS = -Wall -g

all: test_client test_server test_procedure

test_client: client/client.h
		$(CC) $(CFLAGS) -c client/client1.c
		$(CC) $(CFLAGS) -c client/client2.c
		$(CC) $(CFLAGS) -c client/client3.c
		$(CC) $(CFLAGS) -c client/client4.c

test_server:
		$(CC) $(CFLAGS) -c server/server.c

test_procedure:
		$(CC) $(CFLAGS) -c procedure/server_functions.c

clean:
		rm -f *.o