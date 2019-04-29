CC = g++
CFLAGS = -g -c
STANDARD = -std=c++11


all: K1K2RRT 

K1K2RRT: K1K2RRT.o
	$(CC) -o $@ $? 


K1K2RRT.o:	K1K2RRT.cpp
	$(CC) $(STANDARD) $(CFLAGS) -o $@ K1K2RRT.cpp 


clean:
	rm *.o *.txt K1K2RRT 

