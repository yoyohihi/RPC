CXX = g++
AR = ar
ARFLAGS = rcs
CFLAGS = -Wall -g

OBJECTS = binder.o ClientSocket.o rpc_api.o rpc_argType.o ServerSocket.o Socket.o SocketManager.o Security.o Util.o

all:librpc.a


%.o: %.c
		$(CXX) $(CFLAGS) -o $@ $<

librpc.a: $(OBJECTS)
		$(AR) $(ARFLAGS) $@ $(OBJECTS)
		cp *.a ../

clean:
		rm -rf $(OBJECTS) *.a *.o
		rm -rf ../*.a

