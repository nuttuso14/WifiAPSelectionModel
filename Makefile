CC = g++
CFLAGS = -g -c
STANDARD = -std=c++11


all: bestWifiAP 

bestWifiAP: bestWifiAP.o
	$(CC) -o $@ $? 

bestWifiAP.o:	bestWifiAP.cpp
	$(CC) $(STANDARD) $(CFLAGS) -o $@ bestWifiAP.cpp 

clean:
	rm *.o *.txt bestWifiAP 

