#Makefile for Program.cpp

CC=g++
EXEC=Program
FCNS=MyFcn
ADD=MyStr
ADD2=TextQuery
DIR=~/Documents/Programowanie/Cpp
CFLAGS=-c -w -std=c++17 -Wfatal-errors
INCLUDES=-I $(DIR)/include
LIBS=
#-lsfml-graphics -lsfml-window -lsfml-system
SOURCES=Program.o MyStr.o
#StrVec.o TextQuery.o MyFcn.o MyStr.o

# Do all
all: $(EXEC)

# Link precompiled files to program
$(EXEC): $(SOURCES)
	@echo "...:::# Starting Compilation of $(EXEC).cpp #:::...\n"
	
	@$(CC) -o $(DIR)/bin/$(EXEC) $(DIR)/build/$(EXEC).o $(LIBS) $(DIR)/build/$(ADD).o 
#$(DIR)/build/$(ADD2).o 
#$(DIR)/build/$(FCNS).o
	
#Adjust access and run program
	@chmod 711 $(DIR)/bin/$(EXEC)
	@$(DIR)/bin/$(EXEC)
	@echo "\n\n...:::# $(EXEC).cpp Finished #:::..."
	
Program.o: $(DIR)/src/$(EXEC).cpp
	@$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) $(DIR)/src/$(EXEC).cpp -o $(DIR)/build/$(EXEC).o
	@echo "<<Main done>>"
	
$(FCNS).o: $(DIR)/src/$(FCNS).cpp
	@$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) $(DIR)/src/$(FCNS).cpp -o $(DIR)/build/$(FCNS).o
	@echo "<<My Function done>>"
	
$(ADD).o: $(DIR)/src/$(ADD).cpp
	@$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) $(DIR)/src/$(ADD).cpp -o $(DIR)/build/$(ADD).o
	@echo "<<$(ADD) done>"
	
$(ADD2).o: $(DIR)/src/$(ADD2).cpp
	@$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) $(DIR)/src/$(ADD2).cpp -o $(DIR)/build/$(ADD2).o
	@echo "<<$(ADD2) done>>"

clean:
	@rm -f $(DIR)/build/$(EXEC)*
	@rm -f $(DIR)/build/$(ADD).o
	#Here should go sources RM
	@rm -f $(DIR)/bin/$(EXEC)
	@echo '...:::# Cleaning of $(EXEC).cpp Components Done #:::...'