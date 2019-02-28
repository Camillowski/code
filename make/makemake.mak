#My new makefile from tutorial
# Universal makefile.
# To use it put name of output file, name of other sourcefiles and libs.
# To add library write -lxxx where x is name of library(np.-lsfml-graphics)

#Input
EXEC	:=Program
FILES	:=hellomake helloadd hellofunc
LIBS	:=

#System variables and settings
SHELL	:=/bin/bash
CPP		:=g++
CFLAGS	=-w -std=c++17 -I$(INCLUDE) $(LIBS)
BUILD	=$(BLD_DIR)/$(EXEC)
.PHONY:	all clean

# -Wfatal-errors

# Directories
INCLUDE	:=./makehpp
SRC_DIR	:=./makecpp
OBJ_DIR	:=./makebin
BLD_DIR	:=./makebuild

# Objects with directory
OBJS=$(patsubst %,$(OBJ_DIR)/%.o ,$(FILES))

# Start program
__start__: all clean
	@$(BUILD)

all:$(BUILD)	

# Compile proces
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compiling..."
	@$(CPP) -c -o $@ $< $(CFLAGS)

# Build proces
$(BUILD): $(OBJS)
	@echo "Building..."
	@$(CPP) -o $@ $(OBJS)

# Delete .o files
clean:
	@echo "Removing *.o files..."
	@rm $(OBJ_DIR)/*.o

# $@ -name on the left from :
# $< -first thing in dependencies list (%.cpp)

# I want to put build files to bin dirctory.
# I want to delete *.o files after build proces
# I want to run program after building
# I want to choose project directory with structure:
# Project
# |---src/
# |---build/
# |---bin/
# |---include/
# |---lib/
# |-makefile.mak