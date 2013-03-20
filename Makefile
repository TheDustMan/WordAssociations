CXX=g++
CXXFLAGS=-g

FILES = words.cpp WordNode.cpp
OBJECTS = words.o WordNode.o
EXE = words.exe

all: compile-all link-all

link-all:
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJECTS)

compile-all:
	$(CXX) $(CXXFLAGS) -c $(FILES)

clean:
	rm -rf $(EXE) *.o
