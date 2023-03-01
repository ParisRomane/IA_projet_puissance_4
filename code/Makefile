CC = g++
CFLAGS = -std=c++17 -O3 -g -Wall

LFLAGS = structs.h checks.h State.h Node.h
SRCS = State.cpp Node.cpp main.cpp
OBJS = $(SRCS: .cpp=.o)

main: $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ $^

clean:
	rm -rf *.o *~ 
	rm main