CC = g++
CFLAGS = -g -c


all: main 

main: main.o
	$(CC) -o $@ $? 

main.o:	main.cpp
	$(CC) $(CFLAGS) -o $@ main.cpp 

clean:
	rm *.o *.txt main 

