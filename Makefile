ROOTCFLAGS    = $(shell root-config --cflags)
ROOTLIBS      = $(shell root-config --libs) -lMinuit
ROOTGLIBS     = $(shell root-config --glibs)

CC       := g++ # This is the main compiler
SRCDIR   := src
BUILDDIR := build
TARGET   := bin/main
OBJ		 := $(BUILDDIR)/main.o

SRCEXT   := cpp
SOURCES  := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS  := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS   := $(shell root-config --cflags) -g -O3 #-Wno-write-strings -D_FILE_OFFSET_BITS=64 -DDROP_CGAL #-Wall -Wextra
LIB      := $(shell root-config --libs) -lMinuit
INC      := -I interface


all: ${TARGET}

build/main.o: src/main.cpp
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

${TARGET}: $(OBJ)
	@echo "Linking..."
	@mkdir -p bin
	$(CC) -o $@ $^ $(CFLAGS) $(LIB)

.PHONY: clean

clean:
	@echo " Cleaning..."; 
	$(RM) -r $(BUILDDIR) $(TARGET)
