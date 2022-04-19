ROOTLIBS = $(shell root-config --cflags --libs) -lMinuit -lMLP -lXMLIO -lTMVA -lGenVector


CC = g++
CFLAGS = -g -std=c++1y

TARGET = bin/examine

all: $(TARGET)

bin/examine: examine.cpp t.C t.h toolbox.h p.C p.h
	$(CC) $(CFLAGS) -I${ROOTSYS}/include -o bin/examine examine.cpp $(ROOTLIBS)
