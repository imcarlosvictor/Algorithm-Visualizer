# Compiler and flags
CXX      := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -ggdb -Iinclude

# Folders
BIN      := bin
SRC      := src
LIB      := lib

# Libraries to link
LDFLAGS  := -L$(LIB)
LIBS     := -ltgui -lsfml-graphics -lsfml-window -lsfml-system

# Output executable
EXEC     := algo_visualizer

# Find sources and generate object list
SRCS     := $(wildcard $(SRC)/*.cpp)
OBJS     := $(SRCS:$(SRC)/%.cpp=$(BIN)/%.o)

# Default rule
all: $(BIN)/$(EXEC)

# Link step
$(BIN)/$(EXEC): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) $(LIBS) -o $@

# Compile Step
$(BIN)/%.o: $(SRC)/%.cpp
	mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run
run: all
	clear
	./$(BIN)/$(EXEC)

# Clean
clean:
	rm -f $(BIN)/*.o $(BIN)/$(EXEC)
