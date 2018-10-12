#Makefile for Program.cpp

CC=g++
EXEC=Program
DIR=~/Documents/Programowanie
CFLAGS=-c -w -std=c++17 -Wfatal-errors
INCLUDES=-I $(DIR)/include
LIBS=-lncurses
SOURCES=Program.o

all: $(EXEC)

$(EXEC): $(SOURCES)
	@echo "...:::# Starting Compilation of $(EXEC).cpp #:::...\n"
	@$(CC) $(DIR)/build/$(SOURCES) -o $(DIR)/bin/$(EXEC)
	
	@chmod 711 $(DIR)/bin/$(EXEC)
	@$(DIR)/bin/$(EXEC)
	@echo "\n\n...:::# $(EXEC).cpp Finished #:::..."
	
Program.o: $(DIR)/src/Program.cpp
	@$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) $(DIR)/src/$(EXEC).cpp -o $(DIR)/build/$(EXEC).o 
	
clean:
	@rm -f $(DIR)/build/$(EXEC)*
	#Here should go sources RM
	@rm -f $(DIR)/bin/$(EXEC)
	@echo '...:::# Cleaning of $(EXEC).cpp Components Done #:::...'