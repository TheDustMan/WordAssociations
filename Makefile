CXX=g++
CXXFLAGS=-std=c++17 -g -Wall

FILES = words.cpp WordNode.cpp
OBJECTS = words.o WordNode.o
EXE = words

all: compile-all link-all

link-all:
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJECTS)

compile-all:
	$(CXX) $(CXXFLAGS) -c $(FILES)

clean:
	rm -rf $(EXE) *.o *.obj *.pdb *.ilk *.exe*
