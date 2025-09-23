# Executable
TARGET = main

# Source directories
SRC_DIR = .
COMPONENTS = include
APP_DIR = src
BUILD_DIR = build

# Compilers
CC = gcc
CXX = g++
CFLAGS = -g -O0 -Wall -Wextra
CXXFLAGS = -g -O0 -Wall -Wextra -std=c++17
CPPFLAGS = $(foreach comp,$(COMPONENTS),-I$(SRC_DIR)/$(comp)) -I$(SRC_DIR)/$(APP_DIR)

# Source files
COMPONENT_SRC = $(foreach comp,$(COMPONENTS),$(wildcard $(SRC_DIR)/$(comp)/*.cpp) $(wildcard $(SRC_DIR)/$(comp)/*.c))
APP_SRC = $(wildcard $(SRC_DIR)/$(APP_DIR)/*.cpp) $(wildcard $(SRC_DIR)/$(APP_DIR)/*.c)
SRC_FILES = $(COMPONENT_SRC) $(APP_SRC)

# Object & dep files
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES)))
DEP_FILES = $(OBJ_FILES:.o=.d)

# Default
.PHONY: all
all: $(BUILD_DIR)/$(TARGET)

# Link
$(BUILD_DIR)/$(TARGET): $(OBJ_FILES)
	$(CXX) $^ -o $@

# Build rule for .cpp
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Build rule for .c
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

# Include deps
-include $(DEP_FILES)

# Clean
.PHONY: clean
clean:
	$(RM) -r $(BUILD_DIR)

# Run
.PHONY: run
run: all
	./$(BUILD_DIR)/$(TARGET)
