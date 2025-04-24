CXX = g++
CXXFLAGS = -std=c++17
INCLUDE_PATH = -IC:/msys64/mingw64/include -I. -Imovement
LIBRARY_PATH = -LC:/msys64/mingw64/lib
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

OBJECTS = space_object.o movement_strategy/dynamic_movement_strategy.o movement_strategy/static_movement_strategy.o
SOURCE_SOLAR_SYSTEM = solar_system.cpp
SOURCE_RANDOM_OBJECTS = random_objects.cpp
SOURCE_TEST = test.cpp
SPACE_OBJECT_SRC = space_object.cpp
DYNAMIC_STRATEGY_SRC = movement_strategy/dynamic_movement_strategy.cpp
STATIC_STRATEGY_SRC = movement_strategy/static_movement_strategy.cpp
HEADERS = space_object.h movement_strategy/dynamic_movement_strategy.h movement_strategy/static_movement_strategy.h

# Build the random_objects executable
random_objects.exe: $(SOURCE_RANDOM_OBJECTS) $(OBJECTS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o random_objects.exe $(SOURCE_RANDOM_OBJECTS) $(OBJECTS) $(INCLUDE_PATH) $(LIBRARY_PATH) $(SFML_LIBS)

# Build the solar_system executable
solar_system.exe: $(SOURCE_SOLAR_SYSTEM) $(OBJECTS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o solar_system.exe $(SOURCE_SOLAR_SYSTEM) $(OBJECTS) $(INCLUDE_PATH) $(LIBRARY_PATH) $(SFML_LIBS)

# Build the test executable
test.exe: $(SOURCE_TEST) $(OBJECTS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o test.exe $(SOURCE_TEST) $(OBJECTS) $(INCLUDE_PATH) $(LIBRARY_PATH) $(SFML_LIBS)

# Build space_object.o
space_object.o: $(SPACE_OBJECT_SRC) space_object.h
	$(CXX) -c $(CXXFLAGS) $(SPACE_OBJECT_SRC) -o space_object.o $(INCLUDE_PATH)

# Build dynamic_movement_strategy.o
movement_strategy/dynamic_movement_strategy.o: $(DYNAMIC_STRATEGY_SRC) movement_strategy/dynamic_movement_strategy.h
	$(CXX) -c $(CXXFLAGS) $(DYNAMIC_STRATEGY_SRC) -o movement_strategy/dynamic_movement_strategy.o $(INCLUDE_PATH)

# Build static_movement_strategy.o
movement_strategy/static_movement_strategy.o: $(STATIC_STRATEGY_SRC) movement_strategy/static_movement_strategy.h
	$(CXX) -c $(CXXFLAGS) $(STATIC_STRATEGY_SRC) -o movement_strategy/static_movement_strategy.o $(INCLUDE_PATH)

# Clean up object files and executables
clean:
	del /Q *.o *.exe movement_strategy\*.o 2> nul || rm -f *.o *.exe movement_strategy/*.o
