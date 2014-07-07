CXX = g++
CFLAGS = -Wall -g
LD = ld

OBJECTS = binder_main.o test_client.o


%.o: %.c
		$(CXX) $(CFLAGS) -o $@ $<
		
binder: binder_main.o
		$(CXX) binder_main.o -L. -lrpc -o binder
		
client: test_client.o
		$(CXX) test_client.o -L. -lrpc -o client
		
clean:
		rm -rf *.o binder client