ROOTLIBS = $(shell root-config --libs) -lMinuit -lMLP -lXMLIO -lTMVA -lGenVector

CC = g++
CFLAGS = -g -std=c++1y

TARGET = examine

all: $(TARGET)

examine: examine.cpp t.C t.h
	$(CC) $(CFLAGS) -I${ROOTSYS}/include -o examine examine.cpp $(ROOTLIBS)
