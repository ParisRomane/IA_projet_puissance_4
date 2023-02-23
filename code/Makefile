CC = g++
CFLAGS = -std=c++17 -O2

LFLAGS = structs.h checks.h State.h MCT.h
SRCS = State.cpp MCT.cpp main.cpp
OBJS = $(SRCS: .cpp=.o)

main: $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ $^

clean:
	rm -rf *.o *~ 
	rm main