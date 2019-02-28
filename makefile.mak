# My new makefile from tutorial
# Universal makefile.
# To use it put name of output file, name of other sourcefiles and libs.
# XTR_INCL are additional header files that dont have same name as FILES
# To turn on DEBUG flag you need pass debug to prog.sh file
# To add library write -lxxx where x is name of library(np.-lsfml-graphics)

#Input
EXEC	:=$(1)
FILES	:=
XTR_INCL:=
LIBS	:=

# Directories
INCLUDE	:=./include
SRC_DIR	:=./src
OBJ_DIR	:=./bin
BLD_DIR	:=./build
DBG_DIR :=./debug

#System variables and settings
SHELL	:=/bin/bash
CPP		:=g++
CFLAGS	=-w -std=c++17 -Wfatal-errors -I$(INCLUDE) $(LIBS)
DEBUG	=$(1)

# Here make condition, if DEBUG is equal to "debug" then make build use DBG_DIR and add  -Og to CFLAG else keep it the way it is.

ifeq ($(DEBUG),debug)
	BUILD	=$(DBG_DIR)/$(EXEC)
	CFLAGS	+= -g
else
	BUILD	=$(BLD_DIR)/$(EXEC)
endif


# if DEBUG is equal to debug then add -Og and change output dir to ./debug


.PHONY:	all clean

# Objects with directory and header dependencies
OBJS=$(patsubst %,$(OBJ_DIR)/%.o ,$(EXEC) $(FILES))
INCL_DEPS=$(patsubst %,$(INCLUDE)/%.h,$(FILES) $(XTR_INCL)) 

all:$(BUILD)	

# Compile proces
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCL_DEPS)
# @echo $(INCL_DEPS)
# @echo "Compiling..."
	@$(CPP) -c -o $@ $< $(CFLAGS)

# Build proces
$(BUILD): $(OBJS)
# @echo "Building..."
	@$(CPP) -o $(BUILD) $(OBJS)

# Delete .o files
clean:
	@echo "Removing *.o files..."
	rm $(OBJ_DIR)/*.o

# FLOW: All will be done when $(BUILD)(Program) exists For program to exist it needs $(OBJS)(Program.o MyStr.o) .To create those it needs %.cpp files (and check if .h files have changed). *.cpp file exists so it is compiled(recipe si run). After all .cpp files are compiled all prerequisites for Program file are matched. Building (Linking) process starts.
