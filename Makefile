CXX = g++
CFLAGS = -Wall -g
LD = ld

OBJECTS = binder_main.o test_client.o test_server.o test_client2.o


%.o: %.c
		$(CXX) $(CFLAGS) -o $@ $<
		
binder: binder_main.o
		$(CXX) binder_main.o -L. -lrpc -o binder
		
client: test_client.o
		$(CXX) test_client.o -L. -lrpc -o client

client2: test_client2.o
		$(CXX) test_client2.o -L. -lrpc -o client2
		
server: test_server.o
		$(CXX) test_server.o -L. -lrpc -o server
		
clean:
		rm -rf *.o binder client server client2