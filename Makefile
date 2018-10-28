CC = g++
CFLAGS = -g -c
STANDARD = -std=c++11


all: wifiselect 

wifiselect: wifiselect.o
	$(CC) -o $@ $? 

wifiselect.o:	wifiselect.cpp
	$(CC) $(STANDARD) $(CFLAGS) -o $@ wifiselect.cpp 

clean:
	rm *.o *.txt wifiselect 

