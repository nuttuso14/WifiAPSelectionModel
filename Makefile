CC = g++
CFLAGS = -g -c
STANDARD = -std=c++11


all: bestWifiAP 

bestWifiAP: bestWifiAP.o
	$(CC) -o $@ $? 
	$(CC) -o drawFigure drawFigure.o 

bestWifiAP.o:	bestWifiAP.cpp
	$(CC) $(STANDARD) $(CFLAGS) -o $@ bestWifiAP.cpp 
	$(CC) $(STANDARD) $(CFLAGS) -o drawFigure.o drawFigure.cpp 

clean:
	rm *.o *.txt bestWifiAP drawFigure 

