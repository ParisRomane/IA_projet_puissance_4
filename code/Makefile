CC = g++
CFLAGS = -std=c++17 -O2

LFLAGS = structs.h State.h
SRCS = State.cpp main.cpp
OBJS = $(SRCS: .cpp=.o)

main: $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ $^

clean:
	rm -rf *.o *~ 
	rm main