#
#  Makefile - Use this to compile your CompilerKit-based project
#  CompilerKit
#
#  Created by Amy Parent on 25/01/2022.
#

TARGET ?= block1
SRC_DIR := ./src
LIB_DIR := $(SRC_DIR)/CompilerKit
TMP_DIR := build

CPPFLAGS := -g3 -ggdb -O0 -std=c++14 -Wall -Werror
LDFLAGS := -g3 -ggdb -O0 -std=c++14

LIB_SRC := $(wildcard $(LIB_DIR)/*.cpp)
LIB_HDR := $(wildcard $(LIB_DIR)/*.hpp)

APP_SRC := $(wildcard $(SRC_DIR)/*.cpp)
APP_HDR := $(wildcard $(SRC_DIR)/*.hpp)

ALL_SRC := $(LIB_SRC) $(APP_SRC)
ALL_HDR := $(LIB_HDR) $(APP_HDR)

ALL_OBJ := $(patsubst $(SRC_DIR)/%, $(TMP_DIR)/%, $(ALL_SRC:.cpp=.o))

.PHONY: directories clean

$(TARGET): directories $(ALL_OBJ) $(ALL_HDR)
	$(CXX) -o $(TARGET) $(ALL_OBJ) $(LDFLAGS)

clean:
	rm -rf $(TMP_DIR)
	rm -f $(TARGET)

directories: $(OUT_DIR) $(TMP_DIR) $(TMP_DIR)/CompilerKit

$(OUT_DIR):
	mkdir -p $(OUT_DIR)
	
$(TMP_DIR):
	mkdir -p $(TMP_DIR)

$(TMP_DIR)/CompilerKit:
	mkdir -p $(TMP_DIR)/CompilerKit

$(TMP_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CPPFLAGS) -c -o $@ $<
	