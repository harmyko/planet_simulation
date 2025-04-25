# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17

# SFML include and lib paths
INCLUDE_PATH = -IC:/msys64/mingw64/include -Iinclude -Iinclude/space_sim
LIBRARY_PATH = -LC:/msys64/mingw64/lib
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Directories
SRC_DIR = src
CORE_DIR = $(SRC_DIR)/core
MAIN_DIR = $(SRC_DIR)/main
BUILD_DIR = build
BIN_DIR = bin
INCLUDE_DIR = include/space_sim

# Object files
OBJS = \
	$(BUILD_DIR)/space_object.o \
	$(BUILD_DIR)/movement_dynamic.o \
	$(BUILD_DIR)/movement_static.o

# Executable targets
TARGETS = \
	$(BIN_DIR)/random_objects.exe \
	$(BIN_DIR)/solar_system.exe \
	$(BIN_DIR)/test.exe

# Default target
all: $(TARGETS)

# Individual executable builds
$(BIN_DIR)/random_objects.exe: $(MAIN_DIR)/random_objects.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(INCLUDE_PATH) $(LIBRARY_PATH) $(SFML_LIBS)

$(BIN_DIR)/solar_system.exe: $(MAIN_DIR)/solar_system.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(INCLUDE_PATH) $(LIBRARY_PATH) $(SFML_LIBS)

$(BIN_DIR)/test.exe: $(MAIN_DIR)/test.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(INCLUDE_PATH) $(LIBRARY_PATH) $(SFML_LIBS)

# Core object file builds
$(BUILD_DIR)/space_object.o: $(CORE_DIR)/space_object.cpp $(INCLUDE_DIR)/space_object.hpp
	$(CXX) -c $(CXXFLAGS) $< -o $@ $(INCLUDE_PATH)

$(BUILD_DIR)/movement_dynamic.o: $(CORE_DIR)/movement_dynamic.cpp $(INCLUDE_DIR)/movement/dynamic.hpp
	$(CXX) -c $(CXXFLAGS) $< -o $@ $(INCLUDE_PATH)

$(BUILD_DIR)/movement_static.o: $(CORE_DIR)/movement_static.cpp $(INCLUDE_DIR)/movement/static.hpp
	$(CXX) -c $(CXXFLAGS) $< -o $@ $(INCLUDE_PATH)

# Clean build files
clean:
	del /Q $(BUILD_DIR)\*.o $(BIN_DIR)\*.exe 2> nul || true
