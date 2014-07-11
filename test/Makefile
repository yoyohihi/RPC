#Makefile

CC = g++
CFLAGS = -Wall -g

all: test_client test_server test_procedure

test_client: client.h
		$(CC) $(CFLAGS) -c client/client1.c
		$(CC) $(CFLAGS) -c client/client2.c
		$(CC) $(CFLAGS) -c client/client3.c
		$(CC) $(CFLAGS) -c client/client4.c
		$(CC) $(CFLAGS) -c client/client5.c
		$(CC) $(CFLAGS) -c client/client6.c

test_server:
		$(CC) $(CFLAGS) -c server/server1.c
		$(CC) $(CFLAGS) -c server/server2.c

test_procedure:
		$(CC) $(CFLAGS) -c procedure/server1_functions.c

clean:
		rm -f *.o