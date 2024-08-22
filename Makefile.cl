CXX=cl
CXXFLAGS=-Zi /EHsc

FILES = words.cpp WordNode.cpp
OBJECTS = words.obj WordNode.obj
EXE = words.exe

all: compile-all link-all

link-all:
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJECTS)

compile-all:
	$(CXX) $(CXXFLAGS) -c $(FILES)

clean:
	rm -rf $(EXE) *.obj
