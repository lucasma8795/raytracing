.PHONY: help build clean

# display help message
help:
	@echo "To compile raytracing, type "
	@echo "    make [target]"
	@echo ""
	@echo "Supported targets:"
	@echo "    help  - display this command"
	@echo "    build - compile the engine"
	@echo "    clean - clean up object files and executables"

# compiler to use
CXX = /opt/homebrew/bin/g++-12

# name of output executable
EXEC_FILE = raytrace

# list of cpp files
CPPFILES = $(shell find ./src -name "*.cpp") # $(wildcard src/*.cpp)

# list of object files
OBJECTS = $(CPPFILES:.cpp=.o)

# list of dependencies
DEPENDS = $(CPPFILES:.cpp=.d)

# include path
INCLUDE = -isystem /opt/homebrew/include/

# libraries
LIBS = -L/opt/homebrew/lib/ -lSDL2 -lSDL2_image

# linker flags
LDFLAGS = -flto=auto -pthread

# pull in dependency info for existing .o files
-include $(OBJECTS:.o=.d)

# compiler flags
CXXFLAGS  = -Ofast -Wall -Wextra -Wpedantic -Werror
CXXFLAGS += -std=c++23 -march=native
CXXFLAGS += -flto=auto -fopenmp # -pthread
CXXFLAGS += -fno-exceptions -DNDEBUG
# CXXFLAGS += -Wno-unused-variable -Wno-unused-parameter

# build rules
build: $(EXEC_FILE)

# compile .cpp
%.o: %.cpp Makefile
	$(CXX) $(CXXFLAGS) $(INCLUDE) -MMD -MP -c $< -o $@

# make final executable
$(EXEC_FILE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LIBS) $(LDFLAGS) $^ -o $@

# clean up object files & executables
clean:
	rm -rf src/*.o src/*.d
	rm -rf src/materials/*.o src/materials/*.d
	rm -rf src/objects/*.o src/objects/*.d
	rm -rf src/scenes/*.o src/scenes/*.d
	rm -rf src/textures/*.o src/textures/*.d
	rm -f $(EXEC_FILE)