CXX = g++
CFLAGS = -Wall -g
LD = ld

OBJECTS = binder_main.o
LIBS = rpc.a
LIB_INCLUDE = $(patsubst %.a,-l%,$(LIBS))

all: binder

%.o: %.c
		$(CXX) $(CFLAGS) -o $@ $<
		
all: $(LIBS) $(OBJECTS)
		$(CXX) $@ -L. $(LIBS_INCLUDE) -o all
		
clean:
		rm -rf *.o