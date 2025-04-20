# Compiler and Flags
CXX = g++
CXXFLAGS = -std=c++17
INCLUDE_PATH = -IC:/msys64/mingw64/include
LIBRARY_PATH = -LC:/msys64/mingw64/lib
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Object and Executable names
EXEC = space_object_test.exe
OBJECTS = space_object.o
SOURCE = space_object_test.cpp
SPACE_OBJECT_SRC = space_object.cpp
HEADER = space_object.h

# Build the executable
$(EXEC): $(SOURCE) $(OBJECTS) $(HEADER)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(SOURCE) $(OBJECTS) $(INCLUDE_PATH) $(LIBRARY_PATH) $(SFML_LIBS)

# Build object file
$(OBJECTS): $(SPACE_OBJECT_SRC) $(HEADER)
	$(CXX) -c $(CXXFLAGS) $(SPACE_OBJECT_SRC) $(INCLUDE_PATH)

# Clean up object files and executables
clean:
	del /Q *.o *.exe 2> nul || rm -f *.o *.exe
