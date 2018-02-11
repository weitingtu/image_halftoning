CC = gcc
CFLAGS = -O2
ifeq ($(MODE),rd)
    CFLAGS :=$(filter-out -O2,$(CFLAGS))
    CFLAGS += -g3 -gdwarf-4 -ggdb3 
endif
LDFLAGS = -lstdc++ -lm

all: demo bmp.o dither.o inverse.o

bmp.o : bmp.cpp bmp.h
	$(CC) -o $@ -c $< $(CFLAGS) -Wno-multichar

demo.o : demo.cpp utils.h
	$(CC) -o $@ -c $< $(CFLAGS)

dither.o : dither.cpp utils.h
	$(CC) -o $@ -c $< $(CFLAGS)

inverse.o : inverse.cpp utils.h
	$(CC) -o $@ -c $< $(CFLAGS)

demo: bmp.o demo.o dither.o inverse.o
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -f demo demo.o bmp.o dither.o inverse.o
