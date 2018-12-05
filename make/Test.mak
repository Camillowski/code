#Makefile for Program.cpp

CC=g++
EXEC=Program
DIR=~/Documents/Programowanie
CFLAGS=-c -w -std=c++17 -Wfatal-errors
INCLUDES=-I $(DIR)/include
LIBS=
SOURCES=Program.o Ch13_36.o

# Do all
all: $(EXEC)

# Link precompiled files to program
$(EXEC): $(SOURCES)
	@echo "...:::# Starting Compilation of $(EXEC).cpp #:::...\n"
	@$(CC) $(DIR)/build/$(EXEC).o $(DIR)/build/Ch13_36.o -o $(DIR)/bin/$(EXEC)
#@echo "<<All done>>"
	
#Adjust access and run program
	@chmod 711 $(DIR)/bin/$(EXEC)
	@$(DIR)/bin/$(EXEC)
	@echo "\n\n...:::# $(EXEC).cpp Finished #:::..."
	
Program.o: $(DIR)/src/$(EXEC).cpp
	@$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) $(DIR)/src/$(EXEC).cpp -o $(DIR)/build/$(EXEC).o
#@echo "<<Main done>>"
	
Ch13_36.o: $(DIR)/src/Ch13_36.cpp
	@$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) $(DIR)/src/Ch13_36.cpp -o $(DIR)/build/Ch13_36.o
#@echo "<<Other done>>"

clean:
	@rm -f $(DIR)/build/$(EXEC)*
	@rm -f $(DIR)/build/Ch13_36.o
	#Here should go sources RM
	@rm -f $(DIR)/bin/$(EXEC)
	@echo '...:::# Cleaning of $(EXEC).cpp Components Done #:::...'